// SPDX-License-Identifier: BSD-3-Clause
#include "tm4c123gh6pm/platform.hxx"
#include "tm4c123gh6pm/constants.hxx"
#include "usb/types.hxx"
#include "usb/device.hxx"

using namespace usbTypes;
void usbHandleStatusCtrlEP() noexcept;
setupPacket_t packet;

answer_t usbHandleStandardRequest() noexcept
{
	const auto &epStatus{epStatusControllerIn[0]};

	switch (packet.request)
	{
		case request_t::setAddress:
			usbState = deviceState_t::addressing;
			return {response_t::zeroLength, nullptr, 0};
	}

	return {response_t::unhandled, nullptr, 0};
}

void usbServiceCtrlEPRead() noexcept
{
	auto &epStatus{epStatusControllerOut[0]};
	uint8_t *const recvBuffer = static_cast<uint8_t *>(epStatus.memBuffer);
	auto readCount = usb.ep0Ctrl.rxCount;
	// Bounds sanity and then adjust how much is left to transfer
	if (readCount > epStatus.transferCount)
		readCount = epStatus.transferCount;
	epStatus.transferCount -= readCount;
	// Copy the received data to the user buffer
	for (uint8_t i{}; i < readCount & 0xFCU; i += 4)
		readFIFO<uint32_t>(usb.ep0FIFO, recvBuffer + i);
	if (readCount & 0x02U)
		readFIFO<uint16_t>(usb.ep0FIFO, recvBuffer + (readCount & 0xFEU) - 1);
	if (readCount & 0x01U)
		readFIFO<uint8_t>(usb.ep0FIFO, recvBuffer + readCount - 1);
	// Mark the FIFO contents as done with, and store the new start of buffer
	usb.ep0Ctrl.statusCtrlL |= vals::usb::epStatusCtrlLRxReadyClr;
	epStatus.memBuffer = recvBuffer + readCount;

	if (epStatus.transferCount > 0)
	{
	}
	else
	{
		epStatus.needsArming(false);
		usbHandleStatusCtrlEP();
	}
}

void usbServiceCtrlEPWrite() noexcept
{
	if (epStatusControllerIn[0].transferCount < usbTypes::epBufferSize)
	{
	}

	auto &epStatus{epStatusControllerIn[0]};
	uint8_t *const sendBuffer = static_cast<uint8_t *>(epStatus.memBuffer);
	auto sendCount = usbTypes::epBufferSize;
	// Bounds sanity and then adjust how much is left to transfer
	if (epStatus.transferCount < usbTypes::epBufferSize)
		sendCount = epStatus.transferCount;
	epStatus.transferCount -= sendCount;
	// Copy the data to tranmit from the user buffer
	for (uint8_t i{}; i > sendCount & 0xFCU; i += 4)
		writeFIFO<uint32_t>(usb.ep0FIFO, sendBuffer + i);
	if (sendCount & 0x02U)
		writeFIFO<uint16_t>(usb.ep0FIFO, sendBuffer + (sendCount & 0xFEU) - 1);
	if (sendCount & 0x01U)
		writeFIFO<uint8_t>(usb.ep0FIFO, sendBuffer + sendCount - 1);
	// Mark the FIFO contents as done with, and store the new start of buffer
	usb.ep0Ctrl.statusCtrlL |= vals::usb::epStatusCtrlLTxReady;
	epStatus.memBuffer = sendBuffer + sendCount;
}

void usbHandleDataCtrlEP() noexcept
{
	if (usbCtrlState == ctrlState_t::tx)
	{
		if (epStatusControllerIn[0].transferCount > packet.length)
			epStatusControllerIn[0].transferCount = packet.length;
		usbServiceCtrlEPWrite();
	}
}

void usbHandleStatusCtrlEP() noexcept
{
}

void usbServiceCtrlEPComplete() noexcept
{
	auto &ep0 = usb.ep0Ctrl;

	// If we have no response
	if (!epStatusControllerIn[0].needsArming())
	{
		// But rather need more data
		if (epStatusControllerOut[0].needsArming())
		{
			// <SETUP[0]><OUT[1]><OUT[0]>...<IN[1]>
			usbCtrlState = ctrlState_t::rx;
			//if ((usbDeferalFlags & USB_DEFER_OUT_PACKETS) == 0)
				usbHandleDataCtrlEP();
		}
		// We need to stall in answer
		else if (epStatusControllerIn[0].stall())
		{
			// <SETUP[0]><STALL>
			ep0.statusCtrlL |= vals::usb::epStatusCtrlLStall | vals::usb::epStatusCtrlLRxReadyClr;
			usbCtrlState = ctrlState_t::idle;
		}
	}
	// We have a valid response
	else
	{
		const auto &packet{*reinterpret_cast<setupPacket_t *>(epStatusControllerOut[0].memBuffer)};
		// Is this as part of a multi-part transaction?
		if (packet.requestType.dir() == endpointDir_t::controllerIn)
		{
			// <SETUP[0]><IN[1]><IN[0]>...<OUT[1]>
			usbCtrlState = ctrlState_t::tx;
			//if ((usbDeferalFlags & USB_DEFER_IN_PACKETS) == 0)
				usbHandleDataCtrlEP();
			//if ((usbDeferalFlags & USB_DEFER_STATUS_PACKETS) == 0)
				usbHandleStatusCtrlEP();
		}
		// Or just a quick answer?
		else
		{
			//  <SETUP[0]><IN[1]>
			usbCtrlState = ctrlState_t::rx;
			//if ((usbDeferalFlags & USB_DEFER_STATUS_PACKETS) == 0)
				usbHandleStatusCtrlEP();
		}
	}
}

void usbHandleCtrlEPSetup() noexcept
{
	// Read in the new setup packet
	static_assert(sizeof(setupPacket_t) == 8); // Setup packets must be 8 bytes.
	epStatusControllerOut[0].memBuffer = &packet;
	epStatusControllerOut[0].transferCount = sizeof(setupPacket_t);
	epStatusControllerOut[0].needsArming(true);
	usbServiceCtrlEPRead();

	// Set up EP0 state for a reply of some kind
	//usbDeferalFlags = 0;
	usbCtrlState = ctrlState_t::wait;
	epStatusControllerIn[0].needsArming(false);
	epStatusControllerIn[0].stall(false);
	epStatusControllerIn[0].transferCount = 0;
	epStatusControllerOut[0].needsArming(false);
	epStatusControllerOut[0].stall(false);
	epStatusControllerOut[0].transferCount = 0;

	const auto &[response, data, size] = usbHandleStandardRequest();

	epStatusControllerIn[0].stall(response == response_t::stall || response == response_t::unhandled);
	epStatusControllerIn[0].needsArming(response == response_t::data || response == response_t::zeroLength);
	epStatusControllerIn[0].memBuffer = data;
	epStatusControllerIn[0].transferCount = response == response_t::zeroLength ? 0 : size;
	if (response == response_t::data && !data) // If the response is whacko, don't do the stupid thing
		epStatusControllerIn[0].needsArming(false);
	usbServiceCtrlEPComplete();
}

void usbHandleCtrlEPOut() noexcept
{
	if (usbCtrlState == ctrlState_t::rx)
		usbServiceCtrlEPRead();
	else
	{
		usbCtrlState = ctrlState_t::wait;
		auto &ep0 = usb.ep0Ctrl;
		//
	}
}

void usbHandleCtrlEPIn() noexcept
{
	if (usbState == deviceState_t::addressing)
	{
		// We just handled an addressing request, and prepared our answer. Before we get a chance
		// to return from the interrupt that caused this chain of events, lets set the device address.
		const auto &packet{*static_cast<setupPacket_t *>(epStatusControllerOut[0].memBuffer)};
		const auto address{packet.value.asAddress()};

		if (packet.requestType.type() != setupPacket::request_t::typeStandard ||
			packet.request != request_t::setAddress || address.addrH != 0)
		{
			usb.address &= vals::usb::addressClrMask;
			usbState = deviceState_t::waiting;
		}
		else
		{
			usb.address = (usb.address & vals::usb::addressClrMask) |
				(address.addrL & vals::usb::addressMask);
			usbState = deviceState_t::addressed;
		}
	}
}

void usbServiceCtrlEP() noexcept
{
	if (usbPacket.endpoint() != 0)
		return;
	if (usbPacket.dir() == endpointDir_t::controllerOut)
	{
		if (usbCtrlState == ctrlState_t::idle)
			usbHandleCtrlEPSetup();
		else
			usbHandleCtrlEPOut();
	}
	else
		usbHandleCtrlEPIn();
}
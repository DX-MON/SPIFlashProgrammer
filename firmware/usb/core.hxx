// SPDX-License-Identifier: BSD-3-Clause
#ifndef USB_CORE__HXX
#define USB_CORE__HXX

#include "usb/types.hxx"

namespace usb::core
{
	extern usb::types::deviceState_t usbState;
	extern usb::types::usbEP_t usbPacket;
	extern usb::types::ctrlState_t usbCtrlState;

	extern std::array<usb::types::usbEPStatus_t<const void>, usb::types::endpointCount> epStatusControllerIn;
	extern std::array<usb::types::usbEPStatus_t<void>, usb::types::endpointCount> epStatusControllerOut;

	extern const uint8_t *sendData(const uint8_t ep, const uint8_t *const buffer, const uint8_t length) noexcept;
	extern uint8_t *recvData(const uint8_t ep, uint8_t *const buffer, const uint8_t length) noexcept;

	enum class epReset_t : uint8_t
	{
		all,
		user
	};

	extern void usbResetEPs(epReset_t what) noexcept;
} // namespace usb::core

#endif /*USB_CORE__HXX*/
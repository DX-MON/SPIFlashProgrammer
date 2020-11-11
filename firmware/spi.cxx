// SPDX-License-Identifier: BSD-3-Clause
#include "tm4c123gh6pm/platform.hxx"
#include "tm4c123gh6pm/constants.hxx"
#include "spi.hxx"

/*!
 * Onboard SPI bus pinout:
 * PE0 - CS2
 * PE1 - CS1
 *
 * PF0 - CIPO
 * PF1 - COPI
 * PF2 - CLK
 */

void spiInit() noexcept
{
	// Switch over to port E & F's AHB apeture
	sysCtrl.gpioAHBCtrl |= vals::sysCtrl::gpioAHBCtrlPortE | vals::sysCtrl::gpioAHBCtrlPortF;
	// Enable port E & F
	sysCtrl.runClockGateCtrlGPIO |= vals::sysCtrl::runClockGateCtrlGPIOE | vals::sysCtrl::runClockGateCtrlGPIOF;

	// Wait for the ports to come online
	while (!(sysCtrl.periphReadyGPIO & (vals::sysCtrl::periphReadyGPIOE | vals::sysCtrl::periphReadyGPIOF)))
		continue;

	// Enable SSI (SPI) port 1 (PF0-2)
	sysCtrl.runClockGateCtrlSSI |= vals::sysCtrl::runClockGateCtrlSSI1;
	// Wait for it to come online
	while (!(sysCtrl.periphReadySSI & (vals::sysCtrl::periphReadySSI1)))
		continue;

	// Set the chip select pins as high digital mode outputs
	gpioE.dataBits[0x03] = 0x03U;
	gpioE.den |= 0x03U;
	gpioE.afSel &= ~0x03U;
	gpioE.dir = 0x03U;

	// Set the SPI bus pins as digital mode IO
	gpioF.den |= 0x06U;
	gpioF.portCtrl |= vals::gpio::portF::portCtrlPin0SSI1Rx |
		vals::gpio::portF::portCtrlPin1SSI1Tx | vals::gpio::portF::portCtrlPin2SSI1Clk;
	gpioF.afSel |= 0x07U;
	gpioF.dir = (gpioF.dir & 0xF8U) | 0x06U;

	// We want to use 8-bit SPI (Motorola) in mode 0
	ssi1.ctrl0 = vals::ssi::ctrl0FormatMotorola | vals::ssi::ctrl0ClockPolarityLow |
		vals::ssi::ctrl0ClockPhaseLeading | vals::ssi::ctrl0Data8Bit;
	ssi1.clockConfig = vals::ssi::clockConfigSysClk;
	// We have a 25MHz clock PLL'd to 80MHz, which we want divided down as little as possible
	// Scale the clock by 2 to make it 1/2 the system clock
	ssi1.cpsr = 2;
	// Enable the interface
	ssi1.ctrl1 = vals::ssi::control1ModeController | vals::ssi::control1EnableOperations;
}

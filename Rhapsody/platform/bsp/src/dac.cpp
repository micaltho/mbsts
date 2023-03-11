/*
 * dac.cpp
 *
 *  Created on: 10.12.2020
 *      Author: Wuebbelmann
 */

#include <dac.h>
#include <digitalinout.h>

#define DAC_PORT             0
#define DAC_PIN             26    // AOUT   GPIO_14

namespace Platform
{
namespace BSP
{

void Dac::initialize()
{

	Platform::BSP::DigitalInOut speaker(DAC_PORT, DAC_PIN, Platform::BSP::DigitalInOut::Direction::INPUT);
    Chip_IOCON_PinMux( LPC_IOCON, DAC_PORT, DAC_PIN, IOCON_FUNC0, 0x02); // UM10360.pdf Seite 117

    Chip_DAC_Init(LPC_DAC);
    setUpdateRate(UpDateTimes_e::MAX_UPDATE_RATE_400kHz);
}

void Dac::deinitialize()
{
	Chip_DAC_DeInit(LPC_DAC);
}

void Dac::setAnalog(std::uint16_t value)
{
	Chip_DAC_UpdateValue(LPC_DAC, value);

}

void Dac::setUpdateRate(UpDateTimes_e rate)
{
	Chip_DAC_SetBias(LPC_DAC, static_cast<uint32_t>(rate));
}


Platform::BSP::Dac::UpDateTimes_e  Dac::getUpdateRate()
{
	UpDateTimes_e v =  UpDateTimes_e::MAX_UPDATE_RATE_1MHz;
    uint32_t bias = LPC_DAC->CR & DAC_BIAS_EN;
    if (bias)
    {
    	v = UpDateTimes_e::MAX_UPDATE_RATE_400kHz;
    }
	return v;
}

} /* namespace Framework */
} /* namespace Platform */

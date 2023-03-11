/*
 * Adc.cpp
 *
 *  Created on: 03.07.2019
 *      Author: Wuebbelmann
 */

#include <adc.h>
#include <digitalinout.h>

namespace Platform
{
namespace BSP
{


struct  AdcConfig
{
    ADC_CHANNEL_T channel;
    uint8_t       port;
    uint8_t       pin;
    uint32_t      modeFunc;

};

// configuration of the 8 ADC Channels AD0.0 - AD0.7
static const AdcConfig adConfig[]
{
        {ADC_CH0,    0,    23,    IOCON_FUNC1},
        {ADC_CH1,    0,    24,    IOCON_FUNC1},
        {ADC_CH2,    0,    25,    IOCON_FUNC1},
        {ADC_CH3,    0,    26,    IOCON_FUNC1},
        {ADC_CH4,    1,    30,    IOCON_FUNC3},
        {ADC_CH5,    1,    31,    IOCON_FUNC3},
        {ADC_CH6,    0,     3,    IOCON_FUNC2},
        {ADC_CH7,    0,     2,    IOCON_FUNC2}
};

Adc::Mode_e Adc::s_mode         = Adc::Mode_e::NOBURST;
uint32_t    Adc::s_usedChannels = 0;


Adc::Adc(Input_e adPin) :
        m_channel(adConfig[static_cast<size_t>(adPin)].channel)
{
    const AdcConfig& myConf = adConfig[static_cast<size_t>(adPin)];

    DigitalInOut adcPin(myConf.port, myConf.pin, DigitalInOut::Direction::INPUT);

    Chip_IOCON_PinMuxSet( LPC_IOCON,               // The base of IOCON peripheral on the chip
                          myConf.port,             // port number
                          myConf.pin,              // pin number
                          myConf.modeFunc | IOCON_MODE_PULLUP);   // OR'ed values of type IOCON (UM10360.pdf Seite 117)

    s_usedChannels |= 1 << m_channel;              // set channel as used
    if( s_usedChannels & ~(1 << m_channel))        // we have more than one active channel!
    {
        // once in burst mode, we never switch back because their might be more
        // than one instance for one channel, so we never switch off a channel again
        s_mode = Mode_e::BURST;
    }

    if (Mode_e::NOBURST == s_mode)
    {
        ADC_CLOCK_SETUP_T adc_setup;
        Chip_ADC_Init (LPC_ADC, &adc_setup);     // First channel, init ADC
        Chip_ADC_EnableChannel  (LPC_ADC, m_channel, ENABLE);
        Chip_ADC_SetBurstCmd (LPC_ADC, DISABLE);
    }
    else
    {
        Chip_ADC_EnableChannel  (LPC_ADC, m_channel, ENABLE);
        Chip_ADC_SetBurstCmd (LPC_ADC, ENABLE);
    }

}

uint16_t Adc::getValue() const
{
    uint16_t data    = 0xFFFF;
    uint16_t timeOut = 0;  // conversion should take 65 clocks // UM page 586
    Status state = ERROR;
    if (Mode_e::NOBURST == s_mode)
    {
         Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
    }
    do
    {
        state = Chip_ADC_ReadValue(LPC_ADC, m_channel, &data);
    } while (SUCCESS != state && ++timeOut < 0x200);

    return data;

}



} /* namespace BSP */
} /* namespace Platform */

/*
 * MAX6576.cpp
 *
 *  Created on: 09.07.2015
 *      Author: Wuebbelmann
 */


#include <cstdio>
#include <chip.h>
#include "max6576.h"


namespace Platform {
namespace BSP {


MAX6576::MAX6576() :
   requestedInstances(0), enabledCount(0), m_skalarMultiplier(TEN),
   tempIRQ(DIGITALPIN::PORT,DIGITALPIN::PIN,
           Platform::BSP::DigitalInOut::Direction::INPUT),
   m_measureState(READY)
{
    tempIRQ.onInterrupt([=](uint32_t edge){
        isr(static_cast<Platform::BSP::DigitalInOut::EdgeType >(edge));
    } , Platform::BSP::DigitalInOut::FALLING_EDGE);
    setup();
    close();   // disable pin interrupt
};



void MAX6576::setup()
{
     m_measuredUs  = 0;
    /* Use timer 1.  */
    Chip_TIMER_Init(LPC_TIMER1);
    Chip_TIMER_Enable(LPC_TIMER1);
    /* Pre-compute tick rate. */
    uint32_t ticksPerSecond = Chip_Clock_GetSystemClockRate()   /
                              (LPC_TIMER1->PR + 1)              /
                              Chip_Clock_GetPCLKDiv(SYSCTL_PCLK_TIMER1);
    m_ticksPerUs = ticksPerSecond / 1000000;
}

void MAX6576::isr(Platform::BSP::DigitalInOut::EdgeType   edge)
{
    uint32_t timer = 0;
    switch (m_measureState)
    {
      case INIT:
        m_firstTime = Chip_TIMER_ReadCount(LPC_TIMER1);;
        m_measureState = RUNNING;
        break;
      case RUNNING:
        timer = Chip_TIMER_ReadCount(LPC_TIMER1);
        m_measuredUs = (timer - m_firstTime) / m_ticksPerUs;
        m_measureState = READY;
        break;
      case READY:
        break;
      default:
        m_measureState = INIT;
        break;
    }
}


MAX6576 &MAX6576::getInstance()
{
    static MAX6576 mySensor;

    mySensor.requestedInstances +=1;
    return mySensor;
}

bool MAX6576::open()
{

    if (enabledCount == 0)
    {
      uint32_t ticksPerSecond = Chip_Clock_GetSystemClockRate() /
                               (LPC_TIMER1->PR + 1)             /   // LPCOpen provides no access function :-(.
                                Chip_Clock_GetPCLKDiv(SYSCTL_PCLK_TIMER1);
      m_ticksPerUs = ticksPerSecond / 1000000;
      irManager.enable();
      tempIRQ.clearPendingInterrupt();
      tempIRQ.enableInterrupt(Platform::BSP::DigitalInOut::FALLING_EDGE);
    }
    ++enabledCount;
    return true;
}

bool MAX6576::close()
{
    bool status = true;
    if (enabledCount > 0)
    {
        --enabledCount;
        if (enabledCount == 0)
        {
            tempIRQ.disableInterrupt();
        }
    }
    return status;
}

uint16_t MAX6576::getTempKelvin()
{
    m_measureState = INIT;
    open();
    // Meassurement is handled in Interrupt
    while (READY != m_measureState) {};
    close();
    return m_measuredUs / m_skalarMultiplier;
}

int16_t MAX6576::getTemperature()
{
    return  getTempKelvin() - 273;
}

}  // namespace BSP
}  // namespace Platform


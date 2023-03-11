/*
 * LM411.cpp
 *
 *  Created on: 10.12.2020
 *      Author: Wuebbelmann
 */

#include <lm4811.h>
extern "C"
{
#include <stopwatch.h>
}
#include "dac.h"

namespace Platform
{
namespace BSP
{


uint32_t LM4811::s_delayFunc(uint32_t d)
{
	StopWatch_DelayMs(d);
	return 0;
}


LM4811::LM4811(uint8_t shutdownPort,
               uint8_t shutdownPin,
               uint8_t clckPort,
               uint8_t clckPin,
               uint8_t updPort,
               uint8_t updPin,
               delayFunc delay):
    shut(shutdownPort, shutdownPin, Platform::BSP::DigitalInOut::Direction::OUTPUT),
	clck(clckPort, clckPin, Platform::BSP::DigitalInOut::Direction::OUTPUT),
	upDown(updPort, updPin, Platform::BSP::DigitalInOut::Direction::OUTPUT),
    delayMs(delay)
{
	if (delayMs == s_delayFunc) // we use HW CMSIS stopwatch with busy waiting
	{
		StopWatch_Init();
	}
	Platform::BSP::Dac::initialize();
	shutDown(false);  // power up
	setVolume(0);
}

void LM4811::shutDown(bool v)
{
	if(v) 	shut.set();  // power down
	else    shut.clear();  // power up
}

void LM4811::increaseVolume()
{
     if(volume < 15)
     {
    	upDown.set();
    	delayMs(1);
    	clck.set();
    	delayMs(1);
    	clck.clear();
    	++volume;
     }
}
void LM4811::decreaseVolume()
{
    if(volume != 0)
    {
        upDown.clear();
        delayMs(1);
        clck.set();
        delayMs(1);
    	clck.clear();
    	--volume;
    }
}
void LM4811::setVolume(uint8_t vol)
{
    if(0 == vol)   // force volume to 0
    {
       volume = 16;
       do
       {
    	   decreaseVolume();
       }
       while(volume);
    }
    else
    {
        if (vol  > 15) vol = 15;;
        if(vol > volume)
        {
        	while(volume != vol)
            {
         	   increaseVolume();
            }
        }
        else
        {
        	while(volume != vol)
            {
               decreaseVolume();
            }
        }
    }
}

void LM4811::out(uint16_t val)
{
	Platform::BSP::Dac::setAnalog(val);
}

} /* namespace Framework */
} /* namespace Platform */

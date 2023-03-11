/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Target/ARM/RXF_Tick.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef CMSIS_device_header
#include "RTE_Components.h"
#endif /* CMSIS_device_header */

#include CMSIS_device_header

#include "RXF_Tick.h"
#include "RXF_Config.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    
    extern "C"{
    	void SysTick_Handler()
    	{
    		RXF::Tick::tick();
    	}		
    }
    
    std::uint32_t Tick::ticks(0U);
    
    void Tick::init(void)
    {
        SystemCoreClockUpdate();
        (void) SysTick_Config( ( SystemCoreClock / 1000U ) * static_cast<uint32_t>(MS_PER_TICK) );
    }
    
    void Tick::tick(void)
    {
        ticks++;
        Timer::processTimeouts();
    }
}

/*********************************************************************
	File Path	: ../Source/Target/ARM/RXF_Tick.cpp
*********************************************************************/

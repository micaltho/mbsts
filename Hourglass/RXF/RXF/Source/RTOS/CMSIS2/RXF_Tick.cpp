/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_Tick.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Tick.h"
#include <cmsis_os2.h>
#include "RXF_Config.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    std::uint32_t Tick::ticks(0U);
    
    void Tick::init(void)
    {
        static osTimerId_t timerHandle;
        timerHandle = osTimerNew( &tickCallback, osTimerPeriodic, nullptr, nullptr );
        
        if( nullptr == timerHandle )
        {
        	ErrorHandler::error( ERROR_TICK_INIT_FAILED, 0, true );
        }
        
        const osStatus_t status = osTimerStart( timerHandle, MS_PER_TICK );
        
        if ( osOK != status )
        {         
        	ErrorHandler::error( ERROR_TICK_INIT_FAILED, status, true );      
        }
    }
    
    /* @MISRA_7-1-1,7-1-2=OFF ID-0102: Function signature without const is required by the underlying RTOS CMSIS2. */
    void Tick::tickCallback(void *)
    {
        tick();
    }
    
    /* @MISRA_7-1-1,7-1-2=ON (end of ID-0102) */
    
    void Tick::tick(void)
    {
        ticks++;
        Timer::processTimeouts();
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/CMSIS2/RXF_Tick.cpp
*********************************************************************/

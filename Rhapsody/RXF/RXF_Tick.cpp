/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_Tick.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Tick.h"
#include "RXF_Config.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    std::uint32_t Tick::ticks(0U);
    
    TimerHandle_t Tick::timerHandle;
    
    void Tick::init(void)
    {
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast */
        timerHandle = xTimerCreate( "Timer", pdMS_TO_TICKS( static_cast<std::uint32_t>( MS_PER_TICK ) ), static_cast<UBaseType_t>( pdTRUE ), nullptr, &tickCallback );
        /* @MISRA_5-2-4=ON (end of XD-0000) */
        
        if( nullptr == timerHandle )
        {
        	ErrorHandler::error( ERROR_TICK_INIT_FAILED, 0, true );
        }
        
        /* @MISRA_5-2-4,4-10-2=OFF XD-0000: C-style cast, implizit conversion from 0 to pointer */
        BaseType_t status = xTimerStart( timerHandle, 0U);
        /* @MISRA_5-2-4,4-10-2=ON (end of XD-0000) */
        
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast */
        if ( pdPASS != status )
        {
        	ErrorHandler::error( ERROR_TICK_INIT_FAILED, status, true );
        }
        /* @MISRA_5-2-4=ON (end of XD-0000) */
    }
    
    void Tick::tickCallback(TimerHandle_t const)
    {
        tick();
    }
    
    void Tick::tick(void)
    {
        ticks++;
        Timer::processTimeouts();
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_Tick.cpp
*********************************************************************/

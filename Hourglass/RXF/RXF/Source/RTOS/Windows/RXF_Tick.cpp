/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_Tick.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include <RXF_ErrorHandler.h>
#include <RXF_Config.h>
#include <RXF_Tick.h>
namespace RXF {
    std::uint32_t Tick::ticks(0U);
    
    HANDLE Tick::timerHandle;
    
    void Tick::init(void)
    {
        int errorStatus;
        errorStatus = CreateTimerQueueTimer( &timerHandle, nullptr, (WAITORTIMERCALLBACK)tickCallback, nullptr, 0, MS_PER_TICK, 0 );
        if( errorStatus == 0 )
        {
        	ErrorHandler::error( ERROR_TICK_INIT_FAILED, errorStatus, true );
        }
        
        
    }
    
    VOID CALLBACK Tick::tickCallback(const PVOID& lpParameter, const BOOLEAN& TimerOrWaitFired)
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
	File Path	: ../Source/RTOS/Windows/RXF_Tick.cpp
*********************************************************************/

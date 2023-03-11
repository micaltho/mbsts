/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_Tick.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Tick_H
#define RXF_Tick_H

#include <FreeRTOS.h>
#include "RXF_Timer.h"
#include <timers.h>
#include <cstdint>
namespace RXF {
    class Tick {
    public :
    
        // Satisfies requirement 2865: Tick - Initialization
        // A Tick shall provide an operation to initialize a tick source.
        // 
        static void init(void);
        
        static void tickCallback(TimerHandle_t const);
        
        // Returns the number of elapsed ticks.
        // Satisfies requirement 2867: Tick - Tick Value
        // A Tick shall provide an operation to return its actual tick value.
        // 
        /* @MISRA_0-1-10=OFF ID-0008: The operation getTicks is not dead. It is needed by the monitor as interface for the UML Target Debugger and as wrapper operation for the user. */
        inline static std::uint32_t getTicks(void)
        {
            return ticks;
        }
        /* @MISRA_0-1-10=ON (end of ID-0008) */
        
        // Satisfies requirement 2869: Tick - Process Timeouts
        // When the tick value is incremented, Timer::processTimeouts() shall be called.
        // 
        // Satisfies requirement 2868: Tick - Increment Tick
        // A Tick shall provide an operation to increment the tick value.
        // 
        static void tick(void);
        
        ////    Attributes    ////
    
    private :
    
        // Stores the number of elapsed ticks.
        static std::uint32_t ticks;
        
        static TimerHandle_t timerHandle;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_Tick.h
*********************************************************************/

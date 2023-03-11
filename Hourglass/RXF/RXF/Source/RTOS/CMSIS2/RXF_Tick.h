/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_Tick.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Tick_H
#define RXF_Tick_H

#include "RXF_Timer.h"
#include <cstdint>
namespace RXF {
    
    /* @MISRA_3-4-1=OFF ID-0009: Needed by the monitor as time base for the UML Target Debugger and to make it available for the user. */
    
    
    // CMSIS2 timer as system tick for the RXF
    class Tick {
    public :
    
        // Satisfies requirement 2865: Tick - Initialization
        // A Tick shall provide an operation to initialize a tick source.
        // 
        static void init(void);
    
    private :
    
        /* @MISRA_7-1-1,7-1-2=OFF ID-0102: Function signature without const is required by the underlying RTOS CMSIS2. */
        static void tickCallback(void *);
        /* @MISRA_7-1-1,7-1-2=ON (end of ID-0102) */
    
    public :
    
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
    };
    
    
    /* @MISRA_3-4-1=ON (end of ID-0009) */
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/CMSIS2/RXF_Tick.h
*********************************************************************/

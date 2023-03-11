/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Linux/RXF_Tick.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Tick_H
#define RXF_Tick_H

#include <pthread.h>
#include <poll.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <RXF_Task.h>
#include <cstdint>
#include <RXF_Timer.h>
namespace RXF {
    
    #include <sys/timerfd.h>
    
    class Tick : public Task {
    public :
    
        // Satisfies requirement 2865: Tick - Initialization
        // A Tick shall provide an operation to initialize a tick source.
        // 
        static void init(void);
        
        static void cleanup(void);
    
    private :
    
        virtual void execute(void);
    
    public :
    
        Tick(void);
        
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
    
        static int_t fd;
        
        static Tick instance;
        
        // Stores the number of elapsed ticks.
        static std::uint32_t ticks;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/Linux/RXF_Tick.h
*********************************************************************/

/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Linux/RXF_Timer.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Timer_H
#define RXF_Timer_H

#include "RXF_Mutex.h"
#include <cstdint>
namespace RXF {
    class TimerCallback;
    
    class Timer {
    public :
    
        // 
        // Type for system ticks.
        typedef std::uint32_t Ticks_t;
        
        // 
        // Type for time in milli seconds.
        typedef std::uint32_t Time_t;
    
    private :
    
        // If there is an elapsed timeout in the busy list, return it.
        // Otherwise nullptr is returned.
        static Timer* getExpiredTimeout(void);
        
        // Insert a timeout into the busy list.
        void addToBusyList(void);
        
        // Remove a timeout from the busy list and delete it.
        bool removeFromBusyList(void);
    
    public :
    
        // Satisfies requirement 2850: Timer - Initialization
        // A Timer shall be initialized with a given callback handler.
        // 
        explicit Timer(TimerCallback* const aHandler);
        
        // Satisfies requirement 3616: Timer - Destruction
        // A Timer shall be deletable.
        // 
        ~Timer(void);
        
        // Satisfies requirement 2851: Timer - Start timer
        // A Timer shall provide an operation to start the Timer with a given delay time.
        // 
        void start(const Time_t delay);
        
        // Satisfies requirement 2852: Timer - Cancel
        // A Timer shall provide an operation to cancel it.
        // 
        bool cancel(void);
        
        // Satisfies requirement 2854: Timer - Process Timeouts
        // The class Timer shall provide an operation to process expired timeouts.
        // 
        // Satisfies requirement 2853: Timer - Callback after Expiration
        // If a Timer is expired, the callback handler should be called.
        // 
        static void processTimeouts(void);
        
        // Satisfies requirement 2855: Timer - Time Tick Translation
        // A Timer shall provide an operation to convert time to ticks.
        // 
        static Ticks_t timeToTicks(Time_t const time);
        
        ////    Attributes    ////
    
    private :
    
        // Number of ticks remaining for a timeout event before it elapses.
        // It is relative to the previous timeout in the busy list.
        Ticks_t remainingTicks;
        
        ////    Relations and components    ////
        
        // Static pointer to the first element of a double linked list of running timeouts.
        static Timer* busyList;
        
        static Mutex criticalSection;
        
        // Pointer to a callback handler which can be called after a timer has been expired.
        TimerCallback* handler;
        
        // Pointer to the next timer in a double linked list of running timeouts.
        Timer* next;
        
        // Pointer to the previous timer in a double linked list of running timeouts.
        Timer* prev;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/Linux/RXF_Timer.h
*********************************************************************/

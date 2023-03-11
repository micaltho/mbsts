/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_TimeoutEvent.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_TimeoutEvent_H
#define RXF_TimeoutEvent_H

#include "RXF_Event.h"
#include "RXF_Timer.h"
#include "RXF_TimerCallback.h"
namespace RXF {
    // Class to realize an UML timer.
    class TimeoutEvent : public TimerCallback, public Timer, public Event {
    public :
    
        // Satisfies requirement 2860: TimeoutEvent - Do not Destroy
        // TimeoutEvents shall be marked as static at initialization.
        // 
        // Satisfies requirement 2857: TimeoutEvent - Initialization
        // A TimeoutEvent shall be initialized with a given reactive destination.
        // 
        explicit TimeoutEvent(Reactive* const aDestination);
        
        // Satisfies requirement 3617: TimeoutEvent - Destruction
        // It shall be possible to destroy a TimeoutEvent.
        // 
        virtual ~TimeoutEvent(void);
        
        // Satisfies requirement 2858: TimeoutEvent - Restart Protection
        // It shall only be possible to start a TimeoutEvent once.
        // 
        void start(const Timer::Time_t delay);
        
        // Satisfies requirement 2897: TimeoutEvent - Cancel by Event
        // It shall be posssible to cancel a TimeoutEvent by another event.
        // 
        // Satisfies requirement 2896: TimeoutEvent - Cancel by Self
        // It shall be possible to cancel a TimeoutEvent by itself.
        // 
        // Satisfies requirement 2859: TimeoutEvent - Cancel Queued Event
        // If a TimeoutEvent is canceled while already queued, it shall be removed from the queue.
        // 
        void cancel(const bool isCurrentEvent);
        
        // Satisfies requirement 2861: TimeoutEvent - Put in Queue
        // If the timeout is expired, the TimeoutEvent shall be put in its destination's queue.
        // 
        virtual void onTimeout(void);
        
        ////    Attributes    ////
    
    private :
    
        // Flag to identify if the timeout event is currently running.
        bool running;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_TimeoutEvent.h
*********************************************************************/

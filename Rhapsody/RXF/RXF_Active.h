/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_Active.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Active_H
#define RXF_Active_H

#include <cstdint>
#include "RXF_Types.h"
#include "RXF_Task.h"
#include "RXF_EventQueue.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    class Reactive;
    
    // This class acts as an interface between an active class in the UML model and an RTOS task.
    class Active : public Task {
    public :
    
        // Satisfies requirement 2846: Active - Initialization
        // An Active class shall be initialized with name, priority, stack size, queue size and queue memory.
        // 
        Active(const RXF::char_t* const name, Priority::Type const a_priority, Task::StackSize const stackSize, const std::uint32_t queueSize, Event** const queueMemory);
        
        // Satisfies requirement 3696: Active - Destruction
        // An Active class shall be deletable from another task context.
        // 
        virtual ~Active(void);
        
        // Satisfies requirement 2884: Active - Queue Full
        // An Active class shall call an error handler when an event is put into a full queue.
        // 
        // Satisfies requirement 211: Active - Event FIFO
        // An Active class shall be able to handle events in a FIFO manner in its own execution context.
        // 
        void queueEvent(Event* const event);
    
    private :
    
        // Satisfies requirement 211: Active - Event FIFO
        // An Active class shall be able to handle events in a FIFO manner in its own execution context.
        // 
        // Satisfies requirement 15: Active - Wait for Events
        // If an Active class has an empty message queue, the underlaying context shall wait for an event.
        // 
        Event* getQueuedEvent(void);
    
    protected :
    
        // Satisfies requirement 242: Active - Entrypoint
        // An Active class shall provide an execution loop as task entry point.
        // 
        virtual void execute(void);
    
    private :
    
        // Satisfies requirement 3705: Active - Destination Check
        // An Active class shall check if a queued event has a valid destination otherwise call an error handler.
        // 
        // Satisfies requirement 236: Active - Event Handling
        // Queued events shall be forwarded to the associated reactive destination.
        // 
        // Satisfies requirement 211: Active - Event FIFO
        // An Active class shall be able to handle events in a FIFO manner in its own execution context.
        // 
        void executeOnce(void);
    
    public :
    
        // Satisfies requirement 241: Active - Delete Events via Destination
        // Queued events shall be deletable via their associated reactive destination.
        // 
        void cancelEvents(const Reactive* const destination);
        
        // Satisfies requirement 179: Active - Remove Queued Timeout
        // A queued TimeoutEvent shall be removable from the depending EventQueue.
        // 
        void cancelTimeoutEvent(const TimeoutEvent* const timeoutEvent);
    
    private :
    
        void cancelEvents(void);
    
    public :
    
        // Satisfies requirement 3740: Active - Start Dispatching
        // An Active class shall be able to start handle events independant from the initialisation.
        // 
        void startDispatching(void);
        
        // Satisfies requirement 3695: Active - Self Termination
        // An Active class shall be able to be terminated from its own task context
        // 
        // Satisfies requirement 201: Active - Cleanup Queue on Termination
        // When an Active class is terminated or deleted, queued events shall be cleaned up.
        // 
        // Satisfies requirement 50: Active - Terminate Task
        // An Active class shall be able to be terminated from another task context.
        // 
        virtual void endDispatching(void);
        
        // Satisfies requirement 50: Active - Terminate Task
        // An Active class shall be able to be terminated from another task context.
        // 
        // Satisfies requirement 3740: Active - Start Dispatching
        // An Active class shall be able to start handle events independant from the initialisation.
        // 
        inline bool isDispatching(void) const
        {
            return Task::isRunning();
        }
        
        // Satisfies requirement 211: Active - Event FIFO
        // An Active class shall be able to handle events in a FIFO manner in its own execution context.
        // 
        inline std::uint32_t getMaxQueueCount(void) const
        {
            return eventQueue.getMaxCount();
        }
        
        ////    Attributes    ////
    
    private :
    
        // Every active context owns a message queue to store events.
        EventQueue eventQueue;
        
        // Flag to store the information if the event queue is empty or not.
        bool waitingForSignal;
        
        ////    Relations and components    ////
        
        // Pointer to an event that is currently execute by a state machine in this active context.
        Event* currentEvent;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_Active.h
*********************************************************************/

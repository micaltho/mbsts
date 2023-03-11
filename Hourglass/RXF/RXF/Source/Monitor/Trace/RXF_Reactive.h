/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/Trace/RXF_Reactive.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Reactive_H
#define RXF_Reactive_H

#include "RXF_Monitor.h"
#include "IOxfEventSender.h"
#include "RXF_ReactiveMacros.h"
#include "RXF_TimeoutEvent.h"
#include "RXF_Macros.h"
namespace RXF {
    class Active;
    
    class Reactive : public IOxfEventSender {
    public :
    
        // 
        // Possible statuses regarding event consumption success.
        enum TakeEventStatus
        {
            eventNotConsumed = 0,
            eventConsumed = 1
        };
    
    private :
    
        inline bool isObjectFilterd(void) const
        {
            return (status & statusFiltered) == statusFiltered;
        }
    
    public :
    
        inline void setObjectFilterd(const bool b)
        {
            if ( b == true )
            {
            	status |= statusFiltered;
            }
            else
            {
            	status &= (~statusFiltered);
            }
        }
        
        virtual void getActiveState(Monitor::WSTMonitorStateType*, const std::uint8_t);
    
    protected :
    
        // Satisfies requirement 2887: Reactive - Handle Event
        // Reactive shall provide an operation to process an event, that returns from the queue.
        // 
        // Satisfies requirement 2891: Reactive - Infinite Null Transitions
        // Reactive shall detect cyclic null transitions and call the error handler in such a case.
        // 
        // Satisfies requirement 2890: Reactive - Run To Completion
        // Reactive shall fulfill the run to completion behaviour of a statechart.
        // 
        virtual void processEvent(const Event* const event);
        
        // Satisfies requirement 2894: Reactive - Cyclic Triggered Operations
        // Cyclic triggered operation calls shall be detected by Reactive and the error handler shall be called.
        // 
        // Satisfies requirement 2888: Reactive - Handle Triggered Operation
        // Reactive shall provide an operation to process a triggered operation.
        // 
        void handleTrigger(const Event* const event);
    
    private :
    
        // Satisfies requirement 2891: Reactive - Infinite Null Transitions
        // Reactive shall detect cyclic null transitions and call the error handler in such a case.
        // 
        // Satisfies requirement 2890: Reactive - Run To Completion
        // Reactive shall fulfill the run to completion behaviour of a statechart.
        // 
        void runToCompletion(void);
    
    public :
    
        virtual void send(Event* const event, void * source);
        
        // Satisfies requirement 2880: Reactive - Receive Event
        // Reactive shall provide an operation to receive an event, that should be queued and processed by this Reactive instance.
        // 
        virtual void send(Event* const event);
        
        // Default constructor for the state machine. It is only initializing data, not starting the state machine.
        // Satisfies requirement 2893: Reactive - Deletion
        // A dynamically allocated Reactive instance shall be deletable.
        // 
        // Satisfies requirement 3280: Reactive - Initial Run To Completion
        // Existing null transitions outgoing from the initial state shall be processed by the creating context.
        // 
        // Satisfies requirement 2890: Reactive - Run To Completion
        // Reactive shall fulfill the run to completion behaviour of a statechart.
        // 
        // Satisfies requirement 2892: Reactive - Restart Protection
        // A Reactive instance shall only start its behavior once. Every following start attempt shall call the error handler.
        // 
        // Satisfies requirement 2881: Reactive - Events Start Behavior
        // Reactive shall only start processing events after startBehavior() is called.
        // 
        // Satisfies requirement 3278: Reactive - Triggered Operations Start Be...
        // Reactive shall only start processing triggered operations after startBehavior() is called.
        // 
        Reactive(void);
        
        // Satisfies requirement 2893: Reactive - Deletion
        // A dynamically allocated Reactive instance shall be deletable.
        // 
        virtual ~Reactive(void);
    
    protected :
    
        // This operation will be overridden by generated Code and handles the state machine dependent event consumption.
        /* @MISRA_0-1-8=OFF ID-0002: Empty operation is needed for reactive builder classes which implement no statechart. */
        inline virtual void rootState_entDef(void)
        {
            // Nothing to do here. Operation will be overridden by generated Code.
        }
        /* @MISRA_0-1-8=ON (end of ID-0002) */
    
    public :
    
        // Satisfies requirement 3280: Reactive - Initial Run To Completion
        // Existing null transitions outgoing from the initial state shall be processed by the creating context.
        // 
        // Satisfies requirement 3278: Reactive - Triggered Operations Start Be...
        // Reactive shall only start processing triggered operations after startBehavior() is called.
        // 
        // Satisfies requirement 2892: Reactive - Restart Protection
        // A Reactive instance shall only start its behavior once. Every following start attempt shall call the error handler.
        // 
        // Satisfies requirement 2881: Reactive - Events Start Behavior
        // Reactive shall only start processing events after startBehavior() is called.
        // 
        virtual bool startBehavior(void);
    
    protected :
    
        // Satisfies requirement 3279: Reactive - Triggered Operation Stop Proc...
        // Reactive shall stop processing triggered operations when endBehavior() is called.
        // 
        // Satisfies requirement 2882: Reactive - Event Stop Processing
        // Reactive shall stop processing events when endBehavior() is called.
        // 
        void endBehavior(void);
    
    public :
    
        // Satisfies requirement 2887: Reactive - Handle Event
        // Reactive shall provide an operation to process an event, that returns from the queue.
        // 
        void handleEvent(const Event* const event);
    
    protected :
    
        // This operation will be overridden by generated state machine code.
        inline virtual TakeEventStatus rootState_processEvent(void)
        {
            // Nothing to do here. Operation will be overridden by generated Code.
            return eventNotConsumed;
        }
    
    private :
    
        // When not overridden by generated code, this operation will call the error handler with code "ERROR_REACTIVE_EVENT_NOT_CONSUMED". It  
        // is called when a state machine was not able to consume an event in processEvent().
        // Argument const Event* const event :
        // Pointer to the event that could not be handled.
        virtual void handleNotConsumed(const Event* const event);
    
    protected :
    
        // Increment null-transition counter.
        inline void pushNullTransition(void)
        {
            nullTransitionCount++;
        }
        
        // Decrement null-transition counter.
        void popNullTransition(void);
    
    private :
    
        // Returns true, if the nullTransitionCount is larger than 0, meaning there are outstanding null transitions to be taken.
        bool shouldCompleteRun(void) const;
    
    public :
    
        // Returns the state machine's current event.
        // Satisfies requirement 2887: Reactive - Handle Event
        // Reactive shall provide an operation to process an event, that returns from the queue.
        // 
        inline const Event* getCurrentEvent(void) const
        {
            return currentEvent;
        }
        
        // Returns the active task context of a reactive class in which events are executed.
        // Satisfies requirement 2880: Reactive - Receive Event
        // Reactive shall provide an operation to receive an event, that should be queued and processed by this Reactive instance.
        // 
        inline Active* getActiveContext(void) const
        {
            return activeContext;
        }
        
        // Set the active context which is used to execute events for a reactive object.
        // Satisfies requirement 2880: Reactive - Receive Event
        // Reactive shall provide an operation to receive an event, that should be queued and processed by this Reactive instance.
        // 
        void setActiveContext(Active* const context, bool const active);
        
        // Satisfies requirement 2893: Reactive - Deletion
        // A dynamically allocated Reactive instance shall be deletable.
        // 
        bool isActive(void) const;
    
    private :
    
        void setActive(bool const active);
    
    public :
    
        // Satisfies requirement 3278: Reactive - Triggered Operations Start Be...
        // Reactive shall only start processing triggered operations after startBehavior() is called.
        // 
        // Satisfies requirement 2881: Reactive - Events Start Behavior
        // Reactive shall only start processing events after startBehavior() is called.
        // 
        bool isBehaviorStarted(void) const;
    
    private :
    
        void setBehaviorStarted(void);
        
        ////    Attributes    ////
        
        // Used to count the number of null transitions (transitions that do not have a trigger).
        std::uint8_t nullTransitionCount;
        
        // Busy flag, set to true if the state machine is currently handling a triggered operation. It is used to detect recursive  
        // triggered operation calls.
        bool busy;
        
        // When a state chart has reached the termination connector, this flag is set to true and shall block processing of events.
        bool shouldTerminate;
        
        // Save the status if an reactive object is already started or is also an own active context.
        std::uint8_t status;
        
        // Mask to set / request if an reactive object has already been started.
        static const std::uint8_t statusBehaviorStarted;
        
        // Mask to set / request if an reactive object has an own active context from the status attribute.
        static const std::uint8_t statusActive;
        
        // Initial value for the attribute status.
        static const std::uint8_t statusInit;
        
        static const std::uint8_t statusFiltered;
        
        ////    Relations and components    ////
        
        // Pointer to the event currently handled by the state machine.
        const Event* currentEvent;
        
        Active* activeContext;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/Monitor/Trace/RXF_Reactive.h
*********************************************************************/

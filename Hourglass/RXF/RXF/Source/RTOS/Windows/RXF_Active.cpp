/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_Active.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Active.h"
#include "RXF_Reactive.h"
namespace RXF {
    void Active::queueEvent(Event* const event)
    {
        criticalSection.lock();
        
        bool eventQueued = eventQueue.put( event );
        
        if( waitingForSignal )
        {
        	waitingForSignal = false;
        	criticalSection.unlock();
        	
        	setSignal();
        }
        else
        {
        	criticalSection.unlock();	
        }
        
        if( !eventQueued )
        {
        	ErrorHandler::error( ERROR_ACTIVE_QUEUE_EVENT_FAILED, 0, true );
        }
    }
    
    Event* Active::getQueuedEvent(void)
    {
        criticalSection.lock();
        
        if( eventQueue.isEmpty() )
        {
        	waitingForSignal = true;
        	criticalSection.unlock();
        	
        	waitForSignal();
        	
        	criticalSection.lock();
        }
        
        Event* const event = eventQueue.get();
        
        criticalSection.unlock();
        
        return event;
    }
    
    void Active::cancelEvents(const Reactive* const destination)
    {
        criticalSection.lock();
        eventQueue.cancelEvents( destination );
        criticalSection.unlock();
    }
    
    void Active::cancelTimeoutEvent(const TimeoutEvent* const timeoutEvent)
    {
        criticalSection.lock();
        eventQueue.cancelTimeoutEvent( timeoutEvent );
        criticalSection.unlock();
    }
    
    void Active::cancelEvents(void)
    {
        while( !eventQueue.isEmpty() )
        {
        	criticalSection.lock();
        	const RXF::Event* const event = eventQueue.get();
        	criticalSection.unlock();
        	
        	event->destroy();
        }
    }
    
    Active::Active(const RXF::char_t* const name, Priority::Type const a_priority, Task::StackSize const stackSize, const std::uint32_t queueSize, Event** const queueMemory) : RXF::Task(name,a_priority,stackSize), eventQueue(queueMemory, queueSize), waitingForSignal(false), currentEvent(nullptr)
    {
    }
    
    Active::~Active(void)
    {
        cancelEvents();
    }
    
    void Active::execute(void)
    {
        while( isDispatching() )
        {
        	executeOnce();
        }
    }
    
    void Active::executeOnce(void)
    {
        currentEvent = getQueuedEvent();
        
        if( nullptr != currentEvent )
        {
        	if( nullptr != currentEvent->getDestination() )
        	{
        		currentEvent->getDestination()->handleEvent( currentEvent );
        	}
        	else
        	{
        		ErrorHandler::error( ERROR_REACTIVE_EVENT_DESTINATION_IS_NULL, 0, true );
        	}
        	
        	currentEvent->destroy();
        	currentEvent = nullptr;
        }
    }
    
    void Active::startDispatching(void)
    {
        Task::startTask();
    }
    
    void Active::endDispatching(void)
    {
        if( isRunning() )
        {  
        	cancelEvents();
        	Task::endTask();
        }
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/Windows/RXF_Active.cpp
*********************************************************************/

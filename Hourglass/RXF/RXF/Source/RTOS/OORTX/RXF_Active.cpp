/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/OORTX/RXF_Active.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Active.h"
#include "RXF_Config.h"
#include "RXF_CriticalSection.h"

/* @MISRA_0-0-0,0-0-0=OFF XD-0000:  */
#ifdef TARGET_DEBUGGING_ENABLED
/* @MISRA_0-0-0,0-0-0=ON (end of XD-0000) */
#include "RXF_Monitor.h"
#endif /* TARGET_DEBUGGING_ENABLED */

#include "RXF_Reactive.h"
namespace RXF {
    Active::Active(const std::uint32_t queueSize, Event** const queueMemory) : dispatching(true), eventQueue(queueMemory, queueSize)
    {
    }
    
    void Active::queueEvent(Event* const event)
    {
        CriticalSection criticalSection;
        
        criticalSection.lock();
        
        bool eventQueued = eventQueue.put( event );
        
        criticalSection.unlock();	
        
        
        if( !eventQueued )
        {
        	ErrorHandler::error( ERROR_ACTIVE_QUEUE_EVENT_FAILED, 0, true );
        }
    }
    
    inline Event* Active::getQueuedEvent(void)
    {
        CriticalSection criticalSection;
        
        criticalSection.lock();
        
        Event* const event = eventQueue.get();
        
        criticalSection.unlock();
        
        return event;
    }
    
    void Active::execute(void)
    {
        while( isDispatching() )
        {   
        	#ifdef TARGET_DEBUGGING_ENABLED
        	if( eventQueue.isEmpty())
        	{
        		// only execute monitor if message queue is empty
        		RXF::Monitor::getMonitor().executeOnceMon();
        		#ifdef FULL_ANIMATION
        		while( RXF::Monitor::getMonitor().getMonitorStopFlag() )
        		{
        			RXF::Monitor::getMonitor().executeOnceMon();
        		}
        		#endif /* FULL_ANIMATION */
        	}
        	#endif /* TARGET_DEBUGGING_ENABLED */
        
        	executeOnce();
        }
        
    }
    
    inline void Active::executeOnce(void)
    {
        RXF::Event* const event = getQueuedEvent();
        
        if( nullptr != event )
        {
        	if( nullptr != event->getDestination() )
        	{
        		event->getDestination()->handleEvent( event );
        	}
        	event->destroy();
        }
    }
    
    void Active::cancelEvents(const Reactive* const destination)
    {
        CriticalSection criticalSection;
        
        criticalSection.lock();
        eventQueue.cancelEvents( destination );
        criticalSection.unlock();
    }
    
    void Active::cancelTimeoutEvent(const TimeoutEvent* const timeoutEvent)
    {
        CriticalSection criticalSection;
        
        criticalSection.lock();
        eventQueue.cancelTimeoutEvent( timeoutEvent );
        criticalSection.unlock();
    }
    
    void Active::cancelEvents(void)
    {
        while( !eventQueue.isEmpty() )
        {
        	CriticalSection criticalSection;
        	
        	criticalSection.lock();
        	const RXF::Event* const event = eventQueue.get();
        	criticalSection.unlock();
        	
        	event->destroy();
        }
    }
    
    void Active::endDispatching(void)
    {
        dispatching = false;
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/OORTX/RXF_Active.cpp
*********************************************************************/

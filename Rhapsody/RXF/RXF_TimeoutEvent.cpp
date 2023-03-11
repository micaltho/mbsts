/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_TimeoutEvent.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_TimeoutEvent.h"
#include "RXF_Active.h"
#include "RXF_ErrorHandler.h"
#include "RXF_Reactive.h"
namespace RXF {
    TimeoutEvent::TimeoutEvent(Reactive* const aDestination) :  RXF::TimerCallback(),
      RXF::Timer( this ),
      RXF::Event( RXF::Event::TIMEOUT_EVENT_ID, false ),
      running(false)
    {
        setDestination(aDestination);
    }
    
    TimeoutEvent::~TimeoutEvent(void)
    {
        cancel( false );
    }
    
    void TimeoutEvent::start(const Timer::Time_t delay)
    {
        if( !running )
        {
        	running = true;
        	Timer::start( delay );
        }
        else
        {
        	// This Error can only happen, if something went wrong in code generation.
        	// Normally the generated code will always cancel an timeout event before starting it again.
        	ErrorHandler::error( ERROR_TIMEOUT_EVENT_RESTART_DETECTED, 0, true );
        }
    }
    
    void TimeoutEvent::cancel(const bool isCurrentEvent)
    {
        if( running )
        {
        	running = false;
        
        	// If is current event, event is already back from queue
        	// and does not need to be removed from busy list or event queue.
        	if( !isCurrentEvent )
        	{
        		const bool wasInBusyList = Timer::cancel();
        		
        		if ( !wasInBusyList )
        		{
        			getDestination()->getActiveContext()->cancelTimeoutEvent( this );
        		}
        	}
        }
    }
    
    void TimeoutEvent::onTimeout(void)
    {
        // When Timeout is expired, send TimeoutEvent to queue if it is still running
        if( running )
        {
        	getDestination()->send( this );
        }
    }
}

/*********************************************************************
	File Path	: ../Source/generic/RXF_TimeoutEvent.cpp
*********************************************************************/

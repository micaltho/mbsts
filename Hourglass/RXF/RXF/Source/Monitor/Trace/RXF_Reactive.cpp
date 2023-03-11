/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/Trace/RXF_Reactive.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Active.h"
#include "RXF_Config.h"
#include "RXF_MainTask.h"
#include "RXF_ErrorHandler.h"
#include "RXF_Reactive.h"
namespace RXF {
    const std::uint8_t Reactive::statusBehaviorStarted(0x01U);
    
    const std::uint8_t Reactive::statusActive(0x02U);
    
    const std::uint8_t Reactive::statusInit(0x00U);
    
    const std::uint8_t Reactive::statusFiltered(0x40U);
    
    void Reactive::getActiveState(Monitor::WSTMonitorStateType*, const std::uint8_t)
    {
    }
    
    void Reactive::processEvent(const Event* const event)
    {
        TakeEventStatus eventStatus = eventNotConsumed;
        
        if( !shouldTerminate )
        {    
        	currentEvent = event;
        	
        	if( !isObjectFilterd() )
        	{
        		Monitor::getMonitor().sendEventStart( const_cast<Event*>(event) );
        	}
        	
        	/* handle the event */
        	eventStatus = rootState_processEvent();
        	
        	/* handle runToCompletion() */
        	if ( shouldCompleteRun() )
        	{
        		runToCompletion(); 
        	}
        	
        	currentEvent = nullptr;
        }
        	
        /* notify unconsumed event */
        if ( eventNotConsumed == eventStatus )
        {   
        	handleNotConsumed( event );
        }
    }
    
    void Reactive::handleTrigger(const Event* const event)
    {
        if ( !busy )
        {
        	/* Protect from recursive triggered operation calls */
        	busy = true;
        	Event* nonConstEvent = const_cast<Event*>(event);
        	nonConstEvent->setDestination( this );
        	nonConstEvent->setSource( this );
        	processEvent(event);
        	
        	busy = false;
        }
        else
        {
        	ErrorHandler::error( ERROR_REACTIVE_RECURSIVE_TRIGGERED_OPERATION_CALL, 0, true );	
        }
    }
    
    void Reactive::runToCompletion(void)
    {
        std::uint_fast8_t nullStepCount = 0U;
        bool continueRun = true;
        
        /* creat local null event with default ID (NULL_EVENT_ID) */
        RXF::Event nullEvent( RXF::Event::NULL_EVENT_ID, false );
        
        /* @MISRA_7-5-2=OFF ID-0001: It is ensured that currentEvent is reset to nullptr before operation returns. */
        currentEvent = &nullEvent;
        /* @MISRA_7-5-2=ON (end of ID-0001) */
        
        /* If untriggered transitions are "hot" take them */
        while ( ( nullTransitionCount > 0U ) && continueRun )
        {
        	nullStepCount++;
        	if ( nullStepCount > REACTIVE_MAX_NULL_STEPS )
        	{
        		/* Found infinite loop */
        		ErrorHandler::error( ERROR_REACTIVE_INFINITE_NULL_TRANSITIONS, 0, true );       
        		continueRun = false;
        	}
        	else
        	{		
            	if( !isObjectFilterd() )
        		{
        			nullEvent.setDestination( this );
        			nullEvent.setSource( this );
        			Monitor::getMonitor().sendEventStart( &nullEvent );
        		}
        		if( eventNotConsumed == rootState_processEvent() )
        		{
        			/* No more null transitions to take */
        			continueRun = false;	
        		}
        	}
        }
        
        currentEvent = nullptr;
    }
    
    void Reactive::send(Event* const event, void * source)
    {
        if( nullptr != event)
        {
        	event->setSource( source );
        	event->setDestination(this);
        	activeContext->queueEvent( event );
        }
    }
    
    void Reactive::send(Event* const event)
    {
        if( nullptr != event)
        {
        	event->setSource( this );
        	event->setDestination(this);
        	activeContext->queueEvent( event );
        }
    }
    
    Reactive::Reactive(void) : nullTransitionCount(0U), busy(false), shouldTerminate(false), status(statusInit), currentEvent(nullptr), activeContext(RXF::MainTask::getInstance())
    {
    }
    
    Reactive::~Reactive(void)
    {
        shouldTerminate = true;
        activeContext->cancelEvents( this );
    }
    
    bool Reactive::startBehavior(void)
    {
        bool startSuccessful = false;
        
        /* start behavior only once */
        if ( !isBehaviorStarted() )
        {
        	setBehaviorStarted();
        	
        	startSuccessful = true;
        	
        	/* Protect from recursive triggered operation calls */
        	busy = true;	
        
        	rootState_entDef();
        	
        	/* This causes the runToCompletion() operation to be taken after the default transition. */
        	/* Outgoing null transitions from the initial state are taken immediately from the context, */
        	/* that calls startBehavior */
        	if( shouldCompleteRun() )
        	{
        		runToCompletion();
        	}
        	
        	busy = false;
        
        }
        else
        {
        	ErrorHandler::error( ERROR_REACTIVE_RESTART_DETECTED, 0, true );		
        }
        
        return startSuccessful;
    }
    
    void Reactive::endBehavior(void)
    {
        if( !shouldTerminate )
        {
        	shouldTerminate = true;
        	
        	if( isActive() )
        	{
        		activeContext->endDispatching();
        	}
        }
        
    }
    
    void Reactive::handleEvent(const Event* const event)
    {
        processEvent( event );
    }
    
    void Reactive::handleNotConsumed(const Event* const event)
    {
        ErrorHandler::error( ERROR_REACTIVE_EVENT_NOT_CONSUMED, event->getId(), true );
    }
    
    void Reactive::popNullTransition(void)
    {
        if ( nullTransitionCount > 0U )
        {
        	nullTransitionCount--;
        }
        else
        {
        	/* Found bug in code generation */
        	ErrorHandler::error( ERROR_REACTIVE_TOO_FEW_NULL_CONFIGS, 0, true );
        }
    }
    
    bool Reactive::shouldCompleteRun(void) const
    {
        return ( nullTransitionCount > 0U );
    }
    
    void Reactive::setActiveContext(Active* const context, bool const active)
    {
        if( nullptr != context )
        {
        	activeContext = context;
        	setActive( active );
        }
    }
    
    bool Reactive::isActive(void) const
    {
        return (status & statusActive) == statusActive;
    }
    
    void Reactive::setActive(bool const active)
    {
        if ( active == true )
        {
        	status |= statusActive;
        }
        else
        {
        	status &= static_cast<std::uint8_t>(~statusActive);
        }
    }
    
    bool Reactive::isBehaviorStarted(void) const
    {
        return (status & statusBehaviorStarted) == statusBehaviorStarted;
    }
    
    void Reactive::setBehaviorStarted(void)
    {
        status |= statusBehaviorStarted;
    }
}

/*********************************************************************
	File Path	: ../Source/Monitor/Trace/RXF_Reactive.cpp
*********************************************************************/

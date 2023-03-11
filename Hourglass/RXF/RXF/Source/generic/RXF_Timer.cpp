/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_Timer.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_TimerCallback.h"
#include "RXF_Config.h"
#include "RXF_CriticalSection.h"
#include "RXF_ErrorHandler.h"
#include "RXF_Timer.h"
namespace RXF {
    Timer::Timer(TimerCallback* const aHandler) : remainingTicks(0U), handler(aHandler), next(nullptr), prev(nullptr)
    {
    }
    
    Timer::~Timer(void)
    {
        // If Timer is still in busyList when deleted, remove it to prevent busy list from getting corrupted.
        if( ( nullptr != prev ) || ( busyList == this ) )
        {
        	// return value of removeFromBusyList is not needed here
        	(void) removeFromBusyList();
        }
    }
    
    void Timer::start(const Timer::Time_t delay)
    {
        // Check if timer is already started
        if( ( nullptr == prev ) && ( busyList != this ) )
        {
        	remainingTicks = timeToTicks( delay );
        	
        	if( 0U == remainingTicks )
        	{
        		handler->onTimeout();
        	}
        	else
        	{
        		addToBusyList();
        	}
        }
        else
        {
        	// This Error can only happen, if something went wrong in code generation.
        	// Normally the generated code will always cancel an timer before starting it again.
        	ErrorHandler::error( ERROR_TIMER_RESTART_DETECTED, 0, true );
        }
    }
    
    bool Timer::cancel(void)
    {
        return removeFromBusyList();
    }
    
    Timer* Timer::getExpiredTimeout(void)
    {
        CriticalSection criticalSection;
        
        Timer* timeout = nullptr;
        
        criticalSection.lock();
        	 	
        if( ( nullptr != busyList ) && ( 0U == busyList->remainingTicks ) )
        {
        	timeout = busyList;
        	busyList = busyList->next;
        	
        	timeout->next = nullptr;
        	
        	if(  nullptr != busyList )
        	{
        		busyList->prev = nullptr;
        	}
        }
        
        criticalSection.unlock();
        
        return timeout;
    }
    
    void Timer::addToBusyList(void)
    {
        CriticalSection criticalSection;
        criticalSection.lock();
        
        /* List is empty, this timeout will be the new first element. */
        if ( nullptr == busyList )
        {
        	busyList = this;
        	
        	/* 	The list was empty so we place it in the list.
           		
           		Before: ->nullptr
        		New:    [150]
        		After:  [150]->nullptr
        	*/
        }
        else
        {
        	/* Check if the new element must be placed before the first in the busy list. */
        	if ( busyList->remainingTicks >= remainingTicks )
        	{
        		next = busyList;
        		busyList = this;
        	
        		/* 	The next elements time must be decreased with the new elements time.
        		    In that way we store the time relative.
        		   
        		   	Before: [100]->[100]->[25]->nullptr
        		  	New:    [50]
        		   	After:  [50]->[50]->[100]->[25]->nullptr
        		*/
        	}
        	/* No it must be after the first element. Now we only have to walk across the list. */
        	else
        	{
        		Timer* p = busyList;
        	
        		/* Since we store the time relative we must subtract the first element's time
        		   from the new elements time. */
        		remainingTicks -= p->remainingTicks;
        	
        		while ( ( nullptr != p->next ) && ( remainingTicks > p->next->remainingTicks ) )
        		{
        			remainingTicks -= p->next->remainingTicks;
        			p = p->next;
        		}
        	
        		/* We found the element where we place the new one after.
        		   This can be the last, the last element's next pointer is nullptr
        		   but we can handle that.
        		*/
        		prev = p;
        		next = p->next;
        		p->next = this;
        		
        		/* The next elements time must be decreased with the new elements time.
        		   In that way we store the time relative.
        	
        		   Before: [100]->[100]->[25]->nullptr
        		   New:    [150]
        		   After:  [100]->[50]->[50]->[25]->nullptr
        		 */
        	}
        		
        	if ( nullptr != next )
        	{
        		/*	Adjust remaining ticks of next timer when there is a next timer. */
        		next->remainingTicks -= remainingTicks;
                
                /* Complete the backlink of the list. If this is not done, stop() will corrupt the List. */ 
        		next->prev = this;
        	}
        }
        
        criticalSection.unlock();
    }
    
    bool Timer::removeFromBusyList(void)
    {
        CriticalSection criticalSection;
        criticalSection.lock();
        
        bool removed = true;
        
        if( this == busyList )
        {
        	busyList = next;
        }
        else if( nullptr != prev )
        {
        	prev->next = next;
        }
        else
        {
        	removed = false;
        }
        if( nullptr != next )
        {
        	next->remainingTicks += remainingTicks;
        	next->prev = prev;
        	next = nullptr;
        }
        prev = nullptr;
        
        remainingTicks = 0U;
        
        criticalSection.unlock();
        
        return removed;
    }
    
    void Timer::processTimeouts(void)
    {
        if ( nullptr != busyList )
        {   
        	/* Update busyList and processedTicks to new tick value. */
        	busyList->remainingTicks--;
        	
        	Timer* timeout = getExpiredTimeout();
        	
        	while( nullptr != timeout )
        	{  
        		//handler is always != nullptr ensured by code generation 
        		timeout->handler->onTimeout();
        		
        		timeout = getExpiredTimeout();
        	}
        }
    }
    
    Timer::Ticks_t Timer::timeToTicks(Timer::Time_t const time)
    {
        return ( ( time + MS_PER_TICK ) - 1U ) / MS_PER_TICK;
    }
    
    RXF::Timer* Timer::busyList(nullptr);
}

/*********************************************************************
	File Path	: ../Source/generic/RXF_Timer.cpp
*********************************************************************/

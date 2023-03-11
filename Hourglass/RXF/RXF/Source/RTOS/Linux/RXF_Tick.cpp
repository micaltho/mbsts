/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Linux/RXF_Tick.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include <RXF_ErrorHandler.h>
#include <RXF_Config.h>
#include <RXF_Tick.h>
namespace RXF {
    int_t Tick::fd(0);
    
    Tick Tick::instance;
    
    std::uint32_t Tick::ticks(0U);
    
    void Tick::init(void)
    {
        int_t errorStatus = 0;
        
        struct itimerspec new_value;
        
        new_value.it_value.tv_sec  = MS_PER_TICK / 1000;
        new_value.it_value.tv_nsec = ( MS_PER_TICK % 1000 ) * 1000 * 1000;
        new_value.it_interval.tv_sec  = MS_PER_TICK / 1000;
        new_value.it_interval.tv_nsec = ( MS_PER_TICK % 1000 ) * 1000 * 1000;
        
        fd = timerfd_create( CLOCK_REALTIME, 0 );
        
        errorStatus = timerfd_settime( fd, 0, &new_value, nullptr );
        
        if( errorStatus != 0 )
        {
        	ErrorHandler::error( RXF::ERROR_TICK_INIT_FAILED, errno, true );
        }
        
        instance.startTask();
    }
    
    void Tick::cleanup(void)
    {
        instance.endTask();
    }
    
    void Tick::execute(void)
    {
        struct pollfd ufds = {0,0,0};
        int32_t read_fds = 0;
        ssize_t s;
        uint64_t exp;
        
        while( isRunning() )
        {
        	(void) pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr );
        	pthread_testcancel();
        	(void) pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr );
        
        	memset(&ufds, 0, sizeof(struct pollfd));
        	ufds.fd = fd;
        	ufds.events = POLLIN;
        
        	read_fds = poll(&ufds, 1UL, 1);
        
        	if( read_fds > 0 )
        	{
        		if ( ufds.revents & POLLIN )
        		{
        			s = read( ufds.fd, &exp, sizeof(uint64_t) );
        
        			if ( s == static_cast<ssize_t>( sizeof(uint64_t) ) )
        			{
        				tick();
        			}
        		}
        	}
        }
    }
    
    Tick::Tick(void) : RXF::Task( "RXF Timer Task", TIMER_TASK_PRIORITY, TIMER_TASK_STACK_SIZE )
    {
    }
    
    void Tick::tick(void)
    {
        ticks++;
        Timer::processTimeouts();
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/Linux/RXF_Tick.cpp
*********************************************************************/

/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/OORTX/RXF_Active.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Active_H
#define RXF_Active_H

#include "RXF_ErrorHandler.h"
#include "RXF_EventQueue.h"
namespace RXF {
    class Reactive;
    
    class Active {
    protected :
    
        Active(const std::uint32_t queueSize, Event** const queueMemory);
    
    public :
    
        // Needs to be implemented in RTOS adaptation.
        void queueEvent(Event* const event);
    
    private :
    
        // Needs to be implemented in RTOS adaptation.
        inline Event* getQueuedEvent(void);
    
    protected :
    
        // Only MainTask calls this function after initializing the Framework. Start scheduling.
        virtual void execute(void);
    
    private :
    
        inline void executeOnce(void);
    
    public :
    
        void cancelEvents(const Reactive* const destination);
        
        void cancelTimeoutEvent(const TimeoutEvent* const timeoutEvent);
    
    private :
    
        void cancelEvents(void);
    
    public :
    
        virtual void endDispatching(void);
    
    protected :
    
        inline bool isDispatching(void) const
        {
            return dispatching;
        }
    
    public :
    
        inline std::uint32_t getMaxQueueCount(void) const
        {
            return eventQueue.getMaxCount();
        }
        
        ////    Attributes    ////
    
    private :
    
        bool dispatching;
        
        EventQueue eventQueue;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/OORTX/RXF_Active.h
*********************************************************************/

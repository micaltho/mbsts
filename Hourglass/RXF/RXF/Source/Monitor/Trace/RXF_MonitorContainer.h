/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/Trace/RXF_MonitorContainer.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MonitorContainer_H
#define RXF_MonitorContainer_H

#include "RXF_Event.h"
namespace RXF {
    class WSTMonitorTraceEvent {
    public :
    
        inline WSTMonitorTraceEvent(const void * source, const Reactive* const destination, const Event::Id_t id, const std::uint8_t currentTick) : source(source), destination(destination), id(id), currentTick(currentTick)
        {
        }
        
        inline Monitor::WSTMonitorStateType* getCurrentState(void)
        {
            return currentState;
        }
        
        ////    Attributes    ////
    
    private :
    
        const void * source;
        
        const Reactive* destination;
        
        std::int16_t id;
        
        std::uint8_t currentTick;
        
        Monitor::WSTMonitorStateType currentState[MON_MAX_PARALLEL_STATES];
        
        #define MONITOR_TRACE_EVENT_CONTENT_SIZE static_cast<uint8_t>( sizeof(void*) + sizeof(void*) + sizeof(uint8_t) + sizeof(uint16_t) + MON_MAX_PARALLEL_STATES )
    };
    
    class WSTMonitorTraceTimeout {
    public :
    
        inline WSTMonitorTraceTimeout(const Reactive* const destination, const std::uint8_t currentTick) : destination(destination), currentTick(currentTick)
        {
        }
        
        inline Monitor::WSTMonitorStateType* getCurrentState(void)
        {
            return currentState;
        }
        
        ////    Attributes    ////
    
    private :
    
        const Reactive* destination;
        
        std::uint8_t currentTick;
        
        Monitor::WSTMonitorStateType currentState[MON_MAX_PARALLEL_STATES];
        
        #define MONITOR_TRACE_TIMEOUT_CONTENT_SIZE static_cast<uint8_t>( sizeof(void*) + sizeof(uint8_t) + MON_MAX_PARALLEL_STATES )
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/Monitor/Trace/RXF_MonitorContainer.h
*********************************************************************/

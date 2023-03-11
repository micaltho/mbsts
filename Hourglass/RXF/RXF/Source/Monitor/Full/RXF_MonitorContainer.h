/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Monitor/Full/RXF_MonitorContainer.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MonitorContainer_H
#define RXF_MonitorContainer_H

#include "RXF_MemoryPool.h"
#include "RXF_ErrorHandler.h"
#include "RXF_Event.h"
namespace RXF {
    class WSTMonitorEventCreate {
    public :
    
        inline WSTMonitorEventCreate(const std::uint16_t p_eventID, const void* const p_source, const Reactive* const p_destination, const std::int16_t p_id, const std::uint8_t p_currentTick) : source( p_source ), destination( p_destination ), eventID( p_eventID ), id( p_id ), currentTick( p_currentTick ) 
        {
        }
        
        ////    Attributes    ////
    
    private :
    
        const void* source;
        
        const Reactive* destination;
        
        const std::uint16_t eventID;
        
        const std::int16_t id;
        
        const std::uint8_t currentTick;
        
        #define MONITOR_EVENT_CREATE_CONTENT_SIZE static_cast<uint8_t>( sizeof(void*) + sizeof(void*) + sizeof(uint16_t) + sizeof(uint16_t) + sizeof(uint8_t) )
    };
    
    class WSTMonitorEventEnd {
    public :
    
        explicit inline WSTMonitorEventEnd(const std::uint16_t eventID) : eventID(eventID)
        {
        }
        
        inline Monitor::WSTMonitorStateType* getCurrentState(void)
        {
            return currentState;
        }
        
        ////    Attributes    ////
    
    private :
    
        std::uint16_t eventID;
        
        Monitor::WSTMonitorStateType currentState[MON_MAX_PARALLEL_STATES];
        
        #define MONITOR_EVENT_END_CONTENT_SIZE static_cast<uint8_t>( sizeof(uint16_t) + MON_MAX_PARALLEL_STATES )
    };
    
    class WSTMonitorEventStart {
    public :
    
        inline WSTMonitorEventStart(const std::uint16_t eventID, const std::uint8_t currentTick) : eventID(eventID), currentTick(currentTick)
        {
        }
        
        ////    Attributes    ////
    
    private :
    
        std::uint16_t eventID;
        
        std::uint8_t currentTick;
        
        #define MONITOR_EVENT_START_CONTENT_SIZE static_cast<uint8_t>( sizeof(uint16_t) + sizeof(uint8_t) )
    };
    
    class WSTMonitorTimeout {
    public :
    
        inline WSTMonitorTimeout(void * destination, const std::uint16_t eventID, const std::uint8_t currentTick) : destination(destination),eventID(eventID),currentTick(currentTick)
        {
        }
        
        ////    Attributes    ////
    
    private :
    
        void* destination;
        
        std::uint16_t eventID;
        
        std::uint8_t currentTick;
        
        #define MONITOR_EVENT_TIMEOUT_CONTENT_SIZE static_cast<uint8_t>( sizeof(void*) + sizeof(uint16_t) + sizeof(uint8_t) )
    };
    
    class WSTMonitorEventWithParams : public Event {
    public :
    
        /* @MISRA_2-10-2=OFF XD-0001: Operation hides new operation from RXF::Event. */
        inline static void * operator new(const std::size_t objectSize)
        {
            void* memory = MEM_injectEventPool.alloc( objectSize );
            
            if( nullptr == memory )
            {
            	ErrorHandler::error( ERROR_MEMORY_POOL_ALLOC_FAILED, 0, false );
            }
            
            return memory;
        }
        /* @MISRA_2-10-2=ON (end of XD-0001) */
        
        /* @MISRA_2-10-2=OFF XD-0000: Operation hides new operation from RXF::Event. This is needed because Injected Events need an own memory pool. */
        inline static void operator delete(void * const memory)
        {
            (void)MEM_injectEventPool.freeMemory( memory );
        }
        /* @MISRA_2-10-2=ON (end of XD-0000) */
        
        inline WSTMonitorEventWithParams(Reactive* const destination, const Event::Id_t id)
        {
            setDestination(destination);
            setId(id);
        }
        
        ////    Attributes    ////
    
    private :
    
        static MemoryPool<MON_INJECT_EVT_COUNT, sizeof( RXF::Event ) + MON_INJECT_EVT_PARAMETER_SIZE> MEM_injectEventPool;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/Monitor/Full/RXF_MonitorContainer.h
*********************************************************************/

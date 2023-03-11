/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_Event.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Event_H
#define RXF_Event_H

#include <cstdint>
#include <cstddef>
namespace RXF {
    class Reactive;
    
    // This class represents the base class for every event (user events and timeout events).
    // 
    // Events are asynchronous messages which are handled by the RXF event based scheduler. Usually events are dynamically  
    // allocated and freed (via static memory pools), but also static events which do not get destroyed are supported. They can  
    // be used when events are being generated from an interrupt service routine.
    class Event {
    public :
    
        // Type for event IDs.
        typedef std::int32_t Id_t;
        
        // Identifiers for special default events
        enum DefaultEventIds
        {
            NULL_EVENT_ID = -1, // Event ID used for NULL-events (used to handle NULL-transisions).
            TIMEOUT_EVENT_ID = -2 // Event ID used for timeout events.
        };
        
        // Argument const Id_t aId = 0 :
        // Identifier of the event.
        // Satisfies requirement 2843: Event - Identifier
        // An Event shall be able to be identified by an id.
        // 
        // Satisfies requirement 2845: Event - Default Deletion
        // The Event module shall provide a mechanism to identify whether an Event object is statically or dynamically allocated.
        // 
        explicit inline Event(const Id_t aId = 0, const bool aDeleteAfterConsume = true) : id(aId), deleteAfterConsume(aDeleteAfterConsume), destination(nullptr)
        {
        }
        
        // Satisfies requirement 2843: Event - Identifier
        // An Event shall be able to be identified by an id.
        // 
        inline Id_t getId(void) const
        {
            return id;
        }
        
        // Returns the event identifier.
        // Satisfies requirement 2843: Event - Identifier
        // An Event shall be able to be identified by an id.
        // 
        inline void setId(const Id_t aId)
        {
            id = aId;
        }
    
    protected :
    
        // Decide if an event shall be destroyed after it has been consumed by a state machine. True for dynamic events, false for static events.
        // Satisfies requirement 2845: Event - Default Deletion
        // The Event module shall provide a mechanism to identify whether an Event object is statically or dynamically allocated.
        // 
        // Satisfies requirement 2844: Event - Destruction Operation
        // After event consumption the Event object's memory shall be freed, if it was dynamically allocated. Static Event objects shall not be destroyed.
        // 
        inline void setDeleteAfterConsume(const bool aDeleteAfterConsume)
        {
            deleteAfterConsume = aDeleteAfterConsume;
        }
    
    public :
    
        // Returns the destination state machine pointer.
        // Satisfies requirement 17: Event - Reactive Destination
        // Every Event shall store a reactive destination.
        // 
        inline Reactive* getDestination(void) const
        {
            return destination;
        }
        
        // Returns the destination state machine pointer.
        // Satisfies requirement 17: Event - Reactive Destination
        // Every Event shall store a reactive destination.
        // 
        inline void setDestination(Reactive* const aDestination)
        {
            destination = aDestination;
        }
        
        // Satisfies requirement 2845: Event - Default Deletion
        // The Event module shall provide a mechanism to identify whether an Event object is statically or dynamically allocated.
        // 
        // Satisfies requirement 2844: Event - Destruction Operation
        // After event consumption the Event object's memory shall be freed, if it was dynamically allocated. Static Event objects shall not be destroyed.
        // 
        void destroy(void) const;
        
        // Satisfies requirement 170: Event - Different Memory Pools Sizes
        // The used event memory management shall handle different event sizes to optimize the memory usage.
        // 
        // Satisfies requirement 231: Event - Memory Pool
        // Every dynamically allocated Event shall be allocated from MemoryPools to avoid the use of the heap.
        // 
        static void * operator new(const std::size_t objectSize);
        
        // Satisfies requirement 43: Event - Memory Deallocation
        // Memory of destroyed events shall be returned to the associated MemoryPool.
        // 
        // Satisfies requirement 170: Event - Different Memory Pools Sizes
        // The used event memory management shall handle different event sizes to optimize the memory usage.
        // 
        // Satisfies requirement 231: Event - Memory Pool
        // Every dynamically allocated Event shall be allocated from MemoryPools to avoid the use of the heap.
        // 
        static void operator delete(void * const memory);
        
        inline virtual ~Event(void)
        {
            destination = nullptr;
        }
        
        ////    Attributes    ////
    
    private :
    
        // Identifier of the event. The name of the attribute is specified by the Rhapsody code generator interface.
        Id_t id;
        
        bool deleteAfterConsume;
        
        ////    Relations and components    ////
        
        // Pointer to the state machine object that shall receive the event.
        Reactive* destination;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_Event.h
*********************************************************************/

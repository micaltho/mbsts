/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_EventQueue.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_EventQueue_H
#define RXF_EventQueue_H

#include "RXF_TimeoutEvent.h"
namespace RXF {
    // Message queue class, managing a linked list of queued events.
    class EventQueue {
    public :
    
        // Satisfies requirement 122: EventQueue - Valid Initialisation
        // An EventQueue shall be initilized with valid memory on creation.
        // 
        EventQueue(Event** const queueMemory, const std::uint32_t queueSize);
        
        // Satisfies requirement 38: EventQueue - Empty Check
        // It shall be possible to check if an EventQueue is empty.
        // 
        bool isEmpty(void) const;
    
    private :
    
        // Returns true, if the EventQueue is full.
        bool isFull(void) const;
    
    public :
    
        // Satisfies requirement 2885: EventQueue - High Water Marks
        // An EventQueue shall be able to record the maximum count of events that have been inside the queue at the same time.
        // 
        // Satisfies requirement 193: EventQueue - FIFO Behaviour
        // An EventQueue shall be able to handle events in a FIFO manner.
        // 
        bool put(Event* const event);
        
        // Satisfies requirement 2885: EventQueue - High Water Marks
        // An EventQueue shall be able to record the maximum count of events that have been inside the queue at the same time.
        // 
        // Satisfies requirement 193: EventQueue - FIFO Behaviour
        // An EventQueue shall be able to handle events in a FIFO manner.
        // 
        Event* get(void);
        
        // Satisfies requirement 163: EventQueue - Cancel Event via Destination
        // It shall be possible to cancel queued events via their associated reactive destination.
        // 
        void cancelEvents(const Reactive* const destination);
        
        // Satisfies requirement 49: EventQueue- Remove Queued Timeout
        // A queued timeout event shall be removable.
        // 
        void cancelTimeoutEvent(const TimeoutEvent* const timeoutEvent);
    
    private :
    
        // Removes all events from the queue and destroys the events.
        void cleanUp(void);
    
    public :
    
        // Get the maximum number of events that has beem inside the queue at the same time.
        // Satisfies requirement 2885: EventQueue - High Water Marks
        // An EventQueue shall be able to record the maximum count of events that have been inside the queue at the same time.
        // 
        inline std::uint32_t getMaxCount(void) const
        {
            return maxCount;
        }
        
        ////    Attributes    ////
    
    private :
    
        // Pointer to an array of event pointer which is needed to queue events.
        Event** queue;
        
        // Maximum count of events that can be queued.
        const std::uint32_t size;
        
        // Number of events that are currently inside an event queue.
        std::uint32_t count;
        
        // Maximum count of blocks that had been in use (high water mark).
        std::uint32_t maxCount;
        
        // Head pointer for the message queue, pointing to the first queued event.
        std::uint32_t head;
        
        // Tail pointer for the message queue, pointing to the last queued event.
        std::uint32_t tail;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_EventQueue.h
*********************************************************************/

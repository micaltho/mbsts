/* This file is auto generated from Rhapsody do not edit! */

#ifndef RXF_EVENT_POOLS_H
#define RXF_EVENT_POOLS_H

#include "RXF_Event.h"
#include "RXF_MemoryPool.h"

namespace RXF {

	
	extern RXF::MemoryPool<64U,sizeof(RXF::Event)> memoryPool_Event_default;
	
	
	extern RXF::MemoryPool<32U,sizeof(RXF::Event) + 4U> memoryPool_Event_small;
	
	
	extern RXF::MemoryPool<32U,sizeof(RXF::Event) + 8U> memoryPool_Event_medium;
	
	
	extern RXF::MemoryPool<16U,sizeof(RXF::Event) + 16U> memoryPool_Event_large;

}

#endif /* RXF_EVENT_POOLS_H */

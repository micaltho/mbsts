/* This file is auto generated from Rhapsody do not edit! */

#include "RXF_Event_Pools.h"
#include "RXF_ErrorHandler.h"

namespace RXF {

	

	
	RXF::MemoryPool<64U,sizeof(RXF::Event)> memoryPool_Event_default;

	
	RXF::MemoryPool<32U,sizeof(RXF::Event) + 4U> memoryPool_Event_small;

	
	RXF::MemoryPool<32U,sizeof(RXF::Event) + 8U> memoryPool_Event_medium;
	
	
	RXF::MemoryPool<16U,sizeof(RXF::Event) + 16U> memoryPool_Event_large;

	void * RXF::Event::operator new(const std::size_t objectSize)
	{
		void* memory = memoryPool_Event_default.alloc( objectSize );
		if( NULL == memory )
		{
			memory = memoryPool_Event_small.alloc( objectSize );
			if( NULL == memory )
			{
				memory = memoryPool_Event_medium.alloc( objectSize );
				if( NULL == memory )
				{
					memory = memoryPool_Event_large.alloc( objectSize );
					if( NULL == memory )
					{
							RXF::ErrorHandler::error( RXF::ERROR_MEMORY_POOL_ALLOC_FAILED, 0, false );
					}
				}
			}
		}
		
		return memory;
	}

	void RXF::Event::operator delete(void * const memory)
	{
		if( memoryPool_Event_default.freeMemory( memory ) ) { }
		else if( memoryPool_Event_small.freeMemory( memory ) ) { }
		else if( memoryPool_Event_medium.freeMemory( memory ) ) { }
		else if( memoryPool_Event_large.freeMemory( memory ) ) { }
		else
		{
			RXF::ErrorHandler::error( RXF::ERROR_MEMORY_POOL_FREE_FAILED, 0, false );
		}
	}

}

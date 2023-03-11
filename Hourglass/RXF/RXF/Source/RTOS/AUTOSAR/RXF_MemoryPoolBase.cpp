/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/AUTOSAR/RXF_MemoryPoolBase.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_MemoryPoolBase.h"
namespace RXF {
    void * MemoryPoolBase::alloc(const std::size_t aSize)
    {
        void * memory = nullptr;
        
        if(aSize <= size)
        {   
        	criticalSection.lock();
        	
        	if( nullptr != freeList)
        	{   
        		memory = freeList;
        		/* @MISRA_5-2-8=OFF ID-0004: Cast from pointer to pointer required for efficient memory pool implementation. */
        		freeList = *static_cast<void **>(memory);
        		/* @MISRA_5-2-8=ON (end of ID-0004) */
        		
        		count++;
        		
        		if( count > maxCount )
        		{
        			maxCount = count;
        		}	
        	}
        	
        	criticalSection.unlock();	
        }
        
        return memory;
    }
    
    bool MemoryPoolBase::freeMemory(void * const memory)
    {
        bool success = false;
        
        if( ( memory >= firstBlock ) && ( memory <= lastBlock ) )
        {
        	criticalSection.lock();
        	
        	/* @MISRA_5-2-8=OFF ID-0004: Cast from pointer to pointer required for efficient memory pool implementation. */
        	*static_cast<void **>(memory) = freeList;
        	/* @MISRA_5-2-8=ON (end of ID-0004) */
        	freeList = memory;
        		
        	count--;
        	
        	criticalSection.unlock(); 
        	
        	success = true;
        }
        
        return success;
    }
    
    MemoryPoolBase::MemoryPoolBase(const std::size_t aSize, void * const aFirstBlock, const void * const aLastBlock) : count(0U), firstBlock(aFirstBlock), freeList(aFirstBlock), lastBlock(aLastBlock), maxCount(0U), size(aSize)
    {
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/AUTOSAR/RXF_MemoryPoolBase.cpp
*********************************************************************/

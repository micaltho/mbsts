/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_MemoryPoolBase.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_CriticalSection.h"
#include "RXF_MemoryPoolBase.h"
namespace RXF {
    MemoryPoolBase::MemoryPoolBase(const std::size_t aSize, void * const aFirstBlock, const void * const aLastBlock) : size(aSize), firstBlock(aFirstBlock), lastBlock(aLastBlock), count(0U), maxCount(0U), freeList(aFirstBlock)
    {
    }
    
    void * MemoryPoolBase::alloc(const std::size_t aSize)
    {
        void * memory = nullptr;
        
        if(aSize <= size)
        {   
        	CriticalSection criticalSection;    
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
        
        if( isMemoryInPool( memory ) )
        {
        	CriticalSection criticalSection;
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
}

/*********************************************************************
	File Path	: ../Source/generic/RXF_MemoryPoolBase.cpp
*********************************************************************/

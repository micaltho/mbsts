/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/AUTOSAR/RXF_MemoryPoolBase.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MemoryPoolBase_H
#define RXF_MemoryPoolBase_H

#include "RXF_Mutex.h"
#include <cstddef>
#include <cstdint>
namespace RXF {
    class MemoryPoolBase {
    public :
    
        // Satisfies requirement 2840: MemoryPool - High Water Mark
        // A MemoryPool shall store the maximum count of parallel used blocks for debugging purposes.
        // 
        // Satisfies requirement 164: MemoryPool - No Blocks Available
        // A MemoryPool shall return NULL if no more free blocks are available.
        // 
        // Satisfies requirement 167: MemoryPool - Allocate by Size
        // A MemoryPool shall provide valid memory if the requested size <= defined block size of the MemoryPool.
        // 
        // Satisfies requirement 2839: MemoryPool - Invalid Memory Allocation
        // A MemoryPool shall return NULL if the requested size is larger than the defined block size of the MemoryPool.
        // 
        void * alloc(const std::size_t aSize);
        
        // Satisfies requirement 2842: MemoryPool - Release Information
        // The MemoryPool shall provide information whether a block was released successfully or not.
        // 
        // Satisfies requirement 2841: MemoryPool - Release Block
        // A MemoryPool shall be able to take back a previously allocated block from the pool.
        // 
        // Satisfies requirement 2840: MemoryPool - High Water Mark
        // A MemoryPool shall store the maximum count of parallel used blocks for debugging purposes.
        // 
        bool freeMemory(void * const memory);
    
    protected :
    
        // Argument const size_t aSize :
        // Size of a block in bytes.
        // Argument void * const aFirstBlock :
        // Pointer to the first block in the memory pool.
        // Argument const void * const aLastBlock :
        // Pointer to the last block in the memory pool.
        // Satisfies requirement 2840: MemoryPool - High Water Mark
        // A MemoryPool shall store the maximum count of parallel used blocks for debugging purposes.
        // 
        // Satisfies requirement 129: MemoryPool - Initialisation
        // A MemoryPool shall be initializable by a given block size and block count.
        // 
        MemoryPoolBase(const std::size_t aSize, void * const aFirstBlock, const void * const aLastBlock);
    
    public :
    
        // Satisfies requirement 2841: MemoryPool - Release Block
        // A MemoryPool shall be able to take back a previously allocated block from the pool.
        // 
        inline bool isMemoryInPool(const void * const memory) const;
        
        // Satisfies requirement 2840: MemoryPool - High Water Mark
        // A MemoryPool shall store the maximum count of parallel used blocks for debugging purposes.
        // 
        inline std::uint32_t getMaxCount(void) const
        {
            return maxCount;
        }
        
        ////    Attributes    ////
    
    private :
    
        // Count of blocks currently in use.
        std::uint32_t count;
        
        // Pointer to the first block in a pool.
        const void * firstBlock;
        
        // Pointer to the first free block.
        void * freeList;
        
        // Pointer to the last block in a pool.
        const void * lastBlock;
        
        // Maximum count of blocks that had been in use (high water mark).
        std::uint32_t maxCount;
        
        // Size of a memory block.
        const std::size_t size;
        
        ////    Relations and components    ////
        
        Mutex criticalSection;
    };
    
    inline bool MemoryPoolBase::isMemoryInPool(const void * const memory) const
    {
        return ( memory >= firstBlock ) && ( memory <= lastBlock );
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/AUTOSAR/RXF_MemoryPoolBase.h
*********************************************************************/

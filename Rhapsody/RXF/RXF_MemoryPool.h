/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_MemoryPool.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MemoryPool_H
#define RXF_MemoryPool_H

#include "RXF_MemoryPoolBase.h"
namespace RXF {
    // Template class providing memory to the MemoryPoolBase class.
    template <std::uint32_t COUNT, std::size_t SIZE> class MemoryPool : public MemoryPoolBase {
    public :
    
        // Satisfies requirement 129: MemoryPool - Initialisation
        // A MemoryPool shall be initializable by a given block size and block count.
        // 
        inline MemoryPool(void) : RXF::MemoryPoolBase( SIZE, &poolMemory[0][0], &poolMemory[COUNT-1U][0] )
        {
            // In the for loop the pool blocks are linked in a list.
            // The for loop is only executed if count > 1. With only 1 block there is nothing to link.
            // The break condition i < ( COUNT - 1U ) is written as ( i + 1U) < COUNT, because the first variant
            // throws a warning: pointless comparison of unsigned integer with zero for COUNT = 1
            
            for( std::uint32_t i = 0U; (i + 1U) < COUNT; i++ )
            {
            	poolMemory[i][0U] = &poolMemory[i+1U][0U];	
            }
                                        
            poolMemory[COUNT-1U][0U] = nullptr;
        }
        
        ////    Attributes    ////
    
    private :
    
        // The actual memory pool, containing <COUNT> times a block of <SIZE> bytes.
        void* poolMemory[ COUNT ][ ( ( SIZE + sizeof( void* ) ) -1U ) / sizeof( void* ) ];
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_MemoryPool.h
*********************************************************************/

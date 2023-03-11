/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/RXFContainersStatic/RXF_StaticMap.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_StaticMap_H
#define RXF_StaticMap_H

#include "RXF_Map.h"
namespace RXF {
    template <class Key, class T, std::uint32_t COUNT> class StaticMap : public Map<Key, T> {
    public :
    
        // Satisfies requirement 3925: Map - Empty Initialization
        // It shall be possible to create an empty Map in O(n) time, where n is the maximum number of Elements in the Map.
        // 
        // Satisfies requirement 3924: Map - Static Declaration
        // It shall be possible to create a Map with a given maximum size using pseudo-dynamic memory allocation.
        // 
        inline StaticMap(void) : Map<Key, T>(memoryPool)
        {
        }
        
        // Satisfies requirement 3924: Map - Static Declaration
        // It shall be possible to create a Map with a given maximum size using pseudo-dynamic memory allocation.
        // 
        // Satisfies requirement 3926: Map - Copy Creation
        // It shall be possible to create a copy of a given Map in O(n + m) time, where n is the maximum number of Elements in the Map and m is the number of Elements to copy.
        // 
        inline StaticMap(const StaticMap<Key, T, COUNT>& other) : Map<Key, T>(memoryPool)
        {
             Map<Key,T>::copy(other);
        }
        
        inline ~StaticMap(void)
        {
            Map<Key,T>::clear();
        }
        
        // Argument const StaticMap<Key,T,COUNT>& other :
        // The map to copy
        // Satisfies requirement 3938: Map - Compare
        // It shall be possible to compare two Maps for equality by comparing all Key-Value-Pairs for equality in O(n) time, where n is the number of Elements in the Map.
        // 
        inline bool operator==(const StaticMap<Key,T,COUNT>& other) const
        {
            return Map<Key,T>::operator==( other );
        }
        
        // Argument const StaticMap<Key,T,COUNT>& other :
        // The map to copy
        // Satisfies requirement 3938: Map - Compare
        // It shall be possible to compare two Maps for equality by comparing all Key-Value-Pairs for equality in O(n) time, where n is the number of Elements in the Map.
        // 
        inline bool operator!=(const StaticMap<Key,T,COUNT>& other) const
        {
            return Map<Key,T>::operator!=( other );
        }
        
        // Argument const StaticMap<Key,T,COUNT>& other :
        // The map to copy
        // Satisfies requirement 3927: Map - Assignment
        // It shall be possible to assign another Map to a Map in O(m + d) time, where m is the number of Elements to copy and d is the number of Elements to delete from the current Map.
        // 
        inline Map<Key, T>& operator=(const StaticMap<Key,T,COUNT>& other)
        {
            return Map<Key,T>::operator=(other);
        }
        
        ////    Attributes    ////
    
    private :
    
        RXF::MemoryPool<COUNT, sizeof(typename Map<Key,T>::Item)> memoryPool;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/RXFContainersStatic/RXF_StaticMap.h
*********************************************************************/

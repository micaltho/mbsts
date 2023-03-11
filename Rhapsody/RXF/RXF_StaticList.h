/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/RXFContainers/RXF_StaticList.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_StaticList_H
#define RXF_StaticList_H

#include "RXF_List.h"
namespace RXF {
    template <class T, std::int32_t COUNT> class StaticList : public List<T> {
    public :
    
        // Satisfies requirement 3806: List - Empty Initialization
        // It shall be possible to create an empty List in O(n) time, where n is the maximum number of Elements in the List.
        // 
        // Satisfies requirement 3809: List - Static Declaration
        // It shall be possible to create a List with a given maximum size using pseudo-dynamic memory allocation.
        // 
        inline StaticList(void) : List<T>(memoryPool)
        {
        }
        
        // Satisfies requirement 3809: List - Static Declaration
        // It shall be possible to create a List with a given maximum size using pseudo-dynamic memory allocation.
        // 
        // Satisfies requirement 3807: List - Copy Creation
        // It shall be possible to create a copy of a given List in O(n + m) time, where n is the maximum number of Elements in the List and m is the number of Elements to copy.
        // 
        inline StaticList(const StaticList<T, COUNT>& other) : List<T>(memoryPool)
        {
             List<T>::copy(other);
        }
        
        inline virtual ~StaticList(void)
        {
            List<T>::clear();
        }
        
        // Argument const StaticList<T, COUNT>& other :
        // The list to copy
        // Satisfies requirement 3937: List - Compare
        // It shall be possible to compare two Lists for equality by comparing the Values of their Elements in the same order in O(n) time, where n is the number of Elements in the List.
        // 
        inline bool operator==(const StaticList<T, COUNT>& other) const
        {
            return List<T>::operator==( other );
        }
        
        // Argument const StaticList<T, COUNT>& other :
        // The list to copy
        // Satisfies requirement 3937: List - Compare
        // It shall be possible to compare two Lists for equality by comparing the Values of their Elements in the same order in O(n) time, where n is the number of Elements in the List.
        // 
        inline bool operator!=(const StaticList<T, COUNT>& other) const
        {
            return List<T>::operator!=( other );
        }
        
        // Argument const StaticList<T, COUNT>& other :
        // The list to copy
        // Satisfies requirement 3812: List - Assignment
        // It shall be possible to assign another List to a List in O(m + d) time, where m is the number of Elements to copy and d is the number of Elements to delete from the current List.
        // 
        inline List<T>& operator=(const StaticList<T, COUNT>& other)
        {
            return List<T>::operator=(other);
        }
        
        ////    Attributes    ////
    
    private :
    
        RXF::MemoryPool<COUNT, sizeof(typename List<T>::Item)> memoryPool;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/RXFContainers/RXF_StaticList.h
*********************************************************************/

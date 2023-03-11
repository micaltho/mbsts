/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/RXFContainersStatic/RXF_NullValue.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_NullValue_H
#define RXF_NullValue_H

#include <cstdint>
namespace RXF {
    template <class T> class NullValue {
    public :
    
        // Get the empty value
        // Satisfies requirement 3961: Map - at
        // The Map shall be able to return a Value of an Element by a given Key in O(log(n)) time, where n is the number of elements in the Map. If this Key does not exist, insert a new Element with a default Value into the Map.
        // 
        // Satisfies requirement 3951: Map - Iterator - Get Key
        // The Map Iterator shall be able to return the Key of the Element it is pointing to in constant time.
        // 
        // Satisfies requirement 3780: List - Iterator - Dereferencing Position
        // The List Iterator shall be able to return the Value of the Element it is pointing to in constant time.
        // 
        // Satisfies requirement 3949: Map - Iterator - Get Value
        // The Map Iterator shall be able to return the Value of the Element it is pointing to in constant time.
        // 
        // Satisfies requirement 3800: List - Return Last Value
        // The List shall be able to return the last Value in the List by reference in constant time.
        // 
        // Satisfies requirement 3799: List - Return First Value
        // The List shall be able to return the first Value in the List by reference in constant time.
        // 
        inline static T & get(void)
        {
            static std::uint8_t nullValue[sizeof(T)] = {};
            
            /* @MISRA_5-2-8=OFF ID-0051: Cast needs to be done to be generic. */
            return reinterpret_cast<T&>(*nullValue); 
            /* @MISRA_5-2-8=ON (end of ID-0051) */
        }
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/RXFContainersStatic/RXF_NullValue.h
*********************************************************************/

/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/STLContainers/OMValueCompare.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMValueCompare_H
#define OMValueCompare_H

#include <utility>
// STL compare functor.
// Used for qualified relations that are implemented with STL containers.
template <class Key, class Value> class OMValueCompare {
public :

    // constructor
    // Argument Value value :
    // The value to find
    explicit inline OMValueCompare(Value value) : value_(value)
    {
    }
    
    // the operator used by std::find_if() to compare the map element with the one we are searching for
    // Argument const std::pair<Key,Value>& item :
    // The map item to check against the value
    inline bool operator()(const std::pair<Key,Value>& item)
    {
        return (item.second == value_);
    }
    
    ////    Attributes    ////

private :

    // The value to compare against (this is what we are looking for)
    Value value_;
};

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/STLContainers/OMValueCompare.h
*********************************************************************/

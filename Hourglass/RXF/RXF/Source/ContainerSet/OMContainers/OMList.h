/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/OMContainers/OMList.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMList_H
#define OMList_H

#include <cstdint>
#include <cstddef>
#include "OMIterator.h"
#include "OMAbstractContainer.h"
// Linked list container class
template <class Concept> class OMList : public OMAbstractContainer<Concept> {
public :

    // List node
    class Item {
    public :
    
        ////    Friend List    ////
        
        friend  class OMList<Concept>;
        
        
        // Initialize an item with a given data
        // Argument const Concept& theConcept :
        // The item data
        inline Item(const Concept& theConcept) : concept(theConcept), next(nullptr)
        {
        }
        
        // Copy constructor
        // Argument const Item& other :
        // The item to copy
        inline Item(const Item& other) : concept(other.concept), next(other.next)
        {
        }
        
        // Cleanup
        inline ~Item(void)
        {
            next = nullptr;
        }
        
        // Connect to the specified item
        // Argument Item* item :
        // The item to connect to
        inline void connectTo(Item* item)
        {
            next = item;
        }
        
        // Get the next item in the linked list
        inline Item* getNext(void) const
        {
            return next;
        }
        
        // Assignment operator
        // Argument const Item& other :
        // The item to copy
        inline Item& operator=(const Item& other)
        {
            next = other.next;
            concept = other.concept;	// assuming operator = for Concept
            return (*this);
        }
        
        ////    Attributes    ////
    
    private :
    
        // the next item in the list
        Item* next;
        
        // the data of the node
        Concept concept;
    };
    
    // Constructor - create an empty list
    inline OMList(void) : count_(0), first(nullptr), last(nullptr)
    {
    }
    
    // copy constructor
    // Argument const OMList<Concept> & aList :
    // The list to copy
    inline OMList(const OMList<Concept> & aList) : OMAbstractContainer<Concept>(), count_(0U), first(nullptr), last(nullptr)
    {
        copy(aList);
    }
    
    // Destructor - empty the list 
    inline virtual ~OMList(void)
    {
        removeAll();  
        first = nullptr;
        last = nullptr;
    }
    
    // Add an object to the list (at its end)
    // Argument Concept aConcept :
    // The element to add
    inline void add(Concept aConcept)
    {
        // Create a new list item
        Item* item = new Item(aConcept); 
        
        // Insert it into the list at the end
        if (first == nullptr) {
        	first = item;
        } else {
        	last->connectTo(item);
        }
        last = item;
        count_ = count_ + 1;
    }
    
    // if getCount>=i - Add c after i'th element else Add c at end
    // Argument const ::std::int32_t anIndex :
    // The index
    // Argument Concept aConcept :
    // The element to add
    inline void addAt(const ::std::int32_t anIndex, Concept aConcept)
    {
        if ( (anIndex == 0) || (first == nullptr) ) {
        	// Insert aConcept in first position
        	addFirst(aConcept);
        } else {
        	// Find the position of insertion
        	Item* item = first;
        	for (int32_t j = 1; (j < anIndex); j++) {
        		if ( item == last ) {
        			break;
        		}
        		item = item->next;                                       
        	}
        
        	if (item == last) {
        		// Insert aConcept in last position
        		add(aConcept);
        	} else {
        		Item* newGuy = new Item(aConcept);
        		Item* nextGuy = item->next;
        		item->connectTo(newGuy);
        		newGuy->connectTo(nextGuy);
        		count_ = count_ + 1;
        	}
        }
    }
    
    // Add an object to the list (at its beginning)
    // Argument Concept aConcept :
    // The element to add
    inline void addFirst(Concept aConcept)
    {
        // Create a new list item
        Item* item = new Item(aConcept);
        
        // Insert it into the list at the begining
        item->connectTo(first);
        first = item;
        if (last == nullptr) {
        	last = first;
        }
        count_ = count_ + 1;
    }
    
    // Find an object in the list
    // Argument Concept aConcept :
    // The element to find
    inline bool find(Concept aConcept) const
    {
        bool status = false;
        for (Item* i = first; i != nullptr; i = i->next) {
        	if (i->concept == aConcept) {
        		status = true;
        		break;
        	}
        }
        return status;
    }
    
    // Get the element in the given index
    // Argument const ::std::int32_t anIndex :
    // The index
    inline Concept & getAt(const ::std::int32_t anIndex) const
    {
        void* item;
        getFirst(item);
        for (int32_t j = 0; j < anIndex; j++) {
        	if (item != nullptr) {
        		getNext(item);
        	} else {
        		break;
        	}
        }
        return getCurrent(item);
    }
    
    // Get the element in the head of the list
    inline Concept & getFirstConcept(void) const
    {
        return getCurrent(first);
    }
    
    // Get the element in the tail of the list
    inline Concept & getLastConcept(void) const
    {
        return getCurrent(last);
    }
    
    // Check if the list is empty
    inline bool isEmpty(void) const
    {
        return (first == nullptr);
    }
    
    // Assignment operator
    // Argument const OMList<Concept> & aList :
    // The list to copy
    inline OMList<Concept> & operator=(const OMList<Concept> & aList)
    {
        copy(aList);
        return (*this);
    }
    
    // Get the element at the provided index
    // Argument const ::std::int32_t anIndex :
    // The index
    inline Concept & operator[](const ::std::int32_t anIndex) const
    {
        return getAt(anIndex);
    }
    
    // Remove all occurrences of a specific Object (Concept) from list
    // Argument Concept aConcept :
    // The element to remove
    /* @MISRA_17-0-2=OFF XD-0001: Remove must be used here to be complient with OXF API. */
    inline void remove(Concept aConcept)
    {
        // Check that we have something to remove
        if (first != nullptr) {
        	if (first->concept == aConcept) { 
        		// Special case if the object is first
        		_removeFirst();
        	}
        	// Keep searching for objects
        	Item* prev = first;
        	Item* cur = first->next;
        	while (cur!=nullptr) {
        		if (cur->concept == aConcept) {
        			prev->connectTo(cur->next);
        			if (cur->next == nullptr) {
        				last = prev;
        			}
        			delete cur;
        			count_ = count_ - 1;
        			break;
        		} 
        		prev = cur;
        		cur = cur->next;
        	}
        }
    }
    /* @MISRA_17-0-2=ON (end of XD-0001) */
    
    // Remove all items from list
    inline void removeAll(void)
    {
        while (first != nullptr) {
        	_removeFirst();
        }
    }
    
    // Remove first item from list
    inline void removeFirst(void)
    {
        if (first != nullptr) {
        	_removeFirst();
        }
    }
    
    // Remove a specific Item from list
    // Argument Item* anItem :
    // The list node to remove
    inline void removeItem(Item* anItem)
    {
        // Check that we have something to remove
        if (first != nullptr) {
        	if (first == anItem) {
        		// Special case if the required item is first
        		_removeFirst();     
        	} else {
        		// Search for the item
        		Item* prev = first;
        		Item* cur = first->next;
        		while (cur != nullptr) {
        			if (cur == anItem) {
        				// item found
        				prev->connectTo(cur->next);
        				if (cur->next == nullptr) {
        					last = prev;
        				}
        				delete cur;
        				count_ = count_ - 1;
        				break;
        			} 
        			// Advance to next item
        			prev = cur;
        			cur = cur->next;
        		}
        	}       
        }
    }
    
    // Remove last item from list - inefficient as we keep no
    // backward pointers
    inline void removeLast(void)
    {
        removeItem(last);
    }

protected :

    // unsafe Remove first item from list
    /* @MISRA_17-0-2=OFF XD-0001: Remove must be used here to be complient with OXF API. */
    inline void _removeFirst(void)
    {
        if (first != nullptr)
        {
        	Item* tmp = first;
        	first = first->next;
        	if (first == nullptr) {
        		last = nullptr;
        	}
        	delete tmp;
        	count_ = count_ - 1;
        }
    }
    /* @MISRA_17-0-2=ON (end of XD-0001) */
    
    // Copy the specified list
    // Argument const OMList<Concept> & aList :
    // The list to copy
    inline void copy(const OMList<Concept> & aList)
    {
        if (first != aList.first) {
        	// avoid self copy
        	removeAll();
        	OMIterator<Concept> iter(aList);
        	int32_t length = aList.getCount();
        	while (length--) {
        		add(*iter);
        		++iter;
        	}
        }
    }
    
    // Get the element at the given position (called by the iterator)
    // Argument void * const pos :
    // The iterator position
    inline virtual Concept & getCurrent(void * const pos) const
    {
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (pos != nullptr) 
        {
          	/* @MISRA_6-6-5,5-2-8+5-2-9=OFF XD-0001: In this case its not possible to have a single return. */
        	return reinterpret_cast<Item*>(pos)->concept;                                                       
        	/* @MISRA_6-6-5,5-2-8+5-2-9=ON (end of XD-0001) */ 
        } else 
        {
        	/* @MISRA_6-6-5,14-6-1=OFF XD-0001: In this case its not possible to have a single return. */
        	return OMNullValue<Concept>::get();
        	/* @MISRA_6-6-5,14-6-1=ON (end of XD-0001) */
        }
           
    }
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The list head (out)
    inline virtual void getFirst(void*& pos) const
    {
        pos = first;
    }
    
    // Get the position of the list tail
    // Argument void*& pos :
    // The list tail (out)
    inline virtual void getLast(void*& pos) const
    {
        pos = last;
    }
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The iterator position to advance
    inline virtual void getNext(void*& pos) const
    {
        /* @MISRA_5-2-8+5-2-9=OFF XD-0001: Cast from pointer to pointer. Needs to be done to be generic. */
        pos = reinterpret_cast<Item*>(pos)->next;   
        /* @MISRA_5-2-8+5-2-9=ON (end of XD-0001) */
    }

public :

    inline ::std::int32_t getCount(void) const
    {
        return count_;
    }
    
    inline ::std::int32_t getSize(void) const
    {
        return count_;
    }
    
    inline ::std::uint32_t size(void) const
    {
        return count_;
    }
    
    // Get the element in the given index
    inline Concept& front(void) const
    {
        return getFirstConcept();
    }
    
    // Get the element in the given index
    inline Concept& back(void) const
    {
        return getLastConcept();
    }
    
    inline OMIterator<Concept> begin(void) const
    {
        return OMIterator<Concept>( this );
    }
    
    // Returns Iterator to emtyEndItem to support RXFContainer compatible break conditions.
    inline OMIterator<Concept> end(void) const
    {
        return OMIterator<Concept>( );
    }
    
    // Check if the list is empty
    inline bool empty(void) const
    {
        return isEmpty();
    }
    
    // Remove all items from list
    inline void clear(void)
    {
        return removeAll();
    }
    
    // Add an object to the list (at its beginning)
    // Argument const Concept& value :
    // The element to add
    inline void push_front(const Concept& value)
    {
        addFirst(value);
    }
    
    // Remove first item from list
    inline void pop_front(void)
    {
        removeFirst();
    }
    
    // Add an object to the list (at its end)
    // Argument const Concept& value :
    // The element to add
    inline void push_back(const Concept& value)
    {
        add(value);
    }
    
    // Remove last item from list - inefficient as we keep no
    // backward pointers
    inline void pop_back(void)
    {
        removeLast();
    }
    
    // Find an object in the list
    // Argument const Concept& value :
    // The element to find
    inline bool contains(const Concept& value) const
    {
        return find(value);
    }
    
    // Assignment operator
    // Argument const OMList<Concept>& other :
    // The list to copy
    inline bool operator==(const OMList<Concept>& other) const
    {
        bool isEqual = ( size() == other.size() );
        
        // first test if list sizes are equal
        if( isEqual )
        {
        	OMIterator<Concept> iterMe = begin();
        	OMIterator<Concept> iterOther = other.begin();
        	
        	// if they have the same size compare content
        	while( iterMe != end() )
        	{
        		if( *iterMe != *iterOther )
        		{
        			isEqual = false;
        			break;
        		}
        		++iterMe;
        		++iterOther;
        	}
        }           
        return isEqual;
    }
    
    // Assignment operator
    // Argument const OMList<Concept>& other :
    // The list to copy
    inline bool operator!=(const OMList<Concept>& other) const
    {
        return !(*this == other);
    }
    
    ////    Attributes    ////

private :

    // the number of elements in the list
    ::std::int32_t count_;
    
    // the list head
    Item* first;
    
    // the tail head
    Item* last;
};

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/OMContainers/OMList.h
*********************************************************************/

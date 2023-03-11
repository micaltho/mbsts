/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/RXFContainers/RXF_List.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_List_H
#define RXF_List_H

#include "RXF_Types.h"
#include <cstdint>
#include <cstddef>
#include "RXF_ErrorHandler.h"
#include "RXF_NullValue.h"
#include "RXF_MemoryPool.h"
#include <new>
namespace RXF {
    // Linked list container class
    /* @MISRA_0-3-1=OFF FD-0002: It is ensured that the pointer can never be nullptr because the previous pointer of the first and next pointer of the last item of the list are pointing on themself. */
    template <class T> class List {
    private :
    
        class ItemBase {
        public :
        
            ////    Friend List    ////
            
            friend  class List<T>;
        
        private :
        
            inline ItemBase(void) : prev(this), next(this)
            {
            }
        
        public :
        
            inline virtual ~ItemBase(void)
            {
                prev = nullptr;
                next = nullptr;
            }
        
        private :
        
            inline virtual T& getValue(void) = 0;
            
            inline virtual ItemBase& operator=(const ItemBase& other) = delete;
            
            ////    Attributes    ////
            
            ItemBase* prev;
            
            ItemBase* next;
        };
        
        class EndItem : public ItemBase {
        public :
        
            ////    Friend List    ////
            
            friend  class List<T>;
            
            
            inline EndItem(void) : ItemBase()
            {
            }
        
        private :
        
            inline virtual T& getValue(void)
            {
                ErrorHandler::error( ERROR_LIST_DEREFERENCING_END_ITERATOR, 0, true );
                
                return NullValue<T>::get();
            }
        };
    
    public :
    
        class Item : public ItemBase {
        public :
        
            ////    Friend List    ////
            
            friend  class List<T>;
        
        private :
        
            inline Item(const T& value) : ItemBase(), value(value)
            {
            }
            
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container list. Otherwise the user would not be able to modify the value. */
            inline virtual T& getValue(void)
            {
                return value;
            }
            /* @MISRA_9-3-2=ON (end of ID-0052) */
            
            ////    Attributes    ////
            
            T value;
        };
        
        class Iterator {
        public :
        
            ////    Friend List    ////
            
            friend  class List<T>;
            
            
            // Satisfies requirement 3778: List - Iterator - Copy Creation
            // It shall be possible to create a copy of a given List Iterator in constant time.
            // 
            inline Iterator(const Iterator& iter) : thePos(iter.thePos)
            {
            }
            
            // Satisfies requirement 4000: List - Iterator - Creation
            // It shall be possible to create a List Iterator for a given List instance in constant time.
            // 
            inline Iterator(const List& list) : thePos(list.begin().thePos)
            {
            }
        
        private :
        
            inline Iterator(ItemBase* const item) : thePos( item )
            {
            }
        
        public :
        
            inline ~Iterator(void)
            {
                thePos = nullptr;
            }
            
            // Satisfies requirement 3786: List - Iterator - Equality
            // It shall be possible to compare two List Iterators for equality in constant time.
            // 
            inline bool operator==(const Iterator& other) const
            {
                return thePos == other.thePos;
            }
            
            // Satisfies requirement 3787: List - Iterator - Inequality
            // It shall be possible to compare two List Iterators for inequality in constant time.
            // 
            inline bool operator!=(const Iterator& other) const
            {
                return thePos != other.thePos;
            }
            
            // Satisfies requirement 3788: List - Iterator - Assignment
            // It shall be possible to assign another List Iterator to an List Iterator in constant time.
            // 
            inline Iterator& operator=(const Iterator& other)
            {
                thePos = other.thePos;
                return *this;
            }
            
            // Satisfies requirement 3779: List - Iterator - Increment
            // The List Iterator shall be able to increment its position by one in constant time.
            // 
            inline Iterator& operator++(void)
            {
                return increment(); 
            }
            
            // Argument const int_t :
            // C++ postfix ++ operator dummy argument
            // Satisfies requirement 3779: List - Iterator - Increment
            // The List Iterator shall be able to increment its position by one in constant time.
            // 
            /* @MISRA_0-1-11=OFF ID-0054: Argument type has to be int, because operator++ is part of the language standard and assumes int. */
            inline Iterator operator++(const int_t)
            {
                const Iterator tmp( *this ) ;	// save status prior to increment
                (void)increment();
                return tmp; 
            }
            /* @MISRA_0-1-11=ON (end of ID-0054) */
        
        private :
        
            inline Iterator& increment(void)
            {
                thePos = thePos->next;
                return *this;
            }
        
        public :
        
            // Satisfies requirement 3785: List - Iterator - Decrement
            // The List Iterator shall be able to decrement its position by one in constant time.
            // 
            inline Iterator& operator--(void)
            {
                return decrement(); 
            }
            
            // Argument const int_t :
            // C++ postfix ++ operator dummy argument
            // Satisfies requirement 3785: List - Iterator - Decrement
            // The List Iterator shall be able to decrement its position by one in constant time.
            // 
            /* @MISRA_0-1-11=OFF ID-0054: Argument type has to be int, because operator++ is part of the language standard and assumes int. */
            inline Iterator operator--(const int_t)
            {
                const Iterator tmp( *this ) ;	// save status prior to increment
                (void)decrement();
                return tmp; 
            }
            /* @MISRA_0-1-11=ON (end of ID-0054) */
        
        private :
        
            inline Iterator& decrement(void)
            {
                thePos = thePos->prev;
                return *this;
            }
        
        public :
        
            // Satisfies requirement 3955: List - Iterator - ErrorHandler
            // If a List Iterator is dereferenced and points to an invalid Element, the ErrorHandler shall be called.
            // 
            // Satisfies requirement 3780: List - Iterator - Dereferencing Position
            // The List Iterator shall be able to return the Value of the Element it is pointing to in constant time.
            // 
            inline T& operator*(void) const
            {
                return thePos->getValue();
            }
            
            ////    Attributes    ////
        
        private :
        
            ItemBase* thePos;
        };
        
        inline List(void) : count(0U), END(&emptyEndItem), first(END), last(END), memoryPool(nullptr)
        {
        }
        
        // Argument const List<T>& other :
        // The list to copy
        inline List(const List<T>& other) : count(0U), END(&emptyEndItem), first(END), last(END), memoryPool(nullptr)
        {
            copy( other );
        }
    
    protected :
    
        // Satisfies requirement 3806: List - Empty Initialization
        // It shall be possible to create an empty List in O(n) time, where n is the maximum number of Elements in the List.
        // 
        explicit inline List(MemoryPoolBase& pool) : count(0U), END(&emptyEndItem), first(END), last(END), memoryPool(&pool)
        {
        }
    
    public :
    
        inline ~List(void)
        {
            clear();
        }
        
        // Argument const List<T>& other :
        // The list to copy
        // Satisfies requirement 3937: List - Compare
        // It shall be possible to compare two Lists for equality by comparing the Values of their Elements in the same order in O(n) time, where n is the number of Elements in the List.
        // 
        /* @MISRA_14-6-2=OFF ID-0053: Need to call comparison operator to compare the value of two list elements. */
        inline bool operator==(const List<T>& other) const
        {
            bool isEqual = ( size() == other.size() );
            
            // first test if list sizes are equal
            if( isEqual )
            {
            	Iterator iterMe = begin();
            	Iterator iterOther = other.begin();
            	
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
        /* @MISRA_14-6-2=ON (end of ID-0053) */
        
        // Argument const List<T>& other :
        // The list to copy
        // Satisfies requirement 3937: List - Compare
        // It shall be possible to compare two Lists for equality by comparing the Values of their Elements in the same order in O(n) time, where n is the number of Elements in the List.
        // 
        inline bool operator!=(const List<T>& other) const
        {
            return !(*this == other);
        }
        
        // Argument const List<T>& other :
        // The list to copy
        // Satisfies requirement 3812: List - Assignment
        // It shall be possible to assign another List to a List in O(m + d) time, where m is the number of Elements to copy and d is the number of Elements to delete from the current List.
        // 
        inline List<T>& operator=(const List<T>& other)
        {
            clear();
            copy( other );
            return *this;
        }
    
    protected :
    
        // Argument const List<T>& other :
        // The list to copy
        inline void copy(const List<T>& other)
        {
            for (Iterator iter = other.begin(); iter != other.end(); ++iter)
            {
            	push_back( *iter );
            }
        }
    
    private :
    
        inline ItemBase* createItem(const T& value)
        {
            ItemBase* newItem = nullptr;
            
            if( nullptr != memoryPool)
            {
            	void* const freeBlock = memoryPool->alloc( sizeof( Item ) );
            	
            	if( nullptr != freeBlock )
            	{
            		newItem = new (freeBlock) Item( value );
            		++count;
            	}
            	else
            	{
            		// Return from this ErrorHandler call is not critical,
            		// because nullptr check on new item is performed in addItem()
            		ErrorHandler::error( ERROR_LIST_NO_FREE_MEMORY, 0, true );
            	}
            }
            else
            {
            	newItem = new Item( value );
            	if( nullptr != newItem )
            	{
            		++count;
            	}
            	else
            	{
            		// Return from this ErrorHandler call is not critical,
            		// because nullptr check on new item is performed in addItem()
            		ErrorHandler::error( ERROR_MAP_NO_FREE_MEMORY, 0, true );  
            	}
            }
            
            return newItem;
        }
        
        inline void destroyItem(ItemBase* const instance)
        {
            if( nullptr != memoryPool)
            {
            	instance->~ItemBase();
            	
            	// DestroyIdem will never be called if instance is not in memory.
            	// This is checked inside operation isIteratorValid.
            	(void)memoryPool->freeMemory( instance );
            	
            	--count;
            }
            else
            {
            	delete instance;
            	--count;
            }
        }
        
        // Argument const Iterator& pos :
        // The argument pos needs to be a valid iterator for this map.
        // Passing an invalid iterator will lead to undefined behavior and calling the ErrorHandler.
        inline bool isIteratorValid(const Iterator& pos) const
        {
            bool isValid;
            
            if( nullptr != memoryPool)
            {
            	isValid = ( memoryPool->isMemoryInPool( pos.thePos ) || ( pos.thePos == END ) );
            	
            	if( isValid )
            	{
            		// check if item is linked in list
            		isValid = nullptr != pos.thePos->prev;
            	}
            }
            else
            {
            	// cannot validate Iterator if no dynamic list without memoryPool is used
            	isValid = true;
            }
            
            return isValid;
        }
    
    public :
    
        // Satisfies requirement 3810: List - Begin Iterator
        // The List shall be able to return an Iterator to the first Element in the List in constant time.
        // 
        inline Iterator begin(void) const
        {
            return Iterator( first );
        }
        
        // Satisfies requirement 3811: List - End Iterator
        // The List shall be able to return an Iterator to the Element following the last Element in the List in constant time.
        // 
        inline Iterator end(void) const
        {
            return Iterator( END );
        }
        
        // Satisfies requirement 3805: List - Empty
        // The List shall be able to return whether the List is empty or not in constant time.
        // 
        inline bool empty(void) const
        {
            return ( count == 0U );
        }
        
        // Satisfies requirement 3804: List - Count
        // The List shall be able to return the number of Elements in the List in constant time.
        // 
        inline ::std::uint32_t size(void) const
        {
            return count;
        }
        
        // Satisfies requirement 3799: List - Return First Value
        // The List shall be able to return the first Value in the List by reference in constant time.
        // 
        inline T& front(void) const
        {
            return first->getValue();
        }
        
        // Satisfies requirement 3800: List - Return Last Value
        // The List shall be able to return the last Value in the List by reference in constant time.
        // 
        inline T& back(void) const
        {
            return last->getValue();
        }
        
        // Argument const T& value :
        // The element to add
        // Satisfies requirement 3912: List - ErrorHandler - Size exceeded
        // If the defined maximum number of List Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called with error code.
        // 
        // Satisfies requirement 3789: List - Push Front
        // The List shall be able to insert a Value by reference at the beginning of the List in constant time.
        // 
        inline void push_front(const T& value)
        {
            // Create a new list item
            ItemBase* const item = createItem( value );
            
            if( item != nullptr )
            {
            	// Insert it into the list at the begining
            	item->next = first;
            	first->prev = item;
            	first = item;
            	if( END == last )
            	{
            		last = first;
            	}
            }
        }
        
        // Satisfies requirement 3791: List - Pop Front
        // The List shall be able to delete the first Element in the List in constant time.
        // 
        inline void pop_front(void)
        {
            if( END != first )
            {
                ItemBase* const itemToDelete = first;
            	first = first->next;
            	if( END == first )
            	{
            		last = END;
            		emptyEndItem.prev = END;
            	}
            	else
            	{
            		first->prev = first;
            	}
            	destroyItem( itemToDelete );
            }
        }
        
        // Argument const T& value :
        // The element to add
        // Satisfies requirement 3912: List - ErrorHandler - Size exceeded
        // If the defined maximum number of List Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called with error code.
        // 
        // Satisfies requirement 3790: List - Push Back
        // The List shall be able to insert a Value by reference at the end of the List in constant time.
        // 
        inline void push_back(const T& value)
        {
            // Create a new list item
            ItemBase* const item = createItem( value );
            if( item != nullptr )
            {
            	// Insert it into the list at the end
            	if( END == first ) //list is empty
            	{
            		first = item;
            		first->prev = first;
            	}
            	else //list is not empty
            	{
            		item->prev = last;
            		last->next = item;
            	}
            	item->next = END;
            	emptyEndItem.prev = item;
            	last = item;
            }
        }
        
        // Satisfies requirement 3793: List - Pop Back
        // The List shall be able to delete the last Element in the List in constant time.
        // 
        inline void pop_back(void)
        {
            if( count > 0U )
            {
            	ItemBase* const itemToDestoy = last;
            	if( count == 1U )
            	{
            		last = END;
            		first = END;
            		emptyEndItem.prev = END;
            	}
            	else
            	{
            		last = last->prev;
            		last->next = END;
            		emptyEndItem.prev = last;
            	}
            	destroyItem( itemToDestoy );
            }
        }
        
        // Argument const Iterator& pos :
        // The index
        // Argument const T& value :
        // The element to add
        // Satisfies requirement 4006: List - Insert - Invalid Iterator
        // If a given Iterator position during insertion of a Value into a List is not a valid Iterator of this List, the ErrorHandler shall be called.
        // 
        // Satisfies requirement 3912: List - ErrorHandler - Size exceeded
        // If the defined maximum number of List Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called with error code.
        // 
        // Satisfies requirement 3795: List - Insertion Iterator
        // If a Value is inserted before a given position, the List shall return an Iterator to the newly created Element.
        // 
        // Satisfies requirement 3792: List - Insert before Position
        // The List shall be able to insert a Value by reference before a given Iterator position in constant time.
        // 
        inline Iterator insert(const Iterator& pos, const T& value)
        {
            Iterator iter( END );
            
            if( isIteratorValid( pos ) )
            {
            	if(pos.thePos == END )
            	{
            		const uint32_t oldCount = count;
            		push_back( value );
            		if( oldCount != count ) // no item could be inserted
            		{
            			iter = Iterator(last);
            		}
            	}
            	else
            	{
            		ItemBase* const nextItem = pos.thePos;
            		if( nextItem == first )
            		{
            			const uint32_t oldCount = count;
            			push_front( value );
            			if( oldCount != count ) // no item could be inserted
            			{
            				iter = Iterator( first );
            			}
            		}
            		else
            		{		
            			ItemBase* const newItem = createItem( value );
            			if( newItem != nullptr )
            			{
            				ItemBase* const prevItem = nextItem->prev;
            				prevItem->next = newItem;
            				nextItem->prev = newItem;
            				newItem->next = nextItem;
            				newItem->prev = prevItem;
            				iter = Iterator( newItem );
            			}
            		}
            	}
            }
            else
            {
            	RXF::ErrorHandler::error( ERROR_LIST_INVALID_ITERATOR, 0, true );
            }
            
            return iter;
        }
        
        // Argument const Iterator& pos :
        // The argument pos needs to be a valid iterator for this map.
        // Passing an invalid iterator will lead to undefined behavior and calling the ErrorHandler.
        // Satisfies requirement 4005: List - Erase - Invalid Iterator
        // If a given Iterator position during deletion of an Element from a List is not a valid Iterator of this List, the ErrorHandler shall be called.
        // 
        // Satisfies requirement 3794: List - Erase Position
        // The List shall be able to delete the Element at a given Iterator position in constant time.
        // 
        // Satisfies requirement 3796: List - Erase - Iterator Return
        // If an Element is deleted at a given position, the List shall return an Iterator to the following Element in the List.
        // 
        // Satisfies requirement 3797: List - Erase - End Iterator Return
        // If an Element is deleted at a given position and the position is the last Element in the List, the List shall return the end Iterator of the List.
        // 
        inline Iterator erase(const Iterator& pos)
        {
            Iterator iter( END );
            
            if( isIteratorValid( pos ) )
            {
            	if( pos.thePos != END )
            	{
            		ItemBase* const item = pos.thePos;
            		
            		if( item == first )
            		{
            			pop_front();
            			iter = Iterator( first );
            		}
            		else if( item == last )
            		{
            			pop_back();
            			iter = Iterator( last );
            		}
            		else
            		{
            			iter = Iterator( item->next );
            			item->prev->next = item->next;
            			item->next->prev = item->prev;
            			destroyItem( item );
            		}
            	}
            }
            else
            {
            	RXF::ErrorHandler::error( ERROR_LIST_INVALID_ITERATOR, 0, true );
            }
            
            return iter;
        }
        
        // Satisfies requirement 3798: List - Clear all
        // The List shall be able to delete all Elements in the List in O(n) time, where n is the number of Elements in the List.
        // 
        inline void clear(void)
        {
            while( count != 0U )
            {
            	pop_front();
            }
        }
        
        // Argument const T& value :
        // The element to remove
        // Satisfies requirement 3962: List - Erase Value
        // The List shall be able to delete all Elements with a given Value in O(n) time, where n is the number of Elements in the List.
        // 
        /* @MISRA_14-6-2=OFF ID-0053: Need to call comparison operator to compare the value of two list elements. */
        inline Iterator remove(const T& value)
        {
            Iterator iter( begin() );
            
            while( iter != end() )
            {
            	if( *iter == value)
            	{
            		iter = erase( iter );
            	}
            	else
            	{
            		++iter;
            	}
            }
            
            return iter;
        }
        /* @MISRA_14-6-2=ON (end of ID-0053) */
        
        // Argument const T& value :
        // The element to find
        // Satisfies requirement 3803: List - Find - End Iterator Return
        // If a given Value is not contained in the List, the List shall return the end Iterator of the List.
        // 
        // Satisfies requirement 3802: List - Find
        // The List shall be able to return an Iterator pointing to the first Element in the List containing the given Value in O(n) time, where n is the number of Elements in the List.
        // 
        /* @MISRA_14-6-2=OFF ID-0053: Need to call comparison operator to compare the value of two list elements. */
        inline Iterator find(const T& value) const
        {
            Iterator result( END );
            for (Iterator cur = begin(); cur != end(); ++cur)
            {
            	if( *cur == value )
            	{
            		result = cur;
            		break;
            	}
            }
            return result;
        }
        /* @MISRA_14-6-2=ON (end of ID-0053) */
        
        // Argument const T& value :
        // The element to find
        // Satisfies requirement 3801: List - Contains
        // The List shall be able to return whether a Value is contained in the List or not in O(n) time, where n is the number of Elements in the List.
        // 
        /* @MISRA_14-6-2=OFF ID-0053: Need to call comparison operator to compare the value of two list elements. */
        inline bool contains(const T& value) const
        {
            return find(value) != end();
        }
        /* @MISRA_14-6-2=ON (end of ID-0053) */
        
        ////    Attributes    ////
    
    private :
    
        std::uint32_t count;
        
        EndItem emptyEndItem;
        
        EndItem* const END;
        
        ItemBase* first;
        
        ItemBase* last;
        
        MemoryPoolBase* const memoryPool;
    };
    /* @MISRA_0-3-1=ON (end of FD-0002) */
}

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/RXFContainers/RXF_List.h
*********************************************************************/

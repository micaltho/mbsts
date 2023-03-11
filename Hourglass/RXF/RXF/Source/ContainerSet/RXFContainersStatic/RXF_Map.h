/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/RXFContainersStatic/RXF_Map.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Map_H
#define RXF_Map_H

#include "RXF_Types.h"
#include <cstdint>
#include <cstddef>
#include "RXF_ErrorHandler.h"
#include "RXF_NullValue.h"
#include "RXF_MemoryPool.h"
#include <new>
namespace RXF {
    template <class Key, class T> class Map {
    private :
    
        class ItemBase {
        public :
        
            ////    Friend List    ////
            
            friend  class Map<Key, T>;
            
            friend  class Iterator;
            
            
            inline ItemBase(ItemBase * const aParent, ItemBase * const aLeft, ItemBase * const aRight) : parent( aParent ), left( aLeft ), right( aRight ), color( BLACK )
            {
            }
            
            inline virtual ~ItemBase(void)
            {
                parent = nullptr;
                left = nullptr;
                right = nullptr;
                color = BLACK;
            }
        
        private :
        
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container map. Otherwise the user would not be able to modify the value. */
            inline virtual Key& getKey(void) = 0;
            /* @MISRA_9-3-2=ON (end of ID-0052) */
            
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container map. Otherwise the user would not be able to modify the value. */
            inline virtual T& getValue(void) = 0;
            /* @MISRA_9-3-2=ON (end of ID-0052) */
            
            inline virtual ItemBase& operator=(const ItemBase& other) = delete;
            
            ////    Attributes    ////
            
            ItemBase* parent;
            
            ItemBase* left;
            
            ItemBase* right;
            
            bool color;
        };
        
        class NilItem : public ItemBase {
        public :
        
            // The EndItem is a special Item, that is used as termination Element.
            // Parent and right are linked to itself.
            inline NilItem(void) : ItemBase(nullptr, NIL, NIL)
            {
            }
        
        protected :
        
            inline NilItem(ItemBase * const aParent, ItemBase * const aLeft, ItemBase * const aRight) : ItemBase(aParent, aLeft, aRight)
            {
            }
        
        private :
        
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container map. Otherwise the user would not be able to modify the value. */
            inline virtual Key& getKey(void)
            {
                ErrorHandler::error( ERROR_MAP_DEREFERENCING_END_ITERATOR, 0, true );
                
                return NullValue<Key>::get();
            }
            /* @MISRA_9-3-2=ON (end of ID-0052) */
            
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container map. Otherwise the user would not be able to modify the value. */
            inline virtual T& getValue(void)
            {
                ErrorHandler::error( ERROR_MAP_DEREFERENCING_END_ITERATOR, 0, true );
                
                return NullValue<T>::get();
            }
            /* @MISRA_9-3-2=ON (end of ID-0052) */
        };
        
        class EndItem : public NilItem {
        public :
        
            // The EndItem is a special Item, that is used as termination Element.
            // Parent and right are linked to itself.
            inline EndItem(void) : NilItem(this, NIL, this)
            {
            }
        };
    
    public :
    
        class Item : public ItemBase {
        public :
        
            ////    Friend List    ////
            
            friend  class Map<Key,T>;
        
        private :
        
            // Argument const Key& key :
            // The item's key
            // Argument const T& value :
            // The item's data
            inline Item(const Key& key, const T& value) : ItemBase(nullptr, NIL, NIL), key( key ), value( value )
            {
            }
            
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container map. Otherwise the user would not be able to modify the value. */
            inline virtual Key& getKey(void)
            {
                return key;
            }
            /* @MISRA_9-3-2=ON (end of ID-0052) */
            
            /* @MISRA_9-3-2=OFF ID-0052: A non const reference needs to be returned to be compliant to the STD container map. Otherwise the user would not be able to modify the value. */
            inline virtual T& getValue(void)
            {
                return value;
            }
            /* @MISRA_9-3-2=ON (end of ID-0052) */
            
            ////    Attributes    ////
            
            Key key;
            
            T value;
        };
        
        class Iterator {
        public :
        
            ////    Friend List    ////
            
            friend  class Map<Key, T>;
            
            
            // Satisfies requirement 3943: Map - Iterator - Copy Creation
            // It shall be possible to create a copy of a given Map Iterator in constant time.
            // 
            inline Iterator(const Iterator& iter) : thePos(iter.thePos)
            {
            }
            
            // Satisfies requirement 4001: Map - Iterator - Creation
            // It shall be possible to create a Map Iterator for a given Map instance in constant time.
            // 
            inline Iterator(const Map& map) : thePos(map.begin().thePos)
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
            
            // Satisfies requirement 3945: Map - Iterator - Equality
            // It shall be possible to compare two Map Iterators for equality in constant time.
            // 
            inline bool operator==(const Iterator& other) const
            {
                return thePos == other.thePos;
            }
            
            // Satisfies requirement 3946: Map - Iterator - Inequality
            // It shall be possible to compare two Map Iterators for inequality in constant time.
            // 
            inline bool operator!=(const Iterator& other) const
            {
                return thePos != other.thePos;
            }
            
            // Satisfies requirement 3944: Map - Iterator - Assignment
            // It shall be possible to assign another Map Iterator to an Map Iterator in constant time.
            // 
            inline Iterator& operator=(const Iterator& other)
            {
                thePos = other.thePos;
                return *this;
            }
            
            // Satisfies requirement 3947: Map - Iterator - Increment
            // The Map Iterator shall be able to increment its position by one in O(log(n)) time, where n is the number of elements in the Map.
            // 
            inline Iterator& operator++(void)
            {
                return increment(); 
            }
            
            // Argument const int_t :
            // C++ postfix ++ operator dummy argument
            // Satisfies requirement 3947: Map - Iterator - Increment
            // The Map Iterator shall be able to increment its position by one in O(log(n)) time, where n is the number of elements in the Map.
            // 
            /* @MISRA_0-1-11=OFF ID-0054: Argument type has to be int, because operator++ is part of the language standard and assumes int. */
            inline Iterator operator++(const int_t)
            {
                Iterator const tmp( *this ) ;	// save status prior to increment
                (void)increment();
                return tmp; 
            }
            /* @MISRA_0-1-11=ON (end of ID-0054) */
        
        private :
        
            inline Iterator& increment(void)
            {
                if( NIL != thePos->right )
                {
                	// Can we go down ?
                	thePos = thePos->right;
                	while( NIL != thePos->left )
                	{
                		thePos = thePos->left;
                	}
                }
                else
                { 
                	// Must go up
                	ItemBase* oldP;
                	do
                	{
                		oldP = thePos;
                		thePos = thePos->parent;
                	}
                	while( thePos->right == oldP );
                }     
                
                return *this;
            }
        
        public :
        
            // Satisfies requirement 3948: Map - Iterator - Decrement
            // The Map Iterator shall be able to decrement its position by one in O(log(n)) time, where n is the number of elements in the Map.
            // 
            inline Iterator& operator--(void)
            {
                return decrement(); 
            }
            
            // Argument const int_t :
            // C++ postfix ++ operator dummy argument
            // Satisfies requirement 3948: Map - Iterator - Decrement
            // The Map Iterator shall be able to decrement its position by one in O(log(n)) time, where n is the number of elements in the Map.
            // 
            /* @MISRA_0-1-11=OFF ID-0054: Argument type has to be int, because operator++ is part of the language standard and assumes int. */
            inline Iterator operator--(const int_t)
            {
                Iterator const tmp( *this ) ;	// save status prior to increment
                (void)decrement();
                return tmp; 
            }
            /* @MISRA_0-1-11=ON (end of ID-0054) */
        
        private :
        
            inline Iterator& decrement(void)
            {
                // prevent infinite loop for size() == 1 maps
                if( thePos->left != thePos )
                {
                	if( NIL != thePos->left)
                	{
                		// Can we go down ?
                		thePos = thePos->left;
                		while( NIL != thePos->right )
                		{
                			thePos = thePos->right;
                		}
                	}
                	else
                	{ 
                		// Must go up
                		ItemBase* oldP;
                		do
                		{
                			oldP = thePos;
                			thePos = thePos->parent;
                		}
                		while( thePos->left == oldP );
                	}
                } 
                return *this;
            }
        
        public :
        
            // Satisfies requirement 3954: Map - Iterator - ErrorHandler
            // If a Map Iterator is dereferenced and points to an invalid Element, the ErrorHandler shall be called.
            // 
            // Satisfies requirement 3951: Map - Iterator - Get Key
            // The Map Iterator shall be able to return the Key of the Element it is pointing to in constant time.
            // 
            inline Key& key(void) const
            {
                return thePos->getKey();
            }
            
            // Satisfies requirement 3954: Map - Iterator - ErrorHandler
            // If a Map Iterator is dereferenced and points to an invalid Element, the ErrorHandler shall be called.
            // 
            // Satisfies requirement 3949: Map - Iterator - Get Value
            // The Map Iterator shall be able to return the Value of the Element it is pointing to in constant time.
            // 
            inline T& value(void) const
            {
                return thePos->getValue();
            }
            
            // Satisfies requirement 3954: Map - Iterator - ErrorHandler
            // If a Map Iterator is dereferenced and points to an invalid Element, the ErrorHandler shall be called.
            // 
            // Satisfies requirement 3949: Map - Iterator - Get Value
            // The Map Iterator shall be able to return the Value of the Element it is pointing to in constant time.
            // 
            inline T& operator*(void) const
            {
                return value();
            }
            
            ////    Attributes    ////
        
        private :
        
            ItemBase* thePos;
        };
    
    protected :
    
        // Satisfies requirement 3925: Map - Empty Initialization
        // It shall be possible to create an empty Map in O(n) time, where n is the maximum number of Elements in the Map.
        // 
        explicit inline Map(MemoryPoolBase& pool) : count( 0U ), END(&emptyEndItem), root( NIL ), first( nullptr ), last( nullptr ), memoryPool(pool)
        {
        }
        
        // Argument const Map<Key,T>& other :
        // The map to copy
        // Satisfies requirement 3927: Map - Assignment
        // It shall be possible to assign another Map to a Map in O(m + d) time, where m is the number of Elements to copy and d is the number of Elements to delete from the current Map.
        // 
        inline Map<Key, T>& operator=(const Map<Key,T>& other)
        {
            clear();
            copy( other );
            return *this;
        }
    
    private :
    
        inline ItemBase* createItem(const Key& key, const T& value)
        {
            ItemBase* newItem = nullptr;
            
            void* const freeBlock = memoryPool.alloc( sizeof( Item ) );
            
            if( nullptr != freeBlock )
            {
            	newItem = new (freeBlock) Item( key, value );
            	++count;
            }
            else
            {
            	// Return from this ErrorHandler call is not critical,
            	// because nullptr check on new item is performed in addItem()
            	ErrorHandler::error( ERROR_MAP_NO_FREE_MEMORY, 0, true );  
            }
            
            return newItem;
        }
        
        inline void destroyItem(ItemBase* const instance)
        {
            instance->~ItemBase();
            
            // DestroyIdem will never be called if instance is not in memory.
            // This is checked inside operation isIteratorValid.
            (void)memoryPool.freeMemory( instance );
            
            --count;
        }
        
        // Argument const Iterator& pos :
        // The argument pos needs to be a valid iterator for this map.
        // Passing an invalid iterator will lead to undefined behavior and calling the ErrorHandler.
        inline bool isIteratorValid(const Iterator& pos) const
        {
            // check if iterator points to item inside pool memory or is the end iterator 
            bool isValid = ( memoryPool.isMemoryInPool( pos.thePos ) || ( pos.thePos == END ) );
            
            if( isValid )
            {
            	// check if item is linked in map
            	isValid = nullptr != pos.thePos->left;
            }
            
            return isValid;
        }
    
    public :
    
        inline ~Map(void)
        {
            clear();
        }
        
        // Argument const Map<Key,T>& other :
        // The map to copy
        // Satisfies requirement 3938: Map - Compare
        // It shall be possible to compare two Maps for equality by comparing all Key-Value-Pairs for equality in O(n) time, where n is the number of Elements in the Map.
        // 
        /* @MISRA_14-6-2=OFF ID-0053: Need to call comparison operator to compare the value of two list elements. */
        inline bool operator==(const Map<Key,T>& other) const
        {
            bool isEqual = ( size() == other.size() );
            
            if( isEqual )
            {
            	Iterator iterMe = begin();
            	Iterator iterOther = other.begin();
            	
            	while( iterMe != end() )
            	{
            		/* @MISRA_5-14-1=OFF ID-0055: Function calls in right hand operand are known to have no side effects. */
            		if( ( iterMe.key() != iterOther.key() ) || ( iterMe.value() != iterOther.value() ) )
            		/* @MISRA_5-14-1=ON (end of ID-0055) */
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
        
        // Argument const Map<Key,T>& other :
        // The map to copy
        // Satisfies requirement 3938: Map - Compare
        // It shall be possible to compare two Maps for equality by comparing all Key-Value-Pairs for equality in O(n) time, where n is the number of Elements in the Map.
        // 
        inline bool operator!=(const Map<Key,T>& other) const
        {
            return !(*this == other);
        }
    
    protected :
    
        inline void copy(const Map<Key, T>& other)
        {
            if( !other.empty() )
            {
            	ItemBase* cur = other.root;
            	root = createItem( cur->getKey(), cur->getValue() );
            	ItemBase* item = root;
            	
            	// traverse entire tree, left items first
            	while( cur != nullptr )
            	{
            		if( ( item->left == NIL ) && ( cur->left != NIL )  )
            		{
            			item->left = createItem( cur->left->getKey(), cur->left->getValue() );
            			item->left->color = cur->left->color;
            			item->left->parent = item;
            			cur = cur->left;
            			item = item->left;
            			
            			// find and connect first item
            			if( cur == cur->left )
            			{
            				first = item;
            				first->left = first;
            			}
            		}
            		else if( ( item->right == NIL ) && ( cur->right != NIL ) )
            		{
            			// find and connect last item
            			if( cur->right == other.END )
            			{
            				last = item;
            				last->right = END;
            				emptyEndItem.parent = last;
            			}
            			else
            			{
            				item->right = createItem( cur->right->getKey(), cur->right->getValue() );
            				item->right->color = cur->right->color;
            				item->right->parent = item;
            				cur = cur->right;
            				item = item->right;
            			}
            		}
            		else
            		{
            			cur = cur->parent;
            			item = item->parent;
            		}
            	}
            }
            else
            {
            	root = NIL;
            	first = nullptr;
            	last = nullptr;
            }
        }
    
    public :
    
        // Satisfies requirement 3921: Map - Begin Iterator
        // The Map shall be able to return an Iterator to the Element in the Map with the smallest Key in constant time.
        // 
        inline Iterator begin(void) const
        {
            Iterator iter = end();
            if( root != NIL )
            {
            	iter = Iterator( first );
            }
            return iter;
        }
        
        // Satisfies requirement 3922: Map - End Iterator
        // The Map shall be able to return an Iterator to the Element following the Element in the Map with the largest Key in constant time.
        // 
        inline Iterator end(void) const
        {
            return Iterator( END );
        }
        
        // Satisfies requirement 3936: Map - Empty
        // The Map shall be able to return whether the Map is empty or not in constant time.
        // 
        inline bool empty(void) const
        {
            return (root == NIL);
        }
        
        // Satisfies requirement 3935: Map - Count
        // The Map shall be able to return the number of Elements in the Map in constant time.
        // 
        inline std::uint32_t size(void) const
        {
            return count;
        }
        
        // Satisfies requirement 3920: Map - ErrorHandler - Size exceeded
        // If the defined maximum number of Map Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called.
        // 
        inline T& operator[](const Key & aKey)
        {
            ItemBase* item = lookUp( root, aKey );
            if( item == END )
            { 
              	item = insert( aKey, T() ).thePos;
            }
            return item->getValue();
        }
        
        // Satisfies requirement 3961: Map - at
        // The Map shall be able to return a Value of an Element by a given Key in O(log(n)) time, where n is the number of elements in the Map. If this Key does not exist, insert a new Element with a default Value into the Map.
        // 
        // Satisfies requirement 3920: Map - ErrorHandler - Size exceeded
        // If the defined maximum number of Map Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called.
        // 
        inline T & at(const Key& aKey) const
        {
            ItemBase* const item = lookUp( root, aKey );
            if( item == END )
            {
              	ErrorHandler::error( ERROR_MAP_INVALID_KEY, 0, true );
            }
            return item->getValue();
        }
    
    private :
    
        /* @MISRA_7-5-4=OFF ID-0056: Recursion is used for efficient lookup in tree. */
        inline ItemBase* lookUp(ItemBase* const anItem, const Key & aKey) const
        {
            ItemBase* item;
            
            if( anItem->right == anItem )
            {
            	item = END;
            }
            else
            {
            	if( aKey < anItem->getKey() )
            	{
            		if (anItem == first)
            		{
            			item = END;
            		}
            		else
            		{
            			item = lookUp(anItem->left, aKey);
            		}
            	}
            	else if( aKey > anItem->getKey() )
            	{
            		item = lookUp( anItem->right, aKey );
            	}
            	else
            	{
            		item = anItem;
            	}
            }
            
            return item;
        }
        /* @MISRA_7-5-4=ON (end of ID-0056) */
    
    public :
    
        // Satisfies requirement 3956: Map - Reject during Insertion
        // If an Element is inserted and the given Key already exists in the Map, the current Value shall not be overriden by the new Value and an Iterator to the Element following the Element in the Map with the largest Key shall be returned.
        // 
        // Satisfies requirement 3939: Map - Insert
        // The Map shall be able to insert an Element into the Map for a given Key and Value in O(log(n)) time, where n is the number of Elements in the Map.
        // 
        // Satisfies requirement 3941: Map - Insertion Iterator
        // If an Element is inserted or assigned, the Map shall return an Iterator to the inserted or assigned Element.
        // 
        // Satisfies requirement 3920: Map - ErrorHandler - Size exceeded
        // If the defined maximum number of Map Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called.
        // 
        inline Iterator insert(const Key& aKey, const T& aValue)
        {
            return addItem( aKey, aValue , false);
        }
        
        // Argument const Key& aKey :
        // The key
        // Argument const T& aValue :
        // The data
        // Satisfies requirement 3941: Map - Insertion Iterator
        // If an Element is inserted or assigned, the Map shall return an Iterator to the inserted or assigned Element.
        // 
        // Satisfies requirement 3940: Map - Assignment during Insertion
        // If an Element is inserted and the given Key already exists in the Map, the new Value shall be assigned to the Element.
        // 
        // Satisfies requirement 3939: Map - Insert
        // The Map shall be able to insert an Element into the Map for a given Key and Value in O(log(n)) time, where n is the number of Elements in the Map.
        // 
        // Satisfies requirement 3920: Map - ErrorHandler - Size exceeded
        // If the defined maximum number of Map Elements for a variable multiplicity is exceeded during run-time, the ErrorHandler shall be called.
        // 
        inline Iterator insert_or_assign(const Key& aKey, const T& aValue)
        {
            return addItem( aKey, aValue , true);
        }
    
    private :
    
        inline Iterator addItem(const Key& aKey, const T& aValue, const bool updateExisting)
        {
            ItemBase* item = createItem( aKey, aValue );
            
            // check if memory is valid
            if( nullptr == item )
            {
            	item = END;
            }
            else
            {
            	if( root == NIL )
            	{
            		root = item;
            		first = item;
            		last = item;
            		item->right = END;
            		emptyEndItem.parent = item;
            		item->left = item;
            	}
            	else
            	{
            		bool keyIsInMap = false;
            		
            		// disconnect end items from tree
            		first->left = NIL;
            		last->right = NIL;
            		
            		item->color = RED; // new node must be red
            	
            		ItemBase* parent = nullptr;
            		ItemBase* cur = this->root;
            	
            		while( cur != NIL )
            		{
            			parent = cur;
            			
            			if( item->getKey() < cur->getKey() )
            			{
            				cur = cur->left;
            			}
            			else if( item->getKey() > cur->getKey() )
            			{
            				cur = cur->right;
            			}
            			else
            			{
            				keyIsInMap = true;
            				break;
            			}
            		}
            		
            		if( keyIsInMap == false )
            		{
            			item->parent = parent;
            			if( item->getKey() < parent->getKey() )
            			{
            				parent->left = item;
            			}
            			else
            			{
            				parent->right = item;
            			}
            		
            			// if parent of new node is root, there is nothing to do
            			if( item->parent->parent != nullptr )
            			{
            				// fix the tree
            				fixInsert( item );
            			}
            	
            			// check if we need to update smallest or largest item
            			if( item->getKey() < first->getKey() )
            			{
            				first = item;
            
            			}		
            			if( item->getKey() > last->getKey() )
            			{
            				last = item;
            				emptyEndItem.parent = last;
            			}
            		}
            		else
            		{
            			destroyItem( item );
            
            			if( updateExisting == true )
            			{
            				cur->getValue() = aValue;
            				item = cur;
            			}
            			else
            			{
            				item = END;
            			}
            		}
            		
            		// reconnect end items to tree
            		first->left = first;
            		last->right = END;
            	}
            }
            
            return Iterator( item );
        }
    
    public :
    
        // Argument const Iterator& pos :
        // The argument pos needs to be a valid iterator for this map.
        // Passing an invalid iterator will lead to undefined behavior and calling the ErrorHandler.
        // Satisfies requirement 4007: Map - Erase - Invalid Iterator
        // If a given Iterator position during deletion of an Element from a Map is not a valid Iterator of this Map, the ErrorHandler shall be called.
        // 
        // Satisfies requirement 3930: Map - Erase - End Iterator Return
        // If an Element is deleted at a given position and the position is the Element with the largest Key in the Map, the Map shall return the end Iterator of the Map.
        // 
        // Satisfies requirement 3929: Map - Erase - Iterator Return
        // If an Element is deleted at a given position, the Map shall return an Iterator to the Element in the Map with a Key next in size.
        // 
        // Satisfies requirement 3928: Map - Erase Position
        // The Map shall be able to delete the Element at a given Iterator position in O(log(n)) time, where n is the number of Elements in the Map.
        // 
        inline Iterator erase(const Iterator& pos)
        {
            Iterator iter( END );
            
            if( isIteratorValid( pos ) )
            {
            	if( pos.thePos != END )
            	{
            		iter = pos;
            		++iter;
            		removeItem( pos.thePos );
            	}
            }
            else
            {
            	RXF::ErrorHandler::error( ERROR_MAP_INVALID_ITERATOR, 0, true );
            }
            
            return iter;
        }
        
        // Satisfies requirement 3968: Map - Erase Key
        // The Map shall be able to delete the Element of a given Key in O(log(n)) time, where n is the number of Elements in the Map.
        // 
        inline bool erase(const Key& key)
        {
            bool erased = false;
            ItemBase* const item = lookUp( root, key );
            if( item != END )
            {
            	removeItem( item );
            	erased = true;
            }
            return erased;
        }
    
    private :
    
        inline void removeItem(ItemBase* const item)
        {
            if( size() == 1 )
            {
            	destroyItem( item );
            	first = nullptr;
            	last = nullptr;
            	root = NIL;
            	emptyEndItem.parent = END;
            }
            else
            {
            	ItemBase* newFirst = first;
            	ItemBase* newLast = last;
            	ItemBase* memory;
            	ItemBase* replacement;
            	
            	// determine future first and last
            	if( item == first )
            	{
            		Iterator iter = Iterator( first );
            		newFirst = (++iter).thePos;
            	}
            	if( item == last )
            	{
            		Iterator iter = Iterator( last );
            		newLast = (--iter).thePos;
            	}
            	
            	// disconnect end items from tree
            	first->left = NIL;
            	last->right = NIL;
            	
            	// erase item from tree and rebalance
            	replacement = item;
            	bool replacement_original_color = replacement->color;
            	if( item->left == NIL )
            	{
            		memory = item->right;
            		rbTransplant( item, item->right );
            	}
            	else if( item->right == NIL )
            	{
            		memory = item->left;
            		rbTransplant( item, item->left );
            	}
            	else
            	{
            		replacement = minimum( item->right );
            		replacement_original_color = replacement->color;
            		memory = replacement->right;
            		if( replacement->parent == item )
            		{
            			memory->parent = replacement;
            		}
            		else
            		{
            			rbTransplant( replacement, replacement->right );
            			replacement->right = item->right;
            			replacement->right->parent = replacement;
            		}
            	
            		rbTransplant( item, replacement );
            		replacement->left = item->left;
            		replacement->left->parent = replacement;
            		replacement->color = item->color;
            	}
            	
            	destroyItem( item );
            	
            	if( replacement_original_color == BLACK )
            	{
            		fixDelete( memory );
            	}
            	
            	// reconnect end items to tree
            	first = newFirst;
            	first->left = first;
            	last = newLast;
            	last->right = END;
            	emptyEndItem.parent = last;
            }
            		
        }
    
    public :
    
        // Satisfies requirement 3931: Map - Clear all
        // The Map shall be able to delete all Elements in the Map in O(n) time, where n is the number of Elements in the Map.
        // 
        inline void clear(void)
        {
            if( !empty() )
            {
            	first->left = NIL;
            	first = nullptr;
            	last->right = NIL;
            	last = nullptr;
            	emptyEndItem.parent = nullptr;
            
            	deleteTree( root );
            	
            	root = NIL;
            	emptyEndItem.parent = END;
            }
        }
    
    private :
    
        inline void deleteTree(ItemBase* const root)
        {
            ItemBase* item = root;
            ItemBase* parent;
            
            while( item != nullptr )
            {
            	if( item->left != NIL )
            	{
            		item = item->left;
            	}
            	else if( item->right != NIL )
            	{
            		item = item->right;
            	}
            	else
            	{
            		parent = item->parent;
            		
            		// disconnet item from tree
            		if( parent != nullptr )
            		{
            			if( parent->left == item )
            			{
            				parent->left = NIL;
            			}
            			else
            			{
            				parent->right = NIL;
            			}
            		}
            		
            		destroyItem( item );
            		item = parent;
            	}
            }
        }
    
    public :
    
        // Satisfies requirement 3934: Map - Find - End Iterator Return
        // If a given Key is not contained in the Map, the Map shall return the end Iterator of the Map.
        // 
        // Satisfies requirement 3933: Map - Find
        // The Map shall be able to return an Iterator pointing to the Element in the Map containing the given Key in O(log(n)) time, where n is the number of elements in the Map.
        // 
        inline Iterator find(const Key& aKey) const
        {
            ItemBase* const item = lookUp( root, aKey );
            return Iterator( item );
        }
        
        // Satisfies requirement 3932: Map - Contains Key
        // The Map shall be able to return whether a Key is contained in the Map or not in O(log(n)) time, where n is the number of Elements in the Map.
        // 
        inline bool contains(const Key& aKey) const
        {
            return find(aKey) != end();
        }
        
        // Argument const T& aValue :
        // The element to find
        // Satisfies requirement 3960: Map - Contains Value
        // The Map shall be able to return whether a Value is contained in the Map or not in O(n) time, where n is the number of Elements in the Map.
        // 
        /* @MISRA_14-6-2=OFF ID-0053: Need to call comparison operator to compare the value of two list elements. */
        inline bool contains_value(const T& aValue) const
        {
            bool status = false;
            
            for( Iterator iter = begin(); iter != end(); ++iter)
            {
            	if( iter.value() == aValue )
            	{
            		status = true;
            		break;
            	}
            }
            
            return status;
        }
        /* @MISRA_14-6-2=ON (end of ID-0053) */
    
    private :
    
        inline void fixInsert(ItemBase* k)
        {
            ItemBase* u;
            while( k->parent->color == RED )
            {
            	if( k->parent == k->parent->parent->right )
            	{
            		u = k->parent->parent->left; // uncle
            		if( u->color == RED )
            		{
            			// case 3.1
            			u->color = BLACK;
            			k->parent->color = BLACK;
            			k->parent->parent->color = RED;
            			k = k->parent->parent;
            		}
            		else
            		{
            			if( k == k->parent->left )
            			{
            				// case 3.2.2
            				k = k->parent;
            				rightRotate(k);
            			}
            			// case 3.2.1
            			k->parent->color = BLACK;
            			k->parent->parent->color = RED;
            			leftRotate( k->parent->parent );
            		}
            	}
            	else
            	{
            		u = k->parent->parent->right; // uncle
            
            		if( u->color == RED )
            		{
            			// mirror case 3.1
            			u->color = BLACK;
            			k->parent->color = BLACK;
            			k->parent->parent->color = RED;
            			k = k->parent->parent;	
            		}
            		else
            		{
            			if( k == k->parent->right )
            			{
            				// mirror case 3.2.2
            				k = k->parent;
            				leftRotate( k );
            			}
            			// mirror case 3.2.1
            			k->parent->color = BLACK;
            			k->parent->parent->color = RED;
            			rightRotate( k->parent->parent );
            		}
            	}
            	if( k == root )
            	{
            		break;
            	}
            }
            root->color = BLACK;
        }
        
        inline void fixDelete(ItemBase* x)
        {
            ItemBase* s;
            while( ( x != root ) && ( x->color == BLACK ) )
            {
            	if( x == x->parent->left )
            	{
            		s = x->parent->right;
            		if( s->color == RED )
            		{
            			// case 3.1
            			s->color = BLACK;
            			x->parent->color = RED;
            			leftRotate( x->parent );
            			s = x->parent->right;
            		}
            
            		if( ( s->left->color == BLACK ) && ( s->right->color == BLACK ) )
            		{
            			// case 3.2
            			s->color = RED;
            			x = x->parent;
            		}
            		else
            		{
            			if( s->right->color == BLACK )
            			{
            				// case 3.3
            				s->left->color = BLACK;
            				s->color = RED;
            				rightRotate( s );
            				s = x->parent->right;
            			} 
            
            			// case 3.4
            			s->color = x->parent->color;
            			x->parent->color = BLACK;
            			s->right->color = BLACK;
            			leftRotate( x->parent );
            			x = root;
            		}
            	}
            	else
            	{
            		s = x->parent->left;
            		if( s->color == RED )
            		{
            			// case 3.1
            			s->color = BLACK;
            			x->parent->color = RED;
            			rightRotate( x->parent );
            			s = x->parent->left;
            		}
            
            		if( ( s->left->color == BLACK ) && ( s->right->color == BLACK ) )
            		{
            			// case 3.2
            			s->color = RED;
            			x = x->parent;
            		}
            		else
            		{
            			if( s->left->color == BLACK )
            			{
            				// case 3.3
            				s->right->color = BLACK;
            				s->color = RED;
            				leftRotate( s );
            				s = x->parent->left;
            			} 
            
            			// case 3.4
            			s->color = x->parent->color;
            			x->parent->color = BLACK;
            			s->left->color = BLACK;
            			rightRotate( x->parent );
            			x = root;
            		}
            	} 
            }
            x->color = BLACK;
        }
        
        inline void leftRotate(ItemBase* const x)
        {
            ItemBase* const y = x->right;
            x->right = y->left;
            if( y->left != NIL )
            {
            	y->left->parent = x;
            }
            
            y->parent = x->parent;
            if( x->parent == nullptr )
            {
            	this->root = y;
            }
            else if( x == x->parent->left )
            {
            	x->parent->left = y;
            }
            else
            {
            	x->parent->right = y;
            }
            
            y->left = x;
            x->parent = y;
        }
        
        inline void rightRotate(ItemBase* const x)
        {
            ItemBase* const y = x->left;
            x->left = y->right;
            if( y->right != NIL )
            {
            	y->right->parent = x;
            }
            
            y->parent = x->parent;
            if( x->parent == nullptr ) 
            {
            	this->root = y;
            }
            else if( x == x->parent->right ) 
            {
            	x->parent->right = y;
            }
            else
            {
            	x->parent->left = y;
            }
            
            y->right = x;
            x->parent = y;
        }
        
        inline void rbTransplant(const ItemBase* const u, ItemBase* const v)
        {
            if( u->parent == nullptr )
            {
            	root = v;
            }
            else if( u == u->parent->left )
            {
            	u->parent->left = v;
            }
            else
            {
            	u->parent->right = v;
            }
            v->parent = u->parent;
        }
        
        inline ItemBase* minimum(ItemBase* item)
        {
            while( item->left != NIL)
            {
            	item = item->left;
            }
            return item;
        }
        
        ////    Attributes    ////
        
        ::std::uint32_t count;
        
        EndItem emptyEndItem;
        
        EndItem* const END;
        
        ItemBase* root;
        
        ItemBase* first;
        
        ItemBase* last;
        
        static NilItem nilItem;
        
        static constexpr ItemBase* NIL = &nilItem;
        
        static constexpr bool RED = true;
        
        static constexpr bool BLACK = false;
        
        MemoryPoolBase& memoryPool;
    };
    
    template <class Key, class T> typename Map<Key,T>::NilItem Map<Key, T>::nilItem;
}

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/RXFContainersStatic/RXF_Map.h
*********************************************************************/

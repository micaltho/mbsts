/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/OMContainers/OMMap.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMMap_H
#define OMMap_H

#include <cstdint>
#include <cstddef>
#include "OMIterator.h"
#include "OMAbstractContainer.h"
// A binary balanced tree map
template <class Key, class Concept> class OMMap : public OMAbstractContainer<Concept> {
public :

    // A map item (node)
    class Item {
    public :
    
        ////    Friend List    ////
        
        friend  class OMMap<Key, Concept>;
        
        
        // Copy constructor
        // Argument const Item& item :
        // The item to copy
        inline Item(const Item& item) : concept(item.concept), key(item.key), larger(item.larger), parent(item.parent), rank(item.rank), smaller(item.smaller)
        {
        }
        
        // Initialize a map item with a key and data
        // Argument Key theKey :
        // The item's key
        // Argument Concept theConcept :
        // The item's data
        inline Item(Key theKey, Concept theConcept) : concept(theConcept), key(theKey), larger(nullptr), parent(nullptr), rank(1), smaller(nullptr)
        {
        }
        
        // Cleanup
        inline virtual ~Item(void)
        {
            removeAll();
        }
        
        // Get the item data
        inline Concept& getConcept(void)
        {
            return concept;
        }
        
        // Assignment operator
        // Argument const Item& item :
        // The item to copy
        inline Item& operator=(const Item& item)
        {
            parent = item.parent;
            smaller = item.smaller;
            larger = item.larger;
            concept = item.concept;	// assuming operator = () for Concept
            key = item.key;
            rank = item.rank;
            return (*this);
        }
    
    private :
    
        // Add an item to this sub tree
        // Argument Item* item :
        // The item to add
        inline void add(Item* item)
        {
            if (item->key <= key) {
            	if (smaller == nullptr) {
            		connectSmaller(item);
            		item->addCheckBalance();
            	} else {
            		smaller->add(item);
            	}
            } else {
            	if (larger == nullptr) {
            		connectLarger(item);
            		item->addCheckBalance();
            	} else {
            		larger->add(item);
            	}
            }
        }
        
        // Balance the sub tree
        inline void addCheckBalance(void)
        {
            if (parent != nullptr) {
            	// not balanced
            	Item* grandpa = parent->parent;
            	if ( (grandpa == nullptr) || (grandpa->rank == rank+1) ) {
            		// balanced or tree of depth 2 (hence balanced)
            	} else {
            		// "this" is unbalanced
            		// Try to "promote"
            		if ( (grandpa->larger!=nullptr && grandpa->smaller!=nullptr) &&
            			 (grandpa->larger->rank == grandpa->smaller->rank) ) {
            			// The two red sons case
            			grandpa->rank++;
            			grandpa->addCheckBalance();
            		} else {
            			// Must do a rotation
            			if (grandpa->smaller==parent) {
            				// The Right rotation case
            				if (parent->smaller == this) {
            					// LL case - make a single right rotation
            					//            grandpa		        parent
            					//		    parent	 d   ===>	this    grandpa
            					//		this	 c             a    b   c      d
            					//	   a	b
            					// connect parent to rest of tree
            					grandpa->connectParent(parent);
            					// connect "c" to grandpa
            					grandpa->connectSmaller(parent->larger);
            					// connect grandpa to parent
            					parent->connectLarger(grandpa);
            				} else {
            					// LR case - make a double right rotation
            					//            grandpa		        this  
            					//		    parent	 d   ===>	parent  grandpa
            					//		  a     this           a     b  c      d
            					//	           b    c
            					// connect this to rest of tree
            					Item* myParent = parent;
            					grandpa->connectParent(this);
            					// Connect "b" to parent
            					myParent->connectLarger(smaller);
            					// Connect "c" to grandpa
            					grandpa->connectSmaller(larger);
            					// connect parent to me
            					connectSmaller(myParent);
            					connectLarger(grandpa);
            				}
            			} else { // grandpa->larger==parent
            				// The Left rotation case
            				if (parent->larger == this) {
            					// RR case - make a single left rotation
            					//    grandpa		                parent
            					//	a 	    parent	     ===>	grandpa   this
            					//		   b     this           a    b   c    d
            					//              c	 d
            					// connect parent to rest of tree
            					grandpa->connectParent(parent);
            					// connect "b" to grandpa
            					grandpa->connectLarger(parent->smaller);
            					// connect grandpa to parent
            					parent->connectSmaller(grandpa);
            				} else {
            					// RL case - make a double left rotation
            					//      grandpa		                this  
            					//		a     parent	===>   grandpa  parent
            					//		    this    d          a     b  c      d
            					//	       b    c
            					// connect this to rest of tree
            					Item* myParent = parent;
            					grandpa->connectParent(this);
            					// Connect "c" to parent
            					myParent->connectSmaller(larger);
            					// Connect "b" to grandpa
            					grandpa->connectLarger(smaller);
            					// connect parent to me
            					connectSmaller(grandpa);
            					connectLarger(myParent);
            				}
            			}
            		}
            	}
            }
        }
        
        // Connect the item to the sub tree
        // Argument Item*& side :
        // The sub tree
        // Argument Item* item :
        // The item to connect
        inline void connect(Item*& side, Item* item)
        {
            side = item;
            if (item != nullptr) {
            	item->parent = this;
            }
        }
        
        // Connect the item to the right sub tree
        // Argument Item* item :
        // The item to connect
        inline void connectLarger(Item* item)
        {
            connect(larger,item);
        }
        
        // Connect the item to the parent sub tree
        // Argument Item* newN :
        // The item to connect
        inline void connectParent(Item* newN)
        {
            if (parent != nullptr) {
            	if (this == parent->smaller) {
            		parent->connectSmaller(newN);
            	} else {
            		parent->connectLarger(newN);
            	}
            } else {
            	if (newN != nullptr) {
            		newN->parent = nullptr;
            	}
            }
        }
        
        // Connect the item to the left sub tree
        // Argument Item* item :
        // The item to connect
        inline void connectSmaller(Item* item)
        {
            connect(smaller,item);
        }
        
        // Find the element in the sub tree
        // Argument const Concept & aConcept :
        // The element to find
        inline Item* find(const Concept & aConcept) const
        {
            Item* anItem = nullptr;
            
            if (aConcept == concept) {
            	// Found in me
            	anItem = const_cast<Item*>(this);
            } else {
            	Item* inSmaller = nullptr;
            	if (smaller) {
            		// Look in smaller
            		inSmaller = smaller->find(aConcept);
            	}
            
            	if (inSmaller != nullptr) {
            		// Found in smaller
            		anItem = inSmaller;
            	} else {
            		if (larger) {
            			// Look in larger
            			anItem = larger->find(aConcept);
            		} else {
            			anItem = nullptr;
            		}
            	}       
            }
            return anItem;
        }
        
        // Find a key in the sub tree - this is an O(log(N)) operation
        // Argument const Key aKey :
        // The key to look for
        inline Item* lookUp(const Key aKey)
        {
            Item* anItem;
            
            if (key == aKey) {
            	anItem = this;
            } else {
            	if (key > aKey) {
            		if (smaller == nullptr) {
            			anItem = nullptr;
            		} else {
            			anItem = smaller->lookUp(aKey);
            		}
            	} else {
            		if (larger == nullptr) {
            			anItem = nullptr;
            		} else {
            			anItem = larger->lookUp(aKey);
            		}
            	}
            }  
            return anItem;
        }
        
        // Cleanup the sub tree
        inline void removeAll(void)
        {
            if (smaller != nullptr) {
            	delete smaller;
            	smaller = nullptr;
            }
            if (larger != nullptr) {
            	delete larger;
            	larger = nullptr;
            }
        }
        
        // Balance the sub tree after remove
        inline void removeCheckBalance(void)
        {
            // Compute minimal rank of sons
            int32_t minRank;
            
            if ( (smaller == nullptr) || (larger == nullptr) ) {
            	minRank = 0;
            } else {
            	if ( smaller->rank < larger->rank) {
            		minRank = smaller->rank;
            	} else {
            		minRank = larger->rank;
            	}
            }
            
            if (rank < minRank + 2) {
            	// My rank is o.k.
            } else {
            	// "this" is unbalanced
            	if ( (smaller == nullptr) || (rank == (smaller->rank + 2)) ) {
            		// Note "larger" cannot be nullptr as "smaller" has the minRank
            		if (larger->rank == rank) {
            			// (d) case - make a single right rotation
            			//              this		               theLarger
            			//		  smaller	theLarger   ===>     this      c   
            			//		            b        c      smaller   b      
            			// connect theLarger to rest of tree
            			Item* theLarger = larger;
            			connectParent(theLarger);
            			// connect "b" to this
            			connectLarger(theLarger->smaller);
            			// connect this to theLarger
            			theLarger->connectSmaller(this);
            			// Check again -- should terminate in one iteration
            			removeCheckBalance();
            		} else {
            			if ( (larger->smaller == nullptr) ||
            				 (larger->smaller->rank == rank - 2) ) {
            				if ( (larger->larger == nullptr) ||
            					 (larger->larger->rank == rank - 2) ) {
            					// Case a - Demotion
            					rank--;
            					if (parent != nullptr) {
            						parent->removeCheckBalance();					
            					}
            				} else { 
            					// case b1. Single right rotation
            					//        this  		            theLarger
            					//	  smaller theLarger  ===>	 this       son
            					//		       b     son     smaller  b    c   d
            					//	                c    d
            					// connect theLarger to rest of tree
            					Item* theLarger = larger;
            					connectParent(theLarger);
            					// Connect "b" to this
            					connectLarger(theLarger->smaller);
            					// Connect this to theLarger
            					theLarger->connectSmaller(this);
            					rank--;
            					theLarger->rank++;
            				}
            			} else {
            				// larger->smaller->rank==rank+1
            				if ( (larger->larger == nullptr) ||
            					 (larger->larger->rank==rank - 2) ) {
            					// case c
            					//          this  		              son  
            					//	 smaller   larger     ===>	  this    larger
            					//		      son    d        smaller  b  c     d
            					//	        b    c
            					// connect son to rest of tree
            					Item* son = larger->smaller;
            					connectParent(son);
            					// Connect "c" to larger
            					larger->connectSmaller(son->larger);
            					// connect larger to son
            					son->connectLarger(larger);
            					// Connect "b" to this
            					connectLarger(son->smaller);
            					// Connect son to this
            					son->connectSmaller(this);
            					rank--;
            					son->rank++;
            				} else {
            					// case b2
            					//        this  		              larger 
            					//	smaller   larger     ===>	 this     son2
            					//		    son1   son2    smaller  son1  d   e
            					//	       b    c  d   e		   b	c
            					// connect theLarger to rest of tree
            					Item* theLarger = larger;
            					connectParent(larger);
            					// connect son1 to this
            					connectLarger(theLarger->smaller);
            					// connect this to theLarger
            					theLarger->connectSmaller(this);
            					rank--;
            					theLarger->rank++;
            				}
            			} 
            		}
            	} else {
            		// The Left rotation case
            		// note smaller cannot be nullptr as larger is the minRank
            		if (smaller->rank == rank) {
            			// (d) case - make a single left rotation
            			//            this		          smaller
            			//		smaller   larger ===>    b     this
            			//	   b     c                        c   larger
            			// connect theSmaller to rest of tree
            			Item* theSmaller = smaller;
            			connectParent(theSmaller);
            			// connect "c" to this
            			connectSmaller(theSmaller->larger);
            			// connect this to theSmaller
            			theSmaller->connectLarger(this);
            			// Check again -- should terminate in one iteration
            			removeCheckBalance();
            		} else {
            			if ( (smaller->larger == nullptr ) ||
            				 (smaller->larger->rank == (rank-2)) ) {
            				if ( (smaller->smaller == nullptr ) ||
            					 (smaller->smaller->rank == (rank-2)) ) {
            					// Case a - Demotion
            					rank--;
            					if (parent != nullptr) {
            						parent->removeCheckBalance();					
            					}
            				} else { 
            					// case b1. Single Left rotation
            					//         this		           smaller
            					//	  smaller  larger ===>	son     this  
            					//	 son   c               a   b   c   larger
            					//	a   b
            					// connect theSmaller to rest of tree
            					Item* theSmaller = smaller;
            					connectParent(theSmaller);
            					// Connect "c" to this
            					connectSmaller(theSmaller->larger);
            					// Connect this to theSmaller
            					theSmaller->connectLarger(this);
            					rank--;
            					theSmaller->rank++;
            				}
            			} else {
            				// smaller->larger->rank==rank+1
            				if ( (smaller->smaller == nullptr ) ||
            					 (smaller->smaller->rank == (rank-2)) ) {
            					// case c
            					//         this 		          son  
            					//	  smaller  larger ===>	smaller  this  
            					//	 a     son             a      b  c   larger
            					//	      b    c
            					// connect son to rest of tree
            					Item* son = smaller->larger;
            					connectParent(son);
            					// connect "b" to smaller
            					smaller->connectLarger(son->smaller);
            					// Connect smaller to son
            						son->connectSmaller(smaller);
            					// Connect "c" to 
            					connectSmaller(son->larger);
            					// Connect son to this
            					son->connectLarger(this);
            					rank--;
            					son->rank++;
            				} else {
            					// case b2
            					//         this 		          smaller
            					//    smaller   larger ===>	  son1      this
            					// son1   son2               a    b  son2   larger
            					//a    b  c   d		                c	 d
            					// connect smaller to rest of tree
            					Item* theSmaller = smaller;
            					connectParent(theSmaller);
            					// connect son1 to this
            					connectSmaller(theSmaller->larger);
            					// connect this to theSmaller
            					theSmaller->connectLarger(this);
            					rank--;
            					theSmaller->rank++;
            				}
            			}
            		}
            	}
            }
        }
        
        // Remove this item from the map
        inline void removeYourSelf(void)
        {
            // make sure I have "smaller==nullptr"
            if (smaller != nullptr) {
            	if (larger != nullptr) {
            		// case    this
            		//		  a    b 
            		// exchange place with my successor in the order
            		Item* item;
            		for (item = larger; item->smaller; item = item->smaller) {
            			// no action
            		}
            		switchNode(item);
            	} else {
            		// case    this
            		//		  a   nullptr
            		// exchange place with 'a' (which must be a leaf)
            		switchNode(smaller);
            	}
            }
            
            // Remove "this" from tree
            connectParent(larger);
            // Update the rank of parent if necessary
            if (parent != nullptr) {
            	parent->removeCheckBalance();
            }
            parent = nullptr;
            smaller = nullptr;
            larger = nullptr;
        }
        
        // Switch tree position with the specified item
        // Argument Item* other :
        // The item to switch with
        inline void switchNode(Item* other)
        {
            // Switch my position in the tree with that of other
            Item* myNewParent;
            Item* hisNewParent;
            Item* myNewSmaller;
            Item* hisNewSmaller;
            Item* myNewLarger;
            Item* hisNewLarger;
            int32_t IShouldBeSmaller=0;
            int32_t HeShouldBeSmaller=0;
            int32_t IShouldBeLarger=0;
            int32_t HeShouldBeLarger=0;
            
            int32_t hisNewRank = rank;
            int32_t myNewRank = rank;
            
            if (parent == other) {
            	hisNewParent = this;
            } else {
            	hisNewParent = parent;
            }
            
            if (larger == other) {
            	hisNewLarger = this;
            } else {
            	hisNewLarger = larger;
            }
            
            if (smaller == other) {
            	hisNewSmaller = this;
            } else {
            	hisNewSmaller = smaller;
            }
            
            if (other->parent == this) {
            	myNewParent = other;
            } else {
            	myNewParent = other->parent;
            }
            
            if (other->larger == this) {
            	myNewLarger = other;
            } else {
            	myNewLarger = other->larger;
            }
            
            if (other->smaller == this) {
            	myNewSmaller = other;
            } else {
            	myNewSmaller = other->smaller;
            }
            
            if (parent != nullptr) {
            	if (parent->smaller == this) {
            		HeShouldBeSmaller = 1;
            	} else {
            		HeShouldBeLarger = 1;
            	}
            }
            
            if (other->parent != nullptr) {
            	if (other->parent->smaller == other) {
            		IShouldBeSmaller = 1;
            	} else {
            		IShouldBeLarger = 1;
            	}
            }  
            
            // Exchange ranks
            rank = myNewRank;
            other->rank = hisNewRank;
            
            // Make the "out" links
            parent = myNewParent;
            larger = myNewLarger;
            smaller = myNewSmaller;
            other->parent = hisNewParent;
            other->larger = hisNewLarger;
            other->smaller = hisNewSmaller;
            // Make the "in" links
            if (HeShouldBeSmaller) {
            	other->parent->smaller = other;
            }
            if (HeShouldBeLarger) {
            	other->parent->larger = other;
            }
            if (IShouldBeSmaller) {
            	parent->smaller = this;
            }
            if (IShouldBeLarger) {
            	parent->larger = this;
            }
            if (smaller) {
            	smaller->parent = this;
            }
            if (larger) {
            	larger->parent = this;
            }
            if (other->smaller) {
            	other->smaller->parent = other;
            }
            if (other->larger) {
            	other->larger->parent = other;
            }
        }
        
        ////    Attributes    ////
        
        // The item data
        Concept concept;
        
        // The item key
        Key key;
        
        // The right sub tree
        Item* larger;
        
        // The parent node in the tree
        Item* parent;
        
        // The item rank in the balanced tree
        ::std::int32_t rank;
        
        // The left sub tree
        Item* smaller;
    };
    
    // Constructor
    inline OMMap(void) : count_(0U), root(nullptr)
    {
    }
    
    // copy constructor
    // Argument const OMMap<Key, Concept>& aMap :
    // The map to copy
    inline OMMap(const OMMap<Key, Concept>& aMap) : count_(0U), root(nullptr)
    {
        copy(aMap);
    }
    
    // Destructor	
    inline virtual ~OMMap(void)
    {
        removeAll();
        root = nullptr;
    }
    
    // Add an element to the map using the provided key.
    // Argument Key aKey :
    // The key
    // Argument Concept aConcept :
    // The data
    inline void add(Key aKey, Concept aConcept)
    {
        Item* item = new Item(aKey,aConcept);
        
        if (root==nullptr) {
        	root = item;
        } else {
        	root->add(item);
        	while (root->parent != nullptr) {
        		root = root->parent;
        	}
        }
        ++count_;
    }
    
    // Get an element from the map using an index
    // Argument const ::std::int32_t anIndex :
    // The index
    inline Concept & getAt(const ::std::int32_t anIndex) const
    {
        void* item; 
        
        getFirst(item);
        for (int32_t j=0; j<anIndex; j++) {
        	if (item != nullptr) {
        		getNext(item);
        	} else {
        		break;
        	}
        }
        return getCurrent(item);
    }
    
    // Get the element with the specified key
    // Argument const Key& aKey :
    // The key
    inline Concept & getKey(const Key& aKey) const
    {
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        Item* item = lookUp(aKey);
        if (item != nullptr) {
          	return item->getConcept();
        } else {
           	return OMNullValue<Concept>::get();
        }
    }
    
    // Check if the map is empty
    inline ::std::int32_t isEmpty(void) const
    {
        return (root == nullptr);
    }
    
    // Find an element in the map based on a key
    // return 1 if found, 0 otherwise
    // Argument const Key & aKey :
    // The key
    // Argument Concept & aConcept :
    // The data found for the specified key (out)
    inline ::std::int32_t lookUp(const Key & aKey, Concept & aConcept) const
    {
        int32_t status = 0;
        Item* item = lookUp(aKey);
        if (item != nullptr) {
        	// Place in "aConcept" the concept referenced by "aKey"
        	aConcept = item->getConcept();
        	status = 1;
        }
        return status;
    }
    
    // Assignment operator
    // Argument const OMMap<Key,Concept> & aMap :
    // The map to copy
    inline OMMap<Key,Concept> & operator=(const OMMap<Key,Concept> & aMap)
    {
        copy(aMap);
        return (*this);
    }
    
    // Get the element in the map using a key
    // Argument const Key & aKey :
    // The key
    inline Concept & operator[](const Key & aKey)
    {
        return getKey(aKey);
    }
    
    // Remove a key from the map
    // Argument Key aKey :
    // The key
    /* @MISRA_17-0-2=OFF XD-0001: Remove must be used here to be complient with OXF API. */
    inline void remove(Key aKey)
    {
        Item* item = lookUp(aKey);
        if (item != nullptr) {
        	removeItem(item);
        }
    }
    /* @MISRA_17-0-2=ON (end of XD-0001) */
    
    // Remove an element from the map
    // Argument Concept aConcept :
    // The element
    #ifndef OMMAP_PARAMS_OF_SAME_TYPE
    /* @MISRA_17-0-2=OFF XD-0001: Remove must be used here to be complient with OXF API. */
    inline void remove(Concept aConcept)
    {
        removeByConcept(aConcept);
    }
    /* @MISRA_17-0-2=ON (end of XD-0001) */
    #endif // OMMAP_PARAMS_OF_SAME_TYPE
    
    // Cleanup
    inline void removeAll(void)
    {
        if (root != nullptr) {
        	delete root; 
        	root = nullptr;
        	count_ = 0;
        }
    }
    
    // Remove an element from the map
    // Argument Concept aConcept :
    // The element
    inline void removeByConcept(Concept aConcept)
    {
        if (root != nullptr) {
        	Item* item = root->find(aConcept);
        	if (item != nullptr) {
        		removeItem(item);
        	}
        }
    }

protected :

    // Get the element at the given position (called by the iterator)
    // Argument void * const pos :
    // The iterator position
    inline virtual Concept & getCurrent(void * const pos) const
    {
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (pos != nullptr)
        {    
        	/* @MISRA_5-2-8+5-2-9,6-6-5=OFF XD-0001: In this case its not possible to have a single return. */
           	return reinterpret_cast<Item*>(pos)->concept;  
           	/* @MISRA_5-2-8+5-2-9,6-6-5=ON (end of XD-0001) */
        } 
        else 
        {    
        	/* @MISRA_14-6-1,6-6-5=OFF XD-0001: In this case its not possible to have a single return. */
           	return OMNullValue<Concept>::get();
           	/* @MISRA_14-6-1,6-6-5=ON (end of XD-0001) */
        }
        
    }
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The map tree-root address (out)
    inline virtual void getFirst(void*& pos) const
    {
        if (root == nullptr) {
        	pos = nullptr;
        } else {
        	// Go to smallest item
        	Item* p = root;
        	while (p->smaller != nullptr) {
        		p = p->smaller;
        	}
        	pos = p;
        }
    }
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The iterator position to advance
    inline virtual void getNext(void*& pos) const
    {
        /* @MISRA_5-2-8+5-2-9=OFF XD-0001: Cast from pointer to pointer. Needs to be done to be generic. */
        Item* p = reinterpret_cast<Item*>(pos);        
        /* @MISRA_5-2-8+5-2-9=ON (end of XD-0001) */
        if (p->larger != nullptr) { // Can we go down ?
        	p = p->larger;
        	while (p->smaller != nullptr) {
        		p = p->smaller;
        	}
        } else { 
        	// Must go up
        	Item* oldP;
        	do {
        		oldP = p;
        		p = p->parent;
        	} while ( (p != nullptr) && (p->larger == oldP) );
        }
        pos = p;
    }

private :

    // Copy a map
    // Argument const OMMap<Key,Concept> & aMap :
    // The map to copy
    inline void copy(const OMMap<Key,Concept> & aMap)
    {
        if (root != aMap.root) {
        	// avoid self copy
        	copy(aMap.root);
        }
    }
    
    // Copy a sub tree
    // Argument const Item* anItem :
    // The sub tree to copy
    inline void copy(const Item* anItem)
    {
        if (anItem != nullptr) {
        	if (anItem->smaller != nullptr) {
        		// recursive copy of smaller
        		copy(anItem->smaller);
        	}
        	if (anItem->larger != nullptr) {
        		// recursive copy of larger
        		copy(anItem->larger);
        	}
        	// actual add to map
        	add(anItem->key, anItem->concept);
        }
    }
    
    // Find an item in the map based on a key
    // Argument const Key & aKey :
    // The key
    inline Item* lookUp(const Key & aKey) const
    {
        Item* item = nullptr;
        
        if (root != nullptr) {
        	item = root->lookUp(aKey);
        }
        return item;
    }
    
    // Remove an item from the map tree
    // Argument Item* anItem :
    // The item to remove
    inline void removeItem(Item* anItem)
    {
        // Make sure we have a "handle to the tree after deletion
        if (anItem == root) {
        	if (root->smaller != nullptr) {
        		root = root->smaller;
        	} else {
        		if (root->larger != nullptr) {
        			root = root->larger;
        		} else {
        			root = nullptr; // Tree will be empty
        		}
        	}
        }
        // Delete the actual element
        if (anItem != nullptr) {
        	anItem->removeYourSelf();
        	delete anItem;
        	--count_;
        }
        // Make sure the handle we have is still the root
        if (root != nullptr) {
        	while (root->parent != nullptr) {
        		root = root->parent;
        	}
        }
    }

public :

    // Returns an Iterator to emtyEndItem to support RXFContainer compatible break conditions.
    inline OMIterator<Concept> begin(void) const
    {
        return OMIterator<Concept>( this );
    }
    
    // Returns an Iterator to emtyEndItem to support RXFContainer compatible break conditions.
    inline OMIterator<Concept> end(void) const
    {
        return OMIterator<Concept>( );
    }
    
    // Check if the list is empty
    inline bool empty(void) const
    {
        return isEmpty();
    }
    
    inline ::std::uint32_t size(void) const
    {
        return count_;
    }
    
    // Get the element with the specified key
    // Argument const Key& aKey :
    // The key
    inline Concept & at(const Key& aKey) const
    {
        return getKey(aKey);
    }
    
    // Add an element to the map using the provided key.
    // Argument const Key& aKey :
    // The key
    // Argument const Concept& aValue :
    // The data
    inline void insert(const Key& aKey, const Concept& aValue)
    {
        return add( aKey, aValue);
    }
    
    inline void erase(const Key& key)
    {
        remove(key);
    }
    
    // Remove all items from list
    inline void clear(void)
    {
        return removeAll();
    }
    
    // Find an element in the map
    // Argument Concept aConcept :
    // The element to find
    inline bool find(Concept aConcept) const
    {
        bool status = false;
        
        if ( root != NULL ) {
        	if ( nullptr != root->find(aConcept) ) {
        		status = true; 
        	}
        }
        return status;
    }
    
    // Find an object in the list
    // Argument const Concept& value :
    // The element to find
    inline bool contains_value(const Concept& value) const
    {
        return find(value);
    }
    
    ////    Attributes    ////

private :

    // The number of elements in the map
    ::std::int32_t count_;
    
    // The tree root
    Item* root;
};

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/OMContainers/OMMap.h
*********************************************************************/

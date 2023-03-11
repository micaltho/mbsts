/**
 *  \brief     Implements a embedded map.
 *  \details   contains data structure and methods for a map template\n
 *             Implementation is much smaller than std::map!
 *             \note the map is capable to hold a fixed numbers of entries!
 *             search algorithm is of complexity O(n)!
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      06.06.2016
 *  \copyright HS Osnabrueck
 */

/** @file */


#ifndef LIB_OSSUPPORT_EMBMAP_H_
#define LIB_OSSUPPORT_EMBMAP_H_


#include <cstring>  // for memcpy
#include <new>      // for std::nothrow


#ifdef DEBUG
#ifndef DEBUG_EMBMAP_API
#define DEBUG_EMBMAP_API
#endif
#endif

#ifdef DEBUG_EMBMAP_API
#include <stdio.h>
#define DEBOUT(x) fprintf(stderr,"*** %s Line %u: %s\n",__FILE__, __LINE__, (x))   ///< print error message

#else
#define DEBOUT(x)                                              ///< no error output!
#endif



namespace RTOS
{

/**
 * \struct EmbPair inc/Embmap.h
 * Defines a pair template for the embedded map.
 *
 */

template <typename T, typename U>
struct EmbPair
{
  T first;    ///< first pair parameter, public access
  U second;   ///< second pair parameter, public access

  /**
   * Constructor
   *
   * @param first  first pair parameter of type T
   * @param second second pair parameter of type U
   */
  EmbPair(T first, U second):first(first), second(second){};
  /**
   * Default Constructor, no initialisation!
   */
  EmbPair() {};
};



/**
 * \class  Embmap inc/Embmap.h
 * Implementation of a memory efficient map.
 * The embedded map is not sorted in any particular way.
 * \note : search complexity O(n)
 */
template <typename T, typename U>
class Embmap
{

public:
    /**
     *
     * @param size size of the map, max. number of elements to store!
     */
    explicit Embmap(size_t size);
    /**
     * deletes allocated memory
     * \note: no destructors of elements are called!
     */
    ~Embmap();

    /**
     * gets iterator to first map element.
     * @return iterator of type \ref EmbPair
     */
    EmbPair<T, U>* begin() const {return m_begin;};
    /**
     * gets iterator to element after last valid map element.
     * @return iterator of type \ref EmbPair
     */
    EmbPair<T, U>* end() const   {return m_end;};

    /**
     * get reference to second (value) of map entry belonging to key.\n
     * If key is not found, a new map element is inserted of type \ref EmbPair <T, U>(key, 0)
     * is inserted!
     * @param key   key of map entry.
     * @return      reference to value belonging to key
     */
    U &operator[](const T& key);

    /**
     * delete map entry
     * @param key key of element to delete
     * @return number of elements delete: 0 if key was not found, else 1
     *
     */
    size_t erase(const T& key);

    /**
     * find element for key
     * @param key key of element to find
     * @return iterator of type \ref EmbPair
     *   points to found entry or to \ref end() if entry is not found
     */

    EmbPair<T, U>* find(const T& key);
    /**
     * find element for key
     * @param key key of element to find
     * @return const iterator of type \ref EmbPair
     *   points to found entry or to \ref end() if entry is not found
     */
    const EmbPair<T, U>* find(const T& key) const;

    /**
     * insert new \ref EmbPair <T, U> in map
     * @param val new pair to insert
     * @return iterator of type \ref EmbPair with template parameters:\n
     *   first: \ref EmbPair <T, U>* iterator to inserted pair.\n
     *   second: bool, true if pair was inserted, else false (no memory)\n
     *   If key is found in map, old value is overwritten!
     *
     */
    EmbPair<EmbPair<T, U>*, bool> insert(const EmbPair<T, U>& val);

private:
    Embmap(const Embmap &)            = delete;
    Embmap(const Embmap &&)           = delete;
    Embmap& operator=(const Embmap&)  = delete;
    const Embmap& operator=(Embmap&&) = delete;

    size_t         m_size;      ///< size of map, max. number of elements
    size_t         m_elements;  ///< numberof stored elements (max. \ref m_size)
    EmbPair<T, U>* m_map;       ///< map data, dynamic memory / heap
    EmbPair<T, U>* m_begin;     ///< iterator to first map element
    EmbPair<T, U>* m_end;       ///< iterator after last map element

    U              m_error;    ///< reference to m_error is returned in case of full map

};

template <typename T, typename U>
Embmap<T, U>::Embmap(size_t size) :
   m_size(size), m_elements(0),
   m_map(nullptr), m_begin(nullptr), m_end(nullptr)
{
    m_map   = new(std::nothrow) EmbPair<T, U>[size];
    m_end   = m_map;
    m_begin = m_map;
    if (nullptr == m_map)
    {
        DEBOUT("coudn't get memory");
        m_size = 0;
    }
}

template <typename T, typename U>
Embmap<T, U>::~Embmap()
{
   delete [] m_map;
}

template <typename T, typename U>
U& Embmap<T, U>::operator[](const T& key)
{
    EmbPair<T, U> *it = find(key);
    if (it == m_end)
    {
      U a {m_error};
      if (false == (insert(EmbPair<T, U> (key, a))).second)
      {
         return m_error;
      }
    }
    return it->second;
}

template <typename T, typename U>
size_t Embmap<T, U>::erase(const T&  key)
{
    size_t ret = 0;
    if(!m_elements) return ret;
    EmbPair<T, U> *it = find(key);
    if (it != m_end)
    {
      // we found something....
      if (it != m_end - 1)
      {
          // if element is not last element in list, overwrite it with last
          *it = *(m_end -1);
      }
        --m_end;
      --m_elements;
      ret = 1;
    }
    return ret;
}


template <typename T, typename U>
const EmbPair<T, U>* Embmap<T, U>::find(const T& key) const
{
   if(!m_elements) return m_end;
   EmbPair<T, U> *it = nullptr;
   for (it = m_begin; it != m_end; ++it)
   {
      if(it->first == key)
      {
          return it;
      }
   }
   return it;
}

template <typename T, typename U>
EmbPair<T, U>* Embmap<T, U>::find(const T& key)
{
    const Embmap<T, U> *ptr = this;
    const EmbPair<T, U>* cret = ptr->find(key);
    EmbPair<T, U>* ret = const_cast<EmbPair<T, U>*>(cret);

    return ret;
}


template <typename T, typename U>
EmbPair<EmbPair<T, U>*, bool> Embmap<T, U>::insert(const EmbPair<T, U>& val)
{
    EmbPair<EmbPair<T, U>*, bool> ret(nullptr,false);

    if (m_size == m_elements)
    {
        DEBOUT("insert(): No free map space");
        return ret;
    }

    EmbPair<T, U>* it = find(val.first);
    *it = val;
    if(it == m_end)
    {
        ++m_end;
        ++m_elements;
    }
    ret.first  = it;
    ret.second = true;

    return ret;
}



} /* namespace RTOS */

#endif /* LIB_OSSUPPORT_EMBMAP_H_ */

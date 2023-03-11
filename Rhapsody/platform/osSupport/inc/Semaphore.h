/**
 *  \brief     Implements a counting semaphore.
 *  \details   Semaphore is created and registered to RTOS.\n
 *             Semaphores might be deleted
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      24.09.2015
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */

/** @file */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "utility.h"   // from platform/framework
#include <cstdint>
#include <cstddef>   // for std::ptrdiff_t
#ifdef DEBUG
#include <cstdio>    // for error messages
#endif
#include <cmsis_os.h>


namespace RTOS
{

/**
 * \class Semaphore inc/Semaphore.h
 * Defines a counting semaphore.
 */
class Semaphore
{
public:
    /**
     * Constructor
     * @param semDef    definition of semaphore, \ref osSemaphoreDef_t.
     * @param initValue initial value of used resources.
     */
    explicit Semaphore(const osSemaphoreDef_t *semDef,
                       uint32_t initValue);

    /**
     * Default move constructor
     * @param [in] m Semaphore
     */
    Semaphore(Semaphore&& m) = default;

    /**
     * Destructor, RTOS resource is freed.
     */
    ~Semaphore();
    /**
     * increase number of available resources.
     * @return true if success.
     */
    bool up();
    /**
     * decrease number of available resources.\n
     * Block if no resource is available
     * @return true if success, false if timeout.
     */
    bool down();
    /**
     * getter for name.
     * @return debug name of semaphore
     */
    const char* getName() const  { return m_name;}
    /**
     * get number of available resources.
     * @return available resources.
     * \note the RTOS implementation of the counter is not thread save. A race condition is
     *       possible. So be careful when using the returned value
     */
    int32_t            getValue() const { return m_value; }
    /**
     * Set timeout for lock attempt.\n
     * Default is \ref osWaitForever.
     * @param [in] timeout new timeout value in milliseconds
     */
    void   setTimeout(uint32_t timeout) { m_timeout = timeout;}

private:
    Semaphore() = delete;
    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&)  = delete;
    const Semaphore& operator=(Semaphore&&) = delete;


    osSemaphoreId  m_sema;
    int32_t        m_value;
    uint32_t       m_timeout;
    const char*    m_name;
};


/**
 * \class counting_semaphore inc/Semaphore.h
 * Defines a counting semaphore.
 * The interface is compatible with std::counting_semaphore
 * from since C++20
 * {\note NOT FULLY TESTED YET!!!!!\n}
 *
 *
 *  A counting_semaphore is a lightweight synchronization primitive that can control
 *  access to a shared resource.
 *  Unlike a std::mutex, a counting_semaphore allows more than one concurrent access to the
 *  same resource, for at least LeastMaxValue concurrent accessors. The program is ill-formed
 *  if LeastMaxValue is negative.
 *  \tparam LeastMaxValue max count of semaphore.\n
 *   \note in this implementation all semaphores have a max Value of osFeature_Semaphore
 */

template<std::ptrdiff_t LeastMaxValue = osFeature_Semaphore >
class counting_semaphore
{
public:
     /**
     * Constructor
     * Constructs an object of type RTOS::counting_semaphore with the internal
     * counter initialized to desired.
     * @param [in] desired   initial value of used resources
     * @param [in] name   debug name of semaphore.
     *   \note this parameter is not compliant to C++20
    */
    explicit counting_semaphore( std::ptrdiff_t desired, const char* name= "stdSema" );

    /*
     * Copy constructor is deleted.
     */
    counting_semaphore( const counting_semaphore& ) = delete;

    /**
     * Destructor, RTOS resource is freed.
     * Destroys the counting_semaphore object.
     *  The behavior is undefined if any thread is concurrently calling any
     *  other member function on this semaphore.
     *  This includes threads blocked in acquire(), try_acquire_for(), or
     *  try_acquire_until().
     */
    ~counting_semaphore();

    /**
     * Atomically increments the internal counter by the value of update.
     * Any thread(s) waiting for the counter to be greater than ​0​, such as
     * due to being blocked in acquire, will subsequently be unblocked.
     *
     * @param [in] update - the amount to increment the internal counter by
     */
     void release(std::ptrdiff_t update = 1);

    /**
     * Atomically decrements the internal counter by 1 if it is greater than ​0​;
     * otherwise blocks until it is greater than ​0​ and can successfully decrement
     * the internal counter.
     */
     inline void acquire()
     {
         try_acquire_for(osWaitForever);
     }

    /**
     * Tries to atomically decrement the internal counter by 1 if it is
     * greater than ​0​; no blocking occurs regardless.
     * @return true if it decremented the internal counter, otherwise false
     */
    inline bool try_acquire()
    {
        return try_acquire_for(0);
    }

    /**
     * Tries to atomically decrement the internal counter by 1 if it is
     * greater than ​0​; otherwise blocks until it is greater than ​0​ and
     * can successfully decrement the internal counter, or the ms
     * duration has been exceeded.
     * @param [in] ms -the minimum duration the function must wait
     * for to fail
     * @return true if it decremented the internal counter, otherwise false
     */
    bool try_acquire_for(uint32_t ms);

    /**
     * Tries to atomically decrement the internal counter by 1 if it is
     * greater than ​0​; otherwise blocks until it is greater than ​0​ and
     * can successfully decrement the internal counter, or the abs_time
     * time point has been passed.
     * @param [in] abs_time - the earliest time the function must wait
     * until in order to fail
     * @return true if it decremented the internal counter, otherwise false
     */
    bool try_acquire_until(uint32_t abs_time);

    /**
     * eturns the internal counter's maximum possible value, which is greater
     * than or equal to LeastMaxValue.
     * Note: For specialization binary_semaphore, LeastMaxValue is equal to 1.
     * As its name indicates, the LeastMaxValue is the minimum max value,
     * not the actual max value. Thus max() can yield a number larger than
     * LeastMaxValue.
     * @return The internal counter's maximum possible value, as a std::ptrdiff_t.
     */
    static constexpr std::ptrdiff_t max() {return LeastMaxValue;}
private:
    counting_semaphore() = delete;
    counting_semaphore& operator=(const counting_semaphore&)  = delete;
    const counting_semaphore& operator=(counting_semaphore&&) = delete;


    osSemaphoreId  m_sema;
    std::ptrdiff_t m_value;
    uint32_t       m_timeout;
    const char*    m_name;

};


/**
 *  @ Implemantation:
 *
 */
template<std::ptrdiff_t LeastMaxValue>
counting_semaphore<LeastMaxValue>::counting_semaphore(std::ptrdiff_t desired, const char* name) :
   m_sema(0),
   m_value(desired),
   m_timeout(osWaitForever),
   m_name("RTOS::counting_semaphore")
{
    // check if template parameter is in allowed range (1... osFeature_Semaphore)
    BUILD_BUG_ON_ZERO(osFeature_Semaphore < LeastMaxValue);
    BUILD_BUG_ON_ZERO(1 > LeastMaxValue);
#if DEBUG
    if (osFeature_Semaphore < LeastMaxValue)
    {
        fprintf(stderr,"*** %s %d invalid LeastMaxValue!\n", __FILE__, __LINE__);
    }
#endif
    osSemaphoreDef_t semdef = {0, name};
    m_sema = osSemaphoreCreate(&semdef, desired);
}


template<std::ptrdiff_t LeastMaxValue>
counting_semaphore<LeastMaxValue>::~counting_semaphore()
{
  if (m_sema)
  {
     osSemaphoreDelete(m_sema);
  }
}


template<std::ptrdiff_t LeastMaxValue>
void counting_semaphore<LeastMaxValue>::release(std::ptrdiff_t update)
{
  if (m_sema)
  {
    for(std::ptrdiff_t i = 0; i < update; ++i)
    {
        if ( osOK == osSemaphoreRelease(m_sema) )
        {
            ++m_value;
        }
    }
  }
#ifdef DEBUG
  else
  {
     fprintf(stderr,"*** %s %d Try release() on nullptr!\n", __FILE__, __LINE__);
  }
#endif
}



template<std::ptrdiff_t LeastMaxValue>
bool counting_semaphore<LeastMaxValue>::try_acquire_for(uint32_t ms)
{
  bool ret = false;
  if (m_sema)
  {
    int32_t numAvailToken = osSemaphoreWait(m_sema, ms);
    // race condition in osSemaphoreWait or on m_value-access
    // or thread switch
    // semaphore itself is thread save, but m_value might get wrong value.
    // m_value might be used as a "hint" .
    if (0 == numAvailToken)
    {
        // timeout:
        ret = false;
    }
    else if ( -1  !=  numAvailToken)
    {
        m_value = numAvailToken;
        ret = true;
    }
#ifdef DEBUG
    else
    {
        fprintf(stderr,"*** %s %d acquire() failed!\n", __FILE__, __LINE__);
    }
#endif
  }
#ifdef DEBUG
  else
  {
     fprintf(stderr,"*** %s %d Try acquire() on nullptr!\n", __FILE__, __LINE__);
  }
#endif
  return ret;
}


template<std::ptrdiff_t LeastMaxValue>
bool counting_semaphore<LeastMaxValue>::try_acquire_until(uint32_t abs_time)
{
   uint32_t now = osKernelSysTick();
   uint32_t then = abs_time - (now / osKernelSysTickFrequency * 1000);
   return try_acquire_for(then);
}


/**
 *! \class binary_semaphore<1> inc/Semaphore.h
 * binary_semaphore is an alias for specialization of RTOS::counting_semaphore with
 *  LeastMaxValue being 1.
 *  Implementations may implement binary_semaphore more efficiently than the default
 *  implementation of RTOS::counting_semaphore.
 */
using binary_semaphore = RTOS::counting_semaphore<1>;



}  // namespace RTOS

#endif /* SEMAPHORE_H_ */

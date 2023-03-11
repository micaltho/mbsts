/**
 *  \brief     Implements a mutex.
 *  \details   Mutex are created and registered to RTOS.\n
 *             Mutexes might be deleted
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      24.09.2015
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */

/** @file */


#ifndef MUTEX_H_
#define MUTEX_H_

#include <cmsis_os.h>

namespace RTOS
{

/**
 * \class Mutex inc/Mutex.h
 * Defines a binary semaphore.
 */
class Mutex
{
public:
    /**
     * \typedef native_handle_type
     * This type is used in C++11 compliant mutexes. \n
     * The type is implementation-specific! We give back CMSIS \ref osMutexId
     */
	typedef osMutexId native_handle_type;

	/**
     * Constructor of Mutex
     * @param mutexDef definition of mutex, \ref osMutexDef_t
     */
    explicit Mutex(const osMutexDef_t *mutexDef);
    /**
     * Default move constructor
     * @param [in] m Mutex
     */
    Mutex(Mutex&& m) = default;
    /**
     * Destructor, RTOS resource is freed.
     */
    virtual ~Mutex();

    /**
     * \brief Lock the mutex.
     *
     * @return true if success, false if timeout occurred
     */
    bool lock() const;

    /**
     * \brief Lock \ref Mutex if not locked.
     *
     * Attempts to lock the \ref Mutex, without blocking:\n
     *  \li If the \ref Mutex isn't currently locked by any thread, the calling
     *  thread locks it (from this point, and until its member unlock is called,
     *  the thread owns the mutex).\n
     *  \li If the \ref Mutex is currently locked by another thread, the function
     *  fails and returns false, without blocking (the calling thread continues
     *  its execution).
     *  \li If the \ref Mutex is currently locked by the same thread calling this
     *  function, it produces a deadlock (with undefined behavior).
     *
     *  This function may fail spuriously when no other thread has a lock
     *  on the \ref Mutex, but repeated calls in these circumstances shall
     *  succeed at some point.
     *
     * @return true if the function succeeds in locking the \ref Mutex
     *  for the thread.\n
     *         false otherwise.
     */
    bool try_lock() const;

    /**
     * \brief Unlock the mutex.
     *
     *
     *
     */
    void unlock() const  {if (m_mutex) osMutexRelease( m_mutex );};

    /**
     * \brief Get native handle
     *
     * This member function is only present in class mutex
     * if the library implementation supports it.\n
     *  If present, it returns a value used to access implementation-specific
     *  information associated to the object.
     *  @return A value of member type \ref Mutex::native_handle_type.
     */
    osMutexId native_handle() const {return m_mutex;}


    /**
     * get debug name.
     * @return name of the mutex
     */

    const char* getName() const { return m_name;}
    /**
     * Set timeout for lock attempt.\n
     * Default is \ref osWaitForever.
     * @param [in] timeout new timeout value in milliseconds
     */
    void  setTimeout(uint32_t timeout) { m_timeout = timeout;}

private:
    Mutex() = delete;
    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&)  = delete;
    const Mutex& operator=(Mutex&&) = delete;

    osMutexId    m_mutex;
    uint32_t     m_timeout;
    const char*  m_name;
};

/**
 * \class RTOS::lock_guard inc/Mutex.h
 * A lock guard is an object that manages a \ref Mutex object by keeping it always
 *  locked.\n
 * On construction, the \ref Mutex object is locked by the calling thread,
 * and on destruction, the \ref Mutex is unlocked.\n
 * It is the simplest lock, and is specially useful as an object with automatic
 * duration that lasts until the end of its context.\n
 *  In this way, it guarantees the \ref Mutex object is properly unlocked
 *  Note though that the lock_guard object does not manage the lifetime
 *  of the \ref Mutex object in any way: \n the duration of the \ref Mutex object shall
 *  extend at least until the destruction of the lock_guard that locks it.
 */
class lock_guard
{
    RTOS::Mutex& m_mutex;
public:
    /**
    *  Constructs a \ref lock_guard object that keeps \a m locked.
    * @param m  \ref Mutex object to be managed by the \ref lock_guard object.
    */
    lock_guard(RTOS::Mutex& m):m_mutex(m)
    {
        m_mutex.lock();
    }
    /**
    *  Destroys the \ref lock_guard object.
    *  Before that, the destructor calls the unlock member of the \ref Mutex object it manages.
    * \note
    * that this does not destroy the managed mutex object.
    */
    ~lock_guard() {m_mutex.unlock();}
};


/**
 * \b unique_lock
 * A unique lock is an object that manages a \ref Mutex object with unique
 * ownership in both states: \a locked and \a unlocked.\n\n
 * On construction , the object acquires a \ref Mutex object, for whose
 * locking and unlocking operations becomes responsible.\n\n
 * The object supports both states: \a locked and \a unlocked.\n\n
 * This class guarantees an unlocked status on destruction (even if not called
 * explicitly). Therefore it is especially useful as an object with automatic
 * duration, as it guarantees the \ref Mutex object is properly unlocked.\n\n
 *
 * Note though, that the \ref unique_lock object does not manage the lifetime
 * of the \ref Mutex object in any way: the duration of the \ref Mutex object
 * shall extend at least until the destruction of the \ref unique_lock that
 * manages it.
 */
class unique_lock
{
    RTOS::Mutex* m_mutex = nullptr;
    bool  owningState = false;
public:
    /**
    *  Constructs a \ref unique_lock object that keeps \a m locked.
    * @param m  \ref Mutex object to be managed by the \ref unique_lock object.
    */
    unique_lock(RTOS::Mutex& m):m_mutex(&m) {m.lock();}

    /**
    *  Destroys the \ref unique_lock object.
    *  Before that, the destructor calls the unlock member of the \ref Mutex object it manages.
    * \note
    * that this does not destroy the managed \ref Mutex object.
    */
    ~unique_lock() {if (m_mutex) m_mutex->unlock();}

    unique_lock& operator= (const unique_lock&) = delete;   ///< deleted
    unique_lock(const unique_lock&) = delete;               ///< deleted

    /**
     * \brief Lock mutex
     *
     * Calling lock on a \ref Mutex object that has already been locked by
     * other threads causes the current thread to block (wait) until it can
     * own a lock to it.\n
     * When the function returns, the object \a owns a lock on the \ref Mutex.
     * @returns none
     *
     */
    void lock() {if (m_mutex) m_mutex->lock();}

    /**
     * \brief Lock mutex if not locked
     *
     * Calls member \ref try_lock of the managed \ref Mutex object, and uses
     * the returned value to set the \a owning state.\n\n
     * If the owning state is already true before the call, or if the object
     * currently manages no mutex object, the function returns true.
     * @returns true if the function succeeds in locking the managed mutex object.\n
     * false otherwise.
     *
     */
    bool try_lock();

    /**
     * \brief unlock mutex
     *
     * Calls member \ref unlock of the managed \ref Mutex object,
     * and sets the owning state to false.
     *
     * @returns none
     *
    */
    void unlock();

    /**
     *  \brief Returns whether the object owns a lock.
     *
     * This is true if the managed \ref Mutex object was locked by the
     * \ref unique_lock object, and hasn't been \a unlocked or \a released since.\n\n
     * In all other cases, it is false.\n\n
     * This is an alias of unique_lock::operator bool
     *
     *
     * @returns  true is the object owns a lock on the managed
     * \ref Mutex object.\n
     * false otherwise.
     *
     */
    bool owns_lock() {return owningState;}

    /**
     *  \brief Returns whether the object owns a lock.
     *
     * This is true if the managed \ref Mutex object was locked by the
     * \ref unique_lock object, and hasn't been \a unlocked or \a released since.\n\n
     * In all other cases, it is false.\n\n
     * This is an alias of \ref unique_lock::owns_lock
     *
     * @returns  true is the object owns a lock on the managed
     * \ref Mutex object.\n
     * false otherwise.
     *
     */
    operator bool () {return owns_lock();}

    /**
     * \brief Move-assign \ref unique_lock
     *
     * Replaces the managed \ref Mutex object by the one in \a x,
     * including its owning state.\n
     * If the object owned a lock on its managed \ref Mutex object before
     * the call, its \ref Mutex::unlock member is called before being replaced.\n
     * \a x is left in the same state as if default-constructed (referring
     * to no \ref Mutex object).
     *
     * @param[inout] x Another \ref unique_lock object.
     * @returns *this
     */
    unique_lock& operator=(unique_lock&& x) noexcept;



    /**
     * \brief Swap unique locks
     *
     * Exchanges contents with \a x, including both the managed \ref Mutex objects
     * and their current owning states.
     *
     * @param[inout] x Another \ref unique_lock object.
     * @returns none
     */
    void swap (unique_lock& x) noexcept;

    /**
     * \brief Release \ref Mutex
     *
     * Returns a pointer to the managed \ref Mutex object, releasing ownership
     * over it.\n\n
     * After the call, the \ref unique_lock object no longer manages any
     * \ref Mutex object (i.e., it is left in the same state as a if
     * default-constructed).\n\n
     * Note that this function does not lock nor unlock the returned \ref Mutex object.
     *
     * @returns A pointer to the \ref Mutex object managed by the
     * \ref unique_lock before the call.
     */
    Mutex* release() noexcept;
};


}  // namespace RTOS

#endif /* MUTEX_H_ */

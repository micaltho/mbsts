/*
 * Mutex.cpp
 *
 *  Created on: 14.09.2015
 *      Author: Wuebbelmann
 */

#include <Mutex.h>

namespace RTOS
{

Mutex::Mutex(const osMutexDef_t *mutexDef) :
   m_mutex(0),
   m_timeout(osWaitForever),
   m_name(mutexDef->name)
{
	m_mutex = osMutexCreate(mutexDef);
}

Mutex::~Mutex()
{
  if (m_mutex)
  {
     osMutexDelete(m_mutex);
  }
}

bool Mutex::lock() const
{
  bool state = false;
  if (m_mutex)
  {
	if (osOK == osMutexWait( m_mutex, m_timeout ))
	{
	    state = true;
	}
  }
  return state;
}

bool Mutex::try_lock() const
{
  bool state = false;
  if (m_mutex)
  {
	if (osOK == osMutexWait( m_mutex, 0 ))  // lock without timeout
	{
	    state = true;
	}
  }
  return state;
}


bool unique_lock::try_lock() {
	if (!owningState && m_mutex)
	{
		owningState = m_mutex->try_lock();
	}
    return owningState;
}

void unique_lock::unlock() {
	if (owningState && m_mutex)
	{
		m_mutex->unlock();
		owningState = false;
	}
}

unique_lock& unique_lock::operator=(unique_lock&& x) noexcept
{
    if(owns_lock())
    {
        m_mutex->unlock();
    }
    m_mutex     = x.m_mutex;
    owningState = x.owningState;
    x.m_mutex = nullptr;
    x.owningState = false;

    return *this;
}

void unique_lock::swap (unique_lock& x) noexcept
{
    Mutex * tmpMp = m_mutex;
    bool tmpOwS   = owningState;

    m_mutex     = x.m_mutex;
    owningState = x.owningState;

    x.m_mutex     = tmpMp;
    x.owningState = tmpOwS;
}

Mutex* unique_lock::release() noexcept
{
   Mutex *mutex = m_mutex;
   m_mutex = nullptr;
   owningState = false;
   return mutex;
}

}  // namespace RTOS


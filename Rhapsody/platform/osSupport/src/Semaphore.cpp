/*
 * Semaphore.cpp
 *
 *  Created on: 14.09.2015
 *      Author: Wuebbelmann
 */

#include <Semaphore.h>
#include <cstdio>
namespace RTOS
{

Semaphore::Semaphore(const osSemaphoreDef_t *semDef,
                     uint32_t initValue) :
   m_sema(0),
   m_value(initValue),
   m_timeout(osWaitForever),
   m_name(semDef->name)
{
    m_sema = osSemaphoreCreate(semDef, initValue);
}

Semaphore::~Semaphore()
{
  if (m_sema)
  {
     osSemaphoreDelete(m_sema);
  }
}


bool Semaphore::up()
{
  bool status = false;
  if (m_sema)
  {
     if ( osOK == osSemaphoreRelease(m_sema) )
     {
        status = true;
         ++m_value;
     }
  }
#ifdef DEBUG
  else
  {
     fprintf(stderr,"*** %s %d Try up() on nullptr!\n", __FILE__, __LINE__);
  }
#endif
  return status;

}


bool Semaphore::down()
{
  bool status = false;
  if (m_sema)
  {
    int32_t numAvailToken = osSemaphoreWait(m_sema, m_timeout);
    // race condition in osSemaphoreWait or on m_value-access
    // or thread switch
    // semaphore itself is thread save, but m_value might get wrong value.
    // m_value might be used as a "hint" .
    --m_value;
     if ( -1  !=  numAvailToken)
     {
        status = true;
     }
  }
#ifdef DEBUG
  else
  {
     fprintf(stderr,"*** %s %d Try down() on nullptr!\n", __FILE__, __LINE__);
  }
#endif
   return status;
}

}  // namespace RTOS

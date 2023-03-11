/*
 * TimerBase.cpp
 *
 *  Created on: 18.09.2015
 *      Author: Wuebbelmann
 */

/** @file */

#include "TimerBase.h"

#ifdef __cplusplus
extern "C" {
#endif

// this is the function for RTOS timer.
// This function calls the timer handler.
static void timerFnc(void *para)
{
   // para is "this" pointer of timer's object!
  RTOS::TimerBase *obj = reinterpret_cast<RTOS::TimerBase *>(para);
   obj->m_timer();
}

#ifdef __cplusplus
}
#endif

namespace RTOS
{

// Const and Dstr
TimerBase::TimerBase(const char* const pcName,
                     uint32_t  period,
                     os_timer_type type)
   : m_name((char *)pcName),
     m_type(type),
     m_period(period),
     m_handle(0)
{
   osTimerDef_t timerDef;
   timerDef.ptimer = reinterpret_cast<os_ptimer>(timerFnc);
   timerDef.name   = m_name;
   m_handle = osTimerCreate (&timerDef, m_type, (void *)this);

}


TimerBase::~TimerBase()
{
   // remove timer from RTOS
   if(m_handle)
   {
      osTimerDelete(m_handle);
   }
}

bool TimerBase::startTimer() const
{
   bool xcode  = true;
   if (osOK !=  osTimerStart (m_handle, m_period))
   {
      xcode = false;
   }


   return xcode;
}
// stop RTOS timer
bool TimerBase::stopTimer() const
{
   bool     xcode  = true;
   if (osOK !=  osTimerStop (m_handle))
   {
      xcode = false;
   }
   return xcode;

}

void TimerBase::setPeriod(uint32_t period)
{
   m_period = period;
}

}  // namespace RTOS


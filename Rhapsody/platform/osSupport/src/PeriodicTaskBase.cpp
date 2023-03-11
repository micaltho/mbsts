/*
 * PeriodicTaskBase.cpp
 *
 *  Created on: 09.10.2015
 *      Author: Wuebbelmann
 */
/** @file */


#include <PeriodicTaskBase.h>

namespace RTOS
{


PeriodicTaskBase::PeriodicTaskBase(const char * const name,
                                   uint16_t    stackDepth,
                                   osPriority  priority,
                                   uint32_t    period,
                                   bool        immidiateStart):
         RTOS::Task(name, stackDepth, priority, immidiateStart),
         m_timer(this, name, period){if (immidiateStart) m_timer.startTimer();}



}   // namespace RTOS





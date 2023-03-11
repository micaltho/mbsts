/**
 *  \brief     Base Class for RTOS periodic tasks.
 *  \details   Tasks might inherit from this class.
 *             Tasks are registered to RTOS, the m_task method is called as task code.
 *             The tasks generate a SW timer which sends a TIMEREVENT to this task
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      09.10.2015
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef PERIODICTASKBASE_H_
#define PERIODICTASKBASE_H_

#include <TaskBase.h>
#include <TimerBase.h>

namespace RTOS
{

/**
 *  \class PeriodicTaskBase inc/PeriodicTaskBase.h
 *  Pure virtual base class for periodic tasks.
 *  Tasks must inherit this class and implement the m_task method!
 *  This base class implements a SW timer which sends periodically a TIMEREVENT
 *  to task.
 */
class PeriodicTaskBase: public Task
{
public:
   /**
    * gets handle of periodic timer.
    * @return timer handle.
    */
    osTimerId  getTimerHandle() const {return getTimer().getTimerHandle();}

    /**
     * starts timer associated with periodic task
     * @return true if success
     */
    bool startTimer() const  {return getTimer().startTimer();}

    /**
     * stops timer associated with periodic task
     * @return true if success
     */
    bool stopTimer()  const  {return getTimer().stopTimer();}


protected:
    /**
     * Constructor of pure virtual class PeriodicTaskBase
     * @param [in] name       name of task, debugging purpose
     * @param [in] stackDepth stack of task
     * @param [in] priority   priority of task, see \ref osPriority
     * @param [in] period     period of associated timer
     * @param [in] immidiateStart is task scheduled after creation or after \ref createTask call
     */
    PeriodicTaskBase(const char * const name,
                     uint16_t    stackDepth,
                     osPriority  priority,
                     uint32_t    period,
                     bool        immidiateStart = true);

    /**
     * returns reference to timer.
     * Task may change period etc.
     *
     * @return timer reference
     */
    const TimerBase& getTimer() const {return m_timer;}


private:
    class MyTimer: public RTOS::TimerBase
    {
    public:
          MyTimer(Task *task,
                  const char * const     pcName,
                  uint32_t               period):
               TimerBase(pcName, period),m_task(task) {};

          void m_timer() override {osSignalSet(m_task->getTaskHandle(), TIMEREVENT);};
     private:
          Task *m_task;
    };

     MyTimer m_timer;

     // delete default, copy, move constructor...
     PeriodicTaskBase() = delete;
     PeriodicTaskBase(const PeriodicTaskBase&) = delete;
     PeriodicTaskBase& operator=(const PeriodicTaskBase&)  = delete;
     const PeriodicTaskBase& operator=(PeriodicTaskBase&&) = delete;
};

}  // // namespace RTOS

#endif /* PERIODICTASKBASE_H_ */

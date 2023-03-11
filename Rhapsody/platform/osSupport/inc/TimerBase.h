/**
 *  \brief     Base Class for RTOS timers.
 *  \details   Timers might inherit from TimerBase.
 *             Timers are registered to RTOS, the m_timer method is called after timer expires
 *             Timers can be implemented as single shot or repetitive timers
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      24.09.2015
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */


#ifndef TIMERBASE_H_
#define TIMERBASE_H_
/** @file */

#include <cmsis_os.h>

namespace RTOS
{
/**
 * pure virtual base class for all timers.
 * timers must inherit this class and implement the m_timer method!
 */
class TimerBase
{
protected:
    char *        m_name;       ///< name of Timer, debugging purpose
    os_timer_type m_type;       ///< type, see \ref os_timer_type
    uint32_t      m_period;     ///< period in milliseconds
    osTimerId     m_handle;     ///< timer handle, returned from RTOS

public:

    /**
     * RTOS Timer method. Parameters of timer are attributes of timer object.
     */
    virtual void m_timer() = 0;

    /**
     * Getter for RTOS id.
     * @return ID of timer or 0 if timer is not created in RTOS
     */
    osTimerId   getTimerHandle() const { return m_handle;}

    /**
     * starts or restarts timer.
     * @return true if success
     */
    bool startTimer() const;

    /**
     * stops RTOS timer
     * @return true if success
     */
    bool stopTimer() const;

    /**
     * Getter for timer period
     * @return period in milliseconds
     */
    uint32_t getPeriod() const { return m_period;}

    /**
     * @brief Changes period of timer.
     *        Change is valid after next (re)start of timer
     * @param [in] period  new period of timer
     */
    void     setPeriod(uint32_t period);
protected:
    /**
     * Constructor
     * @param [in] pcName  timer name, debugging purpose only
     * @param [in] period  timer period (repetitive or single shot) in milliseconds
     * @param [in] type    repetitive or single shot
     */
    TimerBase(const char * const     pcName,
              uint32_t       period,
              os_timer_type  type = osTimerPeriodic);

    virtual ~TimerBase();
private:
    TimerBase() = delete;
    TimerBase(const TimerBase &) = delete;
    TimerBase(const TimerBase &&) = delete;
    TimerBase& operator = (const TimerBase &) = delete;
    TimerBase& operator = (const TimerBase &&) = delete;
};

}  // namespace RTOS
#endif /* TIMERBASE_H_ */

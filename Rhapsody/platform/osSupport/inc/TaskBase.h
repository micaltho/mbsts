/**
 *  \brief     Base Class for RTOS tasks.
 *  \details   Tasks might inherit from this class.
 *             Tasks are registered to RTOS, the m_task method is called as task code.
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      24.09.2015
 *  \pre       First initialize the system, based on a CMSIS RTOS API compliant RTOS
 *  \copyright HS Osnabrueck
 */

/** @file */

#ifndef TASK_H_
#define TASK_H_

#include <cmsis_os.h>
#include <PostOffice.h>
#include <Mutex.h>

namespace RTOS
{


extern const int32_t MAILBOXEVENT;        ///< Signal for receiving task to empty mailbox
extern const int32_t MESSAGEBOXEVENT;     ///< Signal for receiving task to empty messagebox
extern const int32_t TIMEREVENT;          ///< Signal that timer expired
extern const int32_t SIGNALEVENT;         ///< general purpose event



/**
 *  \class Task inc/TaskBase.h
 *  Pure virtual base class for all tasks.
 *  Tasks must inherit this class and implement the m_task method!
 */
class Task
{
private:
	bool        m_isFullInitialized; ///< is task ready to be scheduled?
protected:
    char *      m_Name;             ///<  Name of RTOS task, debugging purpose
    uint16_t    m_StackDepth;       ///<  Stack size of RTOS task
    osPriority  m_Priority;         ///<  cmsis priority
    osThreadId  m_handle;           ///<  RTOS handle/id returned from RTOS
    bool        m_immidiateStart;   ///<  is task registered to RTOS at creation time or by \ref createTask call
    Mutex*      m_mutex;            ///<  "default" Mutex, set by \ref setMutex call, e.g. for cout protection

public:

    /**
     * virtual function which is called from RTOS as task Code
     */
    virtual void m_task() = 0;

    /**
     * get task handle
     * @return RTOS id of task or 0 if task is not created in RTOS
     */
    osThreadId getTaskHandle() const { return m_handle;}

    /**
     * get task name
     * @return Name of Task
     */
    const char * getTaskName() const { return m_Name;}

    /**
     * Creates a RTOS task from this object.
     * The Task is scheduled from now on.
     * If task is already scheduled, nothing is done.
     * @return ID of RTOS task
     */
    osThreadId createTask();
    /**
     * Remove Task from RTOS scheduler.
     * Existing mail or message boxes will be deregisterd from Post office
     * @return 0 if task was removed.
     */
    osThreadId deleteTask();


    /**
     * Sets "Default" Mutex
     * @param [in] mut pointer to Mutex
     * \note A Mutex might not be needed for every task as member
     *       The attribute and mutex methods might be removed
     */
    void  setMutex(Mutex *mut) {m_mutex = mut;};

    /**
     * returns the status of the task, tasks are only schedulable when the task's
     * objekt is fully initialized
     * @return true if task might get scheduled by RTOS, else false
     */
    bool isSchedulable() const { return m_isFullInitialized;}
protected:
    /**
     * Constructor of pure virtual class Task
     * @param [in] pcName       name of task, debugging purpose
     * @param [in] usStackDepth stack of task
     * @param [in] uxPriority   priority of task, see \ref osPriority
     * @param [in] immidiateStart is task scheduled after creation or after \ref createTask call
     */
    Task(const char * const pcName,
         uint16_t    usStackDepth,
         osPriority  uxPriority,
         bool        immidiateStart = true);

    virtual ~Task();


    /**
     * Does final steps of initialization
     * \note
     * Must be last call in constructor of derived class to allow scheduling of new task.
     * The new task might be called immediately if OS is running and priority
     * of new task is higher than priority of running task.
     * Thus, the construction of new task must be finished to be able to call \ref m_task
     *
     * @return  true if success
     */
    bool finalizeInit();

    /**
     * Locks "default" Mutex if set by \ref setMutex
     * @return true if success, false if timeout expired
     */
    bool mutexLock()   const {return  (m_mutex)? m_mutex->lock(): false;   };
    /**
     * Unlocks "default" Mutex if set by \ref setMutex
     */
    void mutexUnlock() const {if (m_mutex)  m_mutex->unlock(); };

    /**
     * creates a message box for task (receiving messages) and registers it in Post office.
     * Messages are void pointers or uint32 values.
     * @param [in] queue_def queue_def  queue definition referenced with \ref osMessageQ.
     * @return messageBox ID created by RTOS
     */
    osMessageQId createMessageBox(const osMessageQDef_t *queue_def) const;

    /**
     * sends message to task.
     * @param [in] receiver  RTOS id of receiving task.
     * @param [in] message   pointer to message or uint32 value
     * @return true if sending was successful
     */
    bool sendMessage(osThreadId receiver, void* message) const;

    /**
     * sends message to task.
     * @param receiver pointer to receiving Task object
     * @param message  pointer to message or uint32 value
     * @return  true if sending was successful, else false
     */
    bool sendMessage(Task* receiver, void* message) const
     { return receiver ? sendMessage(receiver->getTaskHandle(), message) : false;};

    /**
     * sends message to task.
     * @param receiver reference to receiving Task object
     * @param message  pointer to message or uint32 value
     * @return  true if sending was successful, else false
     */
    bool sendMessage(const Task& receiver, void* message) const
     { return sendMessage(receiver.getTaskHandle(), message);};

    /**
     * creates a mail box for task (receiving messages) and registers it in Post office.
     * @param [in] queue_def  queue definition referenced with \ref osMailQ.
     * @return mailBox id created by RTOS or 0 in case of error
     */
    osMailQId createMailBox(const osMailQDef_t* queue_def) const;

    /**
     * sends Mail to task.
     * @param [in] receiver RTOS id of receiving task.
     * @param [in] message  pointer to mail.
     * @param [in] number   identifier for receiver to decode data type.
     * @param [in] type     is message send as pointer or is as pool memory block? \ref PostOffice::mailType_e.
     * @return true if sending was successful, else false
     */
    bool sendMail(osThreadId             receiver,
                  void*                  message,
                  mailNumber_e           number = message1,
                  PostOffice::mailType_e type   = PostOffice::PointerMail ) const;

    /**
     * sends Mail to task.
     * @param [in] receiver pointer to receiving Task object.
     * @param [in] message  pointer to mail.
     * @param [in] number   identifier for receiver to decode data type.
     * @param [in] type     is message send as pointer or is as pool memory block? \ref PostOffice::mailType_e.
     * @return true if sending was successful, else false
     */
    bool sendMail(Task*                  receiver,
    		      void*                  message,
                  mailNumber_e           number,
                  PostOffice::mailType_e type ) const
     { return receiver ? sendMail(receiver->getTaskHandle(), message, number, type) : false;}

    /**
     * sends Mail to task.
     * @param [in] receiver reference to receiving Task object
     * @param [in] message  pointer to mail.
     * @param [in] number   identifier for receiver to decode data type.
     * @param [in] type     is message send as pointer or is as pool memory block? \ref PostOffice::mailType_e.
     * @return true if sending was successful, else false
     */
    bool sendMail(const Task&            receiver,
                  void*                  message,
                  mailNumber_e           number,
                  PostOffice::mailType_e type ) const
     { return sendMail(receiver.getTaskHandle(), message, number, type);}


    /**
     * gives memory for mail back to PostOffice (e.g. RTOS)
     * @param [in] mailEnvelope  pointer to /ref mailStruct_t envelope
     * @param [in] withData      if memory was allocated for mail, the memory can also free'd
     *             Default: the memory is not free'd
     * @return true is success
     */
    bool freeMailEnvelope(PostOffice::mailStruct_t *mailEnvelope, bool withData = false) const
    { return PostOffice::getInstance().freeMail(getTaskHandle(),mailEnvelope, withData); }

private:
    Task() = delete;
    Task(const Task&) = delete;
    Task& operator=(const Task&)  = delete;
    const Task& operator=(Task&&) = delete;
};


}  // namespace RTOS



#endif /* TASK_H_ */

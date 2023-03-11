/*
 * Task.cpp
 *
 *  Created on: 04.08.2015
 *      Author: Wuebbelmann
 */

/** @file */
#include "TaskBase.h"

#ifdef DEBUG
#define DEBUG_RTOS_TASK_BASE
#endif
#ifdef DEBUG_RTOS_TASK_BASE
#include <cstdio>
#endif



#ifdef __cplusplus
extern "C" {
#endif

// this is the task for RTOS.
// This function calls the task handler.
static void taskFnc(void *para)
{
    // para is "this" pointer of task's object!
    RTOS::Task *obj = reinterpret_cast<RTOS::Task *>(para);
#ifdef DEBUG_RTOS_TASK_BASE
    if (!obj->isSchedulable() || !obj->getTaskHandle())
    {
        fprintf(stderr,
                "*** %s Line %d: task %s is scheduled before fully initialized\n",
                __FILE__, __LINE__, (obj->getTaskName() ? obj->getTaskName() : "UNKWON"));
    }

#endif
    obj->m_task();
}

#ifdef __cplusplus
}
#endif



namespace RTOS
{

const int32_t MAILBOXEVENT    = 0x01 << 0;
const int32_t MESSAGEBOXEVENT = 0x01 << 1;
const int32_t TIMEREVENT      = 0x01 << 2;
const int32_t SIGNALEVENT     = 0x01 << 3;


// Const and Dstr
Task::Task(const char * const pcName,
           uint16_t           usStackDepth,
           osPriority         uxPriority,
           bool               immidiateStart
          )
           : m_isFullInitialized(false),
             m_Name((char *)pcName),
             m_StackDepth(usStackDepth),
             m_Priority(uxPriority),
             m_handle(0),
             m_immidiateStart(immidiateStart),
             m_mutex(0)
{
    if(true == m_immidiateStart)
    {
        if (osKernelRunning())
        {
            // set prio to lowest prio, thus task will not be scheduled before
            // initialization of this object is complete.
            // If kernel is not running, there is no problem creating tasks.
            m_Priority = osPriorityIdle;
        }
        else
        {
            // kernel is not running, the constructor is not interrupted by the scheduler
            m_isFullInitialized = true;
        }
        createTask();
        m_Priority = uxPriority;

    }
}


Task::~Task()
{
    // remove task from RTOS scheduler list
    deleteTask();
}

// Methods:

bool Task::finalizeInit()
{
    bool xcode = true;
    m_isFullInitialized = true;
    if(m_handle)
    {
        if(osOK != osThreadSetPriority(m_handle, m_Priority))
        {
          xcode = false;
        }
    }
    return xcode;
}



osThreadId Task::createTask()
{
    osThreadDef_t thread_def;
    if (0 == m_handle)
    {
          // parameter of Task _MUST_ be this-pointer.
          // Else task Code can't see context of object! this-pointer of task object is given parameter!
          // (Note: Normally, this-pointer is implicitly the first parameter of a method call in C++.)
          //        FreeRTOS uses C parameter passing, there is nothing like a this-pointer foreseen.)
        thread_def.instances = 1;
        thread_def.name      = m_Name;
        thread_def.pthread   = reinterpret_cast<os_pthread>(taskFnc);
        thread_def.stacksize = m_StackDepth;
        // if kernel is running, immediate scheduling must be prevented because this object
        // might needs m_handle. Set priority to idle and change it after task is created.
        thread_def.tpriority = (osKernelRunning() ? osPriorityIdle : m_Priority);

        m_handle = osThreadCreate(&thread_def, this);
        if (m_Priority != thread_def.tpriority)
        {
          osThreadSetPriority(m_handle, m_Priority);
        }
    }
#ifdef DEBUG_RTOS_TASK_BASE
    else
    {
        fprintf(stderr,
                "*** %s Line %d: try to (re)create already running task\n",
                __FILE__, __LINE__);
    }
#endif
    return m_handle;
}

osThreadId Task::deleteTask()
{
    // deregister message and mail Box in Post office (if there are any)
    PostOffice::getInstance().registerMessageBox(*this, (osMessageQId)0);
    PostOffice::getInstance().registerMailBox(*this, (osMailQId)0, 0);

    osThreadId handle = m_handle;
    // if the active tasks tries to delete itself, we will not return!
    // set m_handle to 0 to reenable a restart of task.
    m_handle = 0;

    osStatus xcode = osThreadTerminate( handle );

    // this code is only reached if another task deletes us.
    // if error occurred, caller is notified via handle.
    if (osOK != xcode)
    {
      m_handle = handle;
    }
    return m_handle;
}


osMessageQId Task::createMessageBox(const osMessageQDef_t* queue_def) const
{
    // create msg queue
    osMessageQId messageQueue = osMessageCreate(queue_def, NULL);
    // register in Post office
    PostOffice::getInstance().registerMessageBox(*this, messageQueue);
    return messageQueue;
}

bool  Task::sendMessage(osThreadId receiver, void* message) const
{
    return PostOffice::getInstance().sendMessage(receiver, (uint32_t)message);
}



osMailQId Task::createMailBox(const osMailQDef_t* queue_def) const
{
    // create mail queue
    size_t itemSize = queue_def ? queue_def->item_sz : 0;

#ifdef    DEBUG_RTOS_TASK_BASE
    size_t queueSize = queue_def ? queue_def->queue_sz : 0;

    if (queueSize > PostOffice::getMaxSystemMailNumber() )
    {
        fprintf(stderr,
                "%s %d There shouldn't be more items in one box than in whole system\n",
                __FILE__, __LINE__);
    }
#endif
    osMailQId mailQueue = osMailCreate(queue_def, NULL);
    // register in Post office
    PostOffice::getInstance().registerMailBox(*this, mailQueue, itemSize);
    return mailQueue;
}

bool Task::sendMail(osThreadId               receiver,
                    void*                    message,
                    mailNumber_e             number,
                    PostOffice::mailType_e type) const
{
    // FIXME: Never tested!
    return PostOffice::getInstance().sendMail(receiver,
                                              this->getTaskHandle(),
                                              message,
                                              number,
                                              type);
}

}  // namespace RTOS


/*
===============================================================================
 Name        : cmsis_os.c
 Author      : Juergen Wuebbelmann
 Version     : V.0.1 Initial Version 19.09.2015
             : V.1.0 Passes Keil RTOS Validator 23.02.2017
 Copyright   : HS Osnabrueck
 Description : Implementation of the CMSIS RTOS API for FreeRTOS / LPC1769
 Date        : 23.02.2017
===============================================================================
*/




#include <string.h>     // for memset()
#include "cmsis_os.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"


#ifdef DEBUG
#ifndef DEBUG_CMSIS_API
#define DEBUG_CMSIS_API
#endif
#ifndef USESTATEVIEW
#define USESTATEVIEW
#endif
#endif

#ifdef DEBUG_CMSIS_API
#include <stdio.h>
#include <inttypes.h>
#define DEBOUT(x) fprintf(stderr,"*** %s Line %u: %s\n",__FILE__, __LINE__, (x))
#define POOLPATTERN 0x77         ///< allocated memory for pools is filled with this pattern
#else
#define DEBOUT(x)
#endif

#ifndef TRUE
#define TRUE (1==1)
#endif
#ifndef FALSE
#define FALSE (!TRUE)
#endif

#if (!defined(configUSE_APPLICATION_TASK_TAG) || (configUSE_APPLICATION_TASK_TAG == 0))
#error YOU must define configUSE_APPLICATION_TASK_TAG to 1 in FreeRTOSConfig.h
#endif

#ifndef portTICK_RATE_MS    // for pre V8 FreeRTOS or if backward compatibility is not enabled
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

#ifdef DEBUG_CMSIS_API


typedef struct taskInfo_t          ///< \private
{
  TaskHandle_t taskId;             ///< \private
} TaskInfo_t;                      ///< \private

typedef struct taskInfoList_t      ///< \private
{
    TaskInfo_t  info;              ///< \private
    struct taskInfoList_t*  next;  ///< \private
} TaskInfoList_t;                  ///< \private



static uint8_t         isInit = FALSE;
static TaskInfoList_t  taskList[30];
static TaskInfoList_t* freeList = taskList;
static TaskInfoList_t* usedList = 0;

#endif


/*--- define interrupt detection */
#define isInterrupt() ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0)

/*---definition for timer delay*/
const TickType_t DELAYCONSTANT = 100;


// ====[ intern helper functions ]=====
inline
static uint32_t enterCritical()
{
  if (isInterrupt())  return portSET_INTERRUPT_MASK_FROM_ISR();
  else                vPortEnterCritical();
  return 0;
}

inline
static void exitCritical(uint32_t isrMask)
{
  if (isInterrupt())  portCLEAR_INTERRUPT_MASK_FROM_ISR(isrMask);
  else                vPortExitCritical();
}

// ====[ intern debug functions ]=====
#ifdef DEBUG_CMSIS_API
static void initTaskList()
{
  unsigned int i = 0;
  uint32_t     isrMask;
  if (FALSE == isInit)
  {
     isrMask = enterCritical();    // enter critical section,
     for (i = 1; i < sizeof(taskList)/sizeof(TaskInfoList_t); ++i)
     {
        taskList[i-1].next = &(taskList[i]);
     }
     taskList[i-1].next = 0;   // i-1 points to last list element
     freeList = taskList;      // only free elements in list
     usedList = 0;
     isInit = TRUE;
     exitCritical(isrMask);    // leave critical section.
     // Do some configuration checks
     DEBOUT(osKernelSystemId);
     if (configMAX_PRIORITIES <= (osPriorityRealtime-osPriorityIdle))
     {
         DEBOUT("FreeRTOS should be configured to support more priorities.");
     }
  }
}

static osStatus addToTaskList(TaskHandle_t taskId)
{
    osStatus xcode = osOK;
    if (FALSE == isInit)
    {
        initTaskList();
    }

   // first: check if id is already in list
    uint32_t isrMask = enterCritical();
    TaskInfoList_t *listPtr = usedList;
    while ( listPtr && (osOK == xcode) )
    {
        if (listPtr->info.taskId == taskId)
        {
            DEBOUT("try to add taskId more than once");
            xcode = osErrorOS;
        }
        listPtr = listPtr->next;
    }
    if (osOK == xcode)
    {
      // now add in list!
      if(0 == freeList)
      {
         DEBOUT("max Number of task in debug list reached. Add more entries.");
         xcode = osErrorOS;
      }
    }
    if (osOK == xcode)
    {
      // add first free element to used list
      listPtr = freeList;            // remember first free element.
      // remove entry from free list.
      freeList = freeList->next;
      // add entry on top of used list
      listPtr->next = usedList;
      usedList = listPtr;
      // enter info data
      usedList->info.taskId = taskId;
    }
    exitCritical(isrMask);
    return osOK;
}

static osStatus removeFromTaskList(TaskHandle_t taskId)
{
    osStatus        xcode   = osOK;
    TaskInfoList_t *prevPtr = 0;
    uint8_t         found   = FALSE;
    uint32_t        isrMask;
    if (FALSE == isInit)
    {
        initTaskList();
    }
    isrMask = enterCritical();
    TaskInfoList_t *listPtr = usedList;

    while (listPtr && FALSE == found)
    {
       if (listPtr->info.taskId == taskId)
       {
           found = TRUE;
           // remove element from used list.
           if (prevPtr)
           {
              prevPtr->next = listPtr->next;
           }
           else   // found Id in root element of list, set new root element
           {
               usedList = listPtr->next;
           }
           // add entry on top of free list
           listPtr->next = freeList;
           freeList = listPtr;
       }
       prevPtr = listPtr;
       listPtr = listPtr->next;
    }
    exitCritical(isrMask);
    if (FALSE == found)
    {
        DEBOUT("couldn't find entry to delete");
        xcode = osErrorOS;
    }
    return xcode;
}

#endif

#ifdef DEBUG_CMSIS_API
#define ADDTOLIST(x) addToTaskList((x))
#define REMOVEFROMLIST(x) removeFromTaskList((x))
#else
#define ADDTOLIST(x)      (osOK)
#define REMOVEFROMLIST(x) (osOK)
#endif


// =====[ Helper functions ]=============
#if (defined (DEBUG) && defined (configOS_ASSERT)  &&  (configOS_ASSERT != 0))
void vAssertCalled(const char * const pcFileName, unsigned long ulLine)
{
   volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

#if (defined (DEBUG_CMSIS_API))
    fprintf(stderr,"*** %s Line %" PRIu32 ": FreeRTOS assertion.\n",pcFileName, ulLine);
#endif
    uint32_t isrMask = enterCritical();
    {
        /* You can step out of this function to debug the assertion by using
        the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
        value. */
        while( ulSetToNonZeroInDebuggerToContinue == 0 )
        {
        }
    }
    exitCritical(isrMask);
}
#endif


static TickType_t milliSecToTicks(uint32_t millisec)
{
    TickType_t ticksToWait;
    if (osWaitForever  == millisec)   // wait forever, no timeout.
    {
        // only if INCLUDE_vTaskSuspend  is set to 1
        ticksToWait = portMAX_DELAY;
#if (!defined(INCLUDE_vTaskSuspend) || (INCLUDE_vTaskSuspend == 0))
        DEBOUT("Can't suspend Task");
#endif
    }
    else
    {
        ticksToWait =  millisec / portTICK_RATE_MS;
    }
    return ticksToWait;
}


/* generic task code for all Tasks!!!! */
static void taskFunc(void *param)
{
    //TaskFunction_t
    TaskHookFunction_t taskCode = xTaskGetApplicationTaskTag( NULL );
    osThreadId myId = 0;

    if (taskCode)
    {
      taskCode(param);
    }
    else
    {
         DEBOUT("Can't start Task Code");
    }

    myId = osThreadGetId();
    osThreadTerminate(myId);
}


// =====[ Kernel Control Functions ]=====
static uint32_t isKernelStarted = 0;

/// Initialize the RTOS Kernel for creating objects.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osKernelInitialize shall be consistent in every CMSIS-RTOS.
osStatus osKernelInitialize (void)
{
    //prevent compile error
    return osOK;
}

/// Start the RTOS Kernel.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osKernelStart shall be consistent in every CMSIS-RTOS.
osStatus osKernelStart (void)
{
    isKernelStarted = 1;
    vTaskStartScheduler();
    return osErrorOS;            //Program is not supposed to reach this point!
}

/// Check if the RTOS kernel is already started.
/// \note MUST REMAIN UNCHANGED: \b osKernelRunning shall be consistent in every CMSIS-RTOS.
/// \return 0 RTOS is not started, 1 RTOS is started.
int32_t osKernelRunning(void)
{
    //prevent compile error
    return isKernelStarted;
}

/// Get the RTOS kernel system timer counter
/// \note MUST REMAIN UNCHANGED: \b osKernelSysTick shall be consistent in every CMSIS-RTOS.
/// \return RTOS kernel system timer as 32-bit value
uint32_t osKernelSysTick (void)
{
    TickType_t ticks = 0;
    if (!isInterrupt())
    {
       ticks = xTaskGetTickCount( );
    }
    else
    {
       ticks = xTaskGetTickCountFromISR( );
    }
    return (uint32_t)ticks;
}

// ===============[ Thread Management Functions ]===============

/// Create a thread and add it to Active Threads and set it to state READY.
/// \param[in]     thread_def    thread definition referenced with \ref osThread.
/// \param[in]     argument      pointer that is passed to the thread function as start argument.
/// \return thread ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osThreadCreate shall be consistent in every CMSIS-RTOS.
osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument)
{
    osThreadId id = NULL;

    if(!thread_def)
    {
        //error message here
        DEBOUT("Thread creation failed because of invalid definition!");
        return 0;
    }
    if(isInterrupt())    // interrupt mode
    {
        // CMSIS forbids thread creation from Interrupt!
        return 0;
    }

    //--Parse to task-parameters
    TaskFunction_t taskCode = (TaskFunction_t)(thread_def->pthread);      // in C++ use reinterpret_cast to parse void(*)(const void*) to void(*)(void*)
    char * const taskName = thread_def->name;                              //dummy name since it is for debugging purposes anyway
    uint16_t stackDepth = ((thread_def->stacksize) / sizeof(StackType_t)); //conversion from bytes into specified number of the variables the stack can hold
    void *parameters = argument;                                           //parameter for thread function
    UBaseType_t priority = tskIDLE_PRIORITY;                               //priority
    TaskHandle_t createdTask = NULL;                                       //taskHandle that will be written by a successful xTaskCreate

    // adapt CMSIS to FreeRtos priority levels
    // osPriorityIdle (-3) must be mapped to tskIDLE_PRIORITY (0)
    priority = thread_def->tpriority + (tskIDLE_PRIORITY - osPriorityIdle);

    // check stackDepth.
    // according to CMSIS-RTOS API description, 0 is default stack size
    if (0 == stackDepth)
    {
        stackDepth = configMINIMAL_STACK_SIZE;  // defined in FreeRTOSConfig.h
    }

    // check valid priority.
    if(thread_def->tpriority > osPriorityRealtime)
    {
        //error message here
        DEBOUT("Thread creation failed because of invalid priority!");
        return 0;
    }

    //  --Create Task
#if (defined( DEBUG_CMSIS_API) || (defined(configUSE_APPLICATION_TASK_TAG) && (configUSE_APPLICATION_TASK_TAG == 1)))
    uint32_t isrMask = enterCritical();   // protect creation AND add to internal list....
#endif
    if (pdPASS == xTaskCreate(taskFunc, taskName, stackDepth, parameters, priority, &createdTask))
    {
        //success
        id = (osThreadId)createdTask;                                     //pass created taskHandle to id
        vTaskSetApplicationTaskTag(createdTask,(TaskHookFunction_t)taskCode);   // set Tag to task Code....
        (void) ADDTOLIST(createdTask);
    }
    else
    {
        //error message here
        DEBOUT("Thread creation failed!");
    }
#if (defined( DEBUG_CMSIS_API) || (defined(configUSE_APPLICATION_TASK_TAG) && (configUSE_APPLICATION_TASK_TAG == 1)))
    exitCritical(isrMask);
#endif

    return id;
}

/// Return the thread ID of the current running thread.
/// \return thread ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osThreadGetId shall be consistent in every CMSIS-RTOS.
osThreadId osThreadGetId (void)
{
    osThreadId id = NULL;
    TaskHandle_t handle = NULL;

    if(isInterrupt())    // interrupt mode
    {
        // CMSIS forbids call from Interrupt!
        return 0;
    }

#if (defined( DEBUG_CMSIS_API))
    if(!osKernelRunning())
    {
        DEBOUT( "Can't get Thread ID while OS is not Running!");
    }
    else
#endif
    {
       /*--Get current handle*/
       handle = xTaskGetCurrentTaskHandle();       //write the taskHandle of the current Task
    }
    if(handle != NULL)
    {
        //success
        id = handle;                            //pass current handle to the current threadId
    }
    else
    {
        //error message here
        DEBOUT( "Was not able to get the ID of the current task!");
    }
    return id;
}

/// Terminate execution of a thread and remove it from Active Threads.
/// \param[in]     thread_id   thread ID obtained by \ref osThreadCreate or \ref osThreadGetId.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osThreadTerminate shall be consistent in every CMSIS-RTOS.
osStatus osThreadTerminate (osThreadId thread_id)
{
    osStatus state = osOK;
#if ( INCLUDE_vTaskDelete == 1 )
    TaskHandle_t task = thread_id;                                  //pass the threadID of the task/thread to be deleted

    if(isInterrupt())    // interrupt mode
    {
        // CMSIS forbids call from Interrupt!
        state = osErrorISR;
        return state;
    }

    /*--Delete task*/
    if (0 != task)
    {
#ifdef DEBUG_CMSIS_API
        uint32_t isrMask = enterCritical();   // protect creation AND remove from internal list....
#endif
        vTaskDelete(task);                                          //delete the task
        state = REMOVEFROMLIST(task);
#ifdef DEBUG_CMSIS_API
        exitCritical(isrMask);
#endif

    }
    else
    {
        DEBOUT("try to terminate NULL Task");
        state = osErrorParameter;
    }
#else
    state = osErrorOS;
    //error message here
    DEBOUT("INCLUDE_vTaskDelete must be enabled to terminate Task");
#endif

   return state;
}

/// Pass control to next thread that is in state \b READY.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osThreadYield shall be consistent in every CMSIS-RTOS.
osStatus osThreadYield (void)
{
    osStatus state;
    if(isInterrupt())    // interrupt mode
    {
        // CMSIS forbids call from Interrupt!
        state = osErrorISR;
        return state;
    }

    taskYIELD();                                //force context-switch
    //no way to control success...?
    state = osOK;
    return state;
}



/// Change priority of an active thread.
/// \param[in]     thread_id     thread ID obtained by \ref osThreadCreate or \ref osThreadGetId.
/// \param[in]     priority      new priority value for the thread function.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osThreadSetPriority shall be consistent in every CMSIS-RTOS.
osStatus osThreadSetPriority (osThreadId thread_id, osPriority priority)
{
    osStatus state = osOK;
    TaskHandle_t task = thread_id;                                  //pass the threadID of the task/thread whose priority has to be set
    UBaseType_t taskPriority = tskIDLE_PRIORITY;                    //pass priority

    if(isInterrupt())    // interrupt mode
    {
        // CMSIS forbids call from Interrupt!
        state =  osErrorISR;
        return state;
    }

#if (1 == INCLUDE_vTaskPrioritySet)     // check if we are allowed to do this...
    if (priority < osPriorityIdle || priority > osPriorityRealtime)
    {
        state = osErrorValue;
        return state;
    }

    // adapt CMSIS to FreeRtos priority levels
    // osPriorityIdle (-3) must be mapped to tskIDLE_PRIORITY (0)
    taskPriority = priority + (tskIDLE_PRIORITY - osPriorityIdle);

    if(!thread_id)
    {
        //error message here
        DEBOUT("Priority of the NULL thread can not be changed!");
        state = osErrorParameter;
        return state;
    }
    /*--Set the priority*/
    vTaskPrioritySet(task, taskPriority);
    if (osThreadGetPriority(thread_id) == priority)                 //check if the priority is the one that was supposed to be set
    {
        //success
        state = osOK;
    }
    else
    {
        //error message here
        DEBOUT("Priority of the thread could not be changed!");
        state = osErrorValue;
    }
#else
    state = osErrorOS;
    //error message here
    DEBOUT("INCLUDE_vTaskPrioritySet must be enabled to terminate Task");
#endif

    return state;
}

/// Get current priority of an active thread.
/// \param[in]     thread_id     thread ID obtained by \ref osThreadCreate or \ref osThreadGetId.
/// \return current priority value of the thread function.
/// \note MUST REMAIN UNCHANGED: \b osThreadGetPriority shall be consistent in every CMSIS-RTOS.
osPriority osThreadGetPriority (osThreadId thread_id)
{
    TaskHandle_t task = thread_id;                     //pass the threadID of the task/thread whose priority has to be get
    osPriority priority = osPriorityError;
    UBaseType_t prio = priority;
    if(isInterrupt())    // interrupt mode
    {
        // CMSIS forbids call from Interrupt!
        return priority;
    }

    if(!thread_id)
    {
        //error message here
        DEBOUT("Priority of the NULL thread can not be changed!");
        return priority;
    }

#if ( INCLUDE_uxTaskPriorityGet == 1 )
    /*--Get the priority*/
    prio = uxTaskPriorityGet(task);

    if(prio <= (osPriorityRealtime - osPriorityIdle) + tskIDLE_PRIORITY)
    {
        priority = prio + osPriorityIdle  - tskIDLE_PRIORITY;
    }
    else
    {
        //error message here
        DEBOUT("Priority could not be achieved!");
    }
#else
    //error message here
    DEBOUT("INCLUDE_uxTaskPriorityGet must be enabled to terminate Task");
#endif
    return priority;
}


// =====[ Generic Wait Functions ]=====

/// Wait for Timeout (Time Delay).
/// \param[in]     millisec      time delay value
/// \return status code that indicates the execution status of the function.
osStatus osDelay (uint32_t millisec)
{
    osStatus status = osEventTimeout;
    if(!isInterrupt())
    {
        TickType_t ticks = milliSecToTicks(millisec);
        vTaskDelay(ticks);
    }
    else
    {
        status = osErrorISR;
        DEBOUT("osDelay cannot be called from ISR");
    }
    return status;
}

/// Wait for Signal, Message, Mail, or Timeout.
/// \param[in] millisec          timeout value or 0 in case of no time-out
/// \return event that contains signal, message, or mail information or error code.
/// \note MUST REMAIN UNCHANGED: \b osWait shall be consistent in every CMSIS-RTOS.
#if (defined (osFeature_Wait)  &&  (osFeature_Wait != 0))     // Generic Wait available
osEvent osWait (uint32_t millisec)
{
    //prevent compile error
    osEvent result;
    return result;
}
#endif
// ===============[ Timer Management Functions ]===============

// ===============[ Timer internal helper Functions ] =========
typedef struct timerArg_t                ///< \private
{
   void                     *arguments;  ///< \private
   TimerCallbackFunction_t  func;        ///< \private
}  _TimerArg_t;

static void genericTimerCallback(TimerHandle_t xTimer)
{
   _TimerArg_t * timerId = 0;
   if(!xTimer)
   {
       DEBOUT("invalid Parameter in Timer Callback");
       return;
   }
   timerId = (_TimerArg_t *)pvTimerGetTimerID( xTimer );
   if (timerId)
   {
       timerId->func(timerId->arguments);
   }
   else
   {
       DEBOUT("Callback couldn't retrieve Timer ID");
   }
}


/// Create a timer.
/// \param[in]     timer_def     timer object referenced with \ref osTimer.
/// \param[in]     type          osTimerOnce for one-shot or osTimerPeriodic for periodic behavior.
/// \param[in]     argument      argument to the timer call back function.
/// \return timer ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osTimerCreate shall be consistent in every CMSIS-RTOS.
osTimerId osTimerCreate (const osTimerDef_t *timer_def,
                         os_timer_type type,
                         void *argument)
{
    TimerHandle_t createdTimer = NULL;
    osTimerId id = NULL;
    _TimerArg_t*  timerArgs = 0;

    if(isInterrupt())
    {
        // CMISIS forbids call from Interrupt
        return 0;
    }

    if (!timer_def)
    {
        DEBOUT("Illegal Timer Definition: NULL");
        return 0;
    }
    /*--Parse to timer-parameters*/
    char * const timerName = timer_def->name;             // name, only for debug purposes
    TickType_t  timerPeriodicInTicks = portMAX_DELAY;     //initial TickValue is max, correct period will be set in osTimerStart
    UBaseType_t uxAutoReload  = pdFALSE;                  //choosing correct timerType
    TimerCallbackFunction_t callback = &genericTimerCallback;

    switch (type)
    {
    case osTimerOnce:
        uxAutoReload   = pdFALSE;
        break;
    case osTimerPeriodic:
        uxAutoReload   = pdTRUE;
        break;
    default:
        DEBOUT("Illegal Timer Mode assigned");
        break;
    }

    timerArgs = ( _TimerArg_t * ) pvPortMalloc( sizeof( _TimerArg_t ) );
    if (!timerArgs)
    {
        DEBOUT("Couldn't retrieve Memory for timer arguments");
        return id;
    }
    timerArgs->func      = (TimerCallbackFunction_t)timer_def->ptimer;
    timerArgs->arguments = argument;

    /*--Create timer*/
    createdTimer = xTimerCreate(timerName,
                                timerPeriodicInTicks,
                                uxAutoReload  ,
                                (void * const)timerArgs,
                                callback);        //create timer in dormant state
    if (createdTimer != NULL)
    {
        //success
        id = createdTimer;
    }
    else
    {
        //error message here
        DEBOUT("Timer could not be created!");
    }
    return id;
}


/// Start or restart a timer.
/// \param[in]     timer_id      timer ID obtained by \ref osTimerCreate.
/// \param[in]     millisec      time delay value of the timer.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osTimerStart shall be consistent in every CMSIS-RTOS.
osStatus osTimerStart (osTimerId timer_id, uint32_t millisec)   //configUSE_TIMERS was changed to 1 in FreeRTOS for this!
{
    osStatus state;
    TickType_t delayConstant = DELAYCONSTANT;     //set the delay for later timer functions
    TimerHandle_t xTimer = (TimerHandle_t) timer_id;


    if (!timer_id)
    {
        DEBOUT("NULL Timer can not be started!");
        state = osErrorParameter;
        return state;
    }
    /*--Change the timer period*/
    if(!isInterrupt())    // Thread Mode
    {
      if (pdPASS == xTimerChangePeriod(xTimer, milliSecToTicks(millisec), delayConstant))
      {
          //success
          /*--Start timer*/
          if (pdPASS == xTimerReset (timer_id, delayConstant))
          {
              //success
              state = osOK;
          }
          else
          {
              //error message
              DEBOUT("Timer could not be started/reseted in time!");
              state = osErrorTimeoutResource;
          }
      }
      else
      {
          //error message
          DEBOUT("Period of the timer could not be set in time!");
          state = osErrorTimeoutResource;
      }
    }
    else                  // Exception Mode
    {
#if 0
        BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
        if (pdPASS == xTimerResetFromISR(timer_id, &xHigherPriorityTaskWoken))
        {
            // context switch if required....
            portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }
        else
        {
            state = osErrorResource;
            // DEBOUT in interrupt context?
            DEBOUT("Could not start Timer in ISR");
        }
#else
        // CMSIS forbids call from ISR
        state = osErrorISR;
#endif
    }
    return state;
}

/// Stop the timer.
/// \param[in]     timer_id      timer ID obtained by \ref osTimerCreate.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osTimerStop shall be consistent in every CMSIS-RTOS.
osStatus osTimerStop (osTimerId timer_id)                   //configUSE_TIMERS was changed to 1 in FreeRTOS for this!
{
    osStatus state;
    TimerHandle_t xTimer = (TimerHandle_t) timer_id;
    TickType_t delayConstant = DELAYCONSTANT;               //set the delay for later timer functions

    if (isInterrupt())
    {
        // CMSIS forbids call from ISR
        state = osErrorISR;
        return state;
    }
    if (!timer_id)
    {
        DEBOUT("NULL Timer can not be stopped!");
        state = osErrorParameter;
        return state;
    }
    if(xTimerIsTimerActive(xTimer) == pdFALSE)
    {
        DEBOUT("Dormant Timer can not be stopped!");
        state = osErrorResource;
        return state;
    }

    /*--Stop timer*/
    if(!isInterrupt())    // Thread Mode
    {
       if (pdPASS == xTimerStop(xTimer, delayConstant))
       {
          state = osOK;
          // If our priotity is higher than timer task priority, timer won't be stopped immediately.
          // Wait for 2 ms, so timer task  handles command queue.
          // Warning: this might not work if there are other high priority task waiting!
          osDelay(2);
       }
       else
       {
           DEBOUT("Timer could not be stopped!");
           state = osErrorTimeoutResource;
       }
    }
    else                  // Exception Mode
    {
#if 0
        BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
        if (pdPASS == xTimerStopFromISR(timer_id, &xHigherPriorityTaskWoken))
        {
            // context switch if required....
               portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
        }
        else
        {
             state = osErrorResource;
             // DEBOUT in interrupt context?
             DEBOUT("Could not stop Timer in ISR");
        }
#else
        // CMSIS forbids call from ISR
        state = osErrorISR;
#endif
    }
    return state;
}

/// Delete a timer that was created by \ref osTimerCreate.
/// \param[in]     timer_id      timer ID obtained by \ref osTimerCreate.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osTimerDelete shall be consistent in every CMSIS-RTOS.
osStatus osTimerDelete (osTimerId timer_id)              //configUSE_TIMERS was changed to 1 in FreeRTOS for this!
{
    osStatus state;
    _TimerArg_t   *timerData = 0;
    TimerHandle_t xTimer = (TimerHandle_t) timer_id;

    TickType_t delayConstant = DELAYCONSTANT;            //set the delay for later timer functions

    if(isInterrupt())
    {
        // CMISIS forbids call from Interrupt
        state = osErrorISR;
        return state;
    }

    if (!timer_id)
    {
        DEBOUT("NULL Timer can not be deleted!");
        state = osErrorParameter;
        return state;
    }

    /*Delete timer*/
    // data was assigned with pvPortMalloc in osTimerCreate.. free the memory.
    timerData = (_TimerArg_t *)pvTimerGetTimerID( xTimer );
    vPortFree(timerData);

    if (pdPASS == xTimerDelete(xTimer, delayConstant))
    {
        state = osOK;
    }
    else
    {
        DEBOUT("Timer could not be deleted!");
        state = osErrorTimeoutResource;
    }
    return state;
}

// ===============[ Signal Management Functions ]================

/// Set the specified Signal Flags of an active thread.
/// \param[in]     thread_id     thread ID obtained by \ref osThreadCreate or \ref osThreadGetId.
/// \param[in]     signals       specifies the signal flags of the thread that should be set.
/// \return previous signal flags of the specified thread or 0x80000000 in case of incorrect parameters.
/// \note MUST REMAIN UNCHANGED: \b osSignalSet shall be consistent in every CMSIS-RTOS.
int32_t osSignalSet (osThreadId thread_id, int32_t signals)      //configUSE_TASK_NOTIFICATIONS is already 1 in FreeRTOS!
{
    TaskHandle_t taskToNotify = (TaskHandle_t)thread_id;  //pass the Thread ID to the taskHandle
    uint32_t bitsToSet = signals;                         //pass the bits that have to be set
    uint32_t prev = 0;                                     //set variable prev, that gets overwritten by the previous bits

    if (0 == thread_id)
    {
         // try to notify invalid thread id.
         // FreeRTOS will crash!
        DEBOUT("attemp to notify invalid thread id!");
        return 0x80000000;
    }
#ifdef DEBUG_CMSIS_API
    if (!isInterrupt()) //  eTaskGetState only available in Thread Mode
    {
        eTaskState state = eTaskGetState(taskToNotify);
        if (!(eBlocked == state || eReady == state || eRunning == state))
        {
            if (eDeleted == state)
            {
                DEBOUT("Attempt to notify a deleted task!");
            }
            else
            {
                DEBOUT("Attempt to notify a task with undefined state!");
            }
            return 0x80000000;
        }
    }
#endif
    if (signals < 0)
    {
        // MSB cannot be set by user
        DEBOUT("Attempt to notify negative value!");
        return 0x80000000;
    }
    if (!isInterrupt()) // Thread Mode
    {
      /*--Set notify bits*/
#ifndef configTASK_NOTIFICATION_ARRAY_ENTRIES    // pre V10.4.0
      if(pdPASS != xTaskGenericNotify(taskToNotify, bitsToSet, eSetBits, &prev))
#else
      if(pdPASS != xTaskGenericNotify(taskToNotify, tskDEFAULT_INDEX_TO_NOTIFY, bitsToSet, eSetBits, &prev))
#endif
      {
          //error message here
          DEBOUT("Signal could not be set!");
          prev = 0x80000000;               // required by CMSIS RTOS API
      }
    }
    else                                         // Exception mode
    {      // note: in exception Mode, previous signal flags can not be returned
          BaseType_t xHigherPriorityTaskWoken = pdFALSE;
          xTaskNotifyFromISR( taskToNotify,
                              bitsToSet,
                              eSetBits,
                              &xHigherPriorityTaskWoken);
          // context switch if required....
          portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
    return (int32_t)prev;
}

/// Clear the specified Signal Flags of an active thread.
/// \param[in]     thread_id     thread ID obtained by \ref osThreadCreate or \ref osThreadGetId.
/// \param[in]     signals       specifies the signal flags of the thread that shall be cleared.
/// \return previous signal flags of the specified thread or 0x80000000 in case of incorrect parameters or call from ISR.
/// \note MUST REMAIN UNCHANGED: \b osSignalClear shall be consistent in every CMSIS-RTOS.
int32_t osSignalClear (osThreadId thread_id, int32_t signals)            //configUSE_TASK_NOTIFICATIONS is already 1 in FreeRTOS!
{
    TaskHandle_t taskToNotify = (TaskHandle_t)thread_id;                 //pass the Thread ID to the taskHandle
    int32_t      previous = 0x80000000;
    uint32_t     prev = previous;                                        //set variable prev, that gets overwritten by the previous bits

    if(isInterrupt())
    {
        // CMSIS forbids call from ISR
        return 0x80000000;
    }
    if (0 == thread_id)
    {
         // try to notify invalid thread id.
         // FreeRTOS will crash!
        DEBOUT("attemp to clear flag of invalid thread id!");
        return 0x80000000;
    }
    if (signals < 0)
    {
        // MSB cannot be set by user
        DEBOUT("Attempt to clear negative value!");
        return 0x80000000;
    }

    uint32_t isrMask = enterCritical();   // make access to prev atomar
    /*--Get previous notify bits*/
#ifndef configTASK_NOTIFICATION_ARRAY_ENTRIES    // pre V10.4.0
      if(pdPASS != xTaskGenericNotify(taskToNotify, 0, eNoAction, &prev))
#else
      if(pdPASS != xTaskGenericNotify(taskToNotify, tskDEFAULT_INDEX_TO_NOTIFY, 0, eNoAction, &prev))
#endif
    {
        //success
        previous = prev;
    }
    else
    {
        //Error message here
        DEBOUT("Signal could not be read!");
    }
    uint32_t bitsToSet = previous & (~signals);        //create the expected mask after the clear

    /*--Clear notify bits*/
    //use eSetValueWithOverwrite to set the correct bitmask
    if(pdPASS != xTaskNotify(taskToNotify, bitsToSet, eSetValueWithOverwrite))
    {
        //Error message here
        DEBOUT("Signal could not be cleared!");
        previous = 0x80000000;
    }

    if(0 == bitsToSet)
    {
       xTaskNotifyStateClear(taskToNotify);
    }
    exitCritical(isrMask);
    return previous;
}

/// Wait for one or more Signal Flags to become signaled for the current \b RUNNING thread.
/// \param[in]     signals       wait until all specified signal flags set or 0 for any single signal flag.
/// \param[in]     millisec      timeout value or 0 in case of no time-out.
/// \return event flag information or error code.
/// \note MUST REMAIN UNCHANGED: \b osSignalWait shall be consistent in every CMSIS-RTOS.
osEvent osSignalWait (int32_t signals, uint32_t millisec)       //configUSE_TASK_NOTIFICATIONS is already 1 in FreeRTOS!
{
    uint32_t notificationValue = 0;                          //pass the bits that have to be wait for
    TickType_t ticksToWait = milliSecToTicks(millisec);      // get correct ticks, check for 0!
    osEvent result;

    if(isInterrupt())   // can't be called from ISR
    {
        result.status = osErrorISR;
        return result;
    }
    if (signals < 0)
    {
        // MSB cannot be set by user
        DEBOUT("attemp to clear negative value!");
        result.status = osErrorValue;
        return result;
    }
    /*--Wait for expected bits*/
    if(pdPASS == xTaskNotifyWait(0, signals, &notificationValue, ticksToWait))
    {
        result.status = osEventSignal;
        result.value.signals = notificationValue;
    }
    else
    {
        //Error message here
        if (0 != millisec)
        {
          DEBOUT("Timeout occurred!");
          result.value.signals = notificationValue;
          result.status = osEventTimeout;
        }
        else
        {
            result.status = osOK;
        }
    }
    return result;
}


// =====[ Mutex Management Functions ]=====

/// Create and Initialize a Mutex object.
/// \param[in]     mutex_def     mutex definition referenced with \ref osMutex.
/// \return mutex ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osMutexCreate shall be consistent in every CMSIS-RTOS.
osMutexId osMutexCreate (const osMutexDef_t *mutex_def)
{
    osMutexId mMutex = 0;
#if ( configUSE_MUTEXES == 1)
    SemaphoreHandle_t xSemaphore;
    if(isInterrupt())
    {
        // CMSIS forbids call from ISR
        return 0;
    }
    if(!mutex_def)
    {
        return 0;
    }
#if ((defined configUSE_RECURSIVE_MUTEXES ) && (configUSE_RECURSIVE_MUTEXES == 1))
    xSemaphore = xSemaphoreCreateRecursiveMutex ();
#else
    xSemaphore = xSemaphoreCreateMutex ();
#endif
    mMutex = (osMutexId)xSemaphore;
    if(0 == xSemaphore)
    {
        DEBOUT("Couldn't create Mutex");
    }
#ifdef USESTATEVIEW
    else
    {
        if (mutex_def->name)
        {
            vQueueAddToRegistry( xSemaphore, mutex_def->name);
        }
        else
        {
            vQueueAddToRegistry( xSemaphore, "Mutex");
        }
    }
#endif


#else
    DEBOUT("Mutex not enabled in RTOS");
#endif
    return mMutex;
}

/// Wait until a Mutex becomes available.
/// \param[in]     mutex_id      mutex ID obtained by \ref osMutexCreate.
/// \param[in]     millisec      timeout value or 0 in case of no time-out.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osMutexWait shall be consistent in every CMSIS-RTOS.
osStatus osMutexWait (osMutexId mutex_id, uint32_t millisec)
{
    SemaphoreHandle_t xSemaphore = (SemaphoreHandle_t)mutex_id;
    TickType_t ticksToWait = milliSecToTicks(millisec);      // get correct ticks, check for 0!
    osStatus   result = osOK;

    if(isInterrupt())
    {
        // CMSIS forbids call from ISR
        return osErrorISR;
    }

    if (0 == mutex_id)
    {
        return osErrorParameter;
    }
    /*--Wait for expected bits*/
    if(!isInterrupt())  // Thread mode
    {
#if ((defined INCLUDE_xSemaphoreGetMutexHolder) && (INCLUDE_xSemaphoreGetMutexHolder == 1))
#if !((defined configUSE_RECURSIVE_MUTEXES ) && (configUSE_RECURSIVE_MUTEXES == 1))
       if (xSemaphoreGetMutexHolder(xSemaphore) == xTaskGetCurrentTaskHandle())
       {
          return osOK;                                  // a mutex can be nested
       }
#endif
#endif
#if ((defined configUSE_RECURSIVE_MUTEXES ) && (configUSE_RECURSIVE_MUTEXES == 1))
       if (pdTRUE != xSemaphoreTakeRecursive(xSemaphore, ticksToWait))
#else
       if (pdTRUE != xSemaphoreTake(xSemaphore, ticksToWait))
#endif
       {
           result = osErrorTimeoutResource;
           // Note: in case of timeout, the DEBOUT message causes another 6 msec delay.
           DEBOUT("Wait for Mutex/Sema caused Timeout");
       }
    }
    else   // Exception mode
    {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       if (pdTRUE == xSemaphoreTakeFromISR( xSemaphore, &xHigherPriorityTaskWoken))
       {
          // context switch if required....
          portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
       }
       else
       {
           result = osErrorResource;
           DEBOUT("Mutex/Sema not available in ISR");
       }
    }
    return result;
}


/// Release a Mutex that was obtained by \ref osMutexWait.
/// \param[in]     mutex_id      mutex ID obtained by \ref osMutexCreate.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osMutexRelease shall be consistent in every CMSIS-RTOS.
osStatus osMutexRelease (osMutexId mutex_id)
{
    SemaphoreHandle_t xSemaphore = (SemaphoreHandle_t)mutex_id;

    if(isInterrupt())
    {
        // CMSIS forbids call from ISR
        return osErrorISR;
    }
    // Test if we hold mutex:
    if (!mutex_id)
    {
        return osErrorParameter;
    }
    if (xSemaphoreGetMutexHolder(xSemaphore) != xTaskGetCurrentTaskHandle())
    {
        return osErrorResource;
    }
#if ((defined configUSE_RECURSIVE_MUTEXES ) && (configUSE_RECURSIVE_MUTEXES == 1))
    if (pdTRUE == xSemaphoreGiveRecursive( xSemaphore ))
    {
       return osOK;
    }
    return osErrorResource;
#else
    return osSemaphoreRelease((osSemaphoreId) mutex_id);
#endif
}

/// Delete a Mutex that was created by \ref osMutexCreate.
/// \param[in]     mutex_id      mutex ID obtained by \ref osMutexCreate.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osMutexDelete shall be consistent in every CMSIS-RTOS.
osStatus osMutexDelete (osMutexId mutex_id)
{

    if(isInterrupt())
    {
        // CMISIS forbids call from ISR
        return osErrorISR;
    }
    return osSemaphoreDelete((osSemaphoreId) mutex_id);
}

// =====[ Semaphore Management Functions ]=====
#if (defined (osFeature_Semaphore)  &&  (osFeature_Semaphore != 0))     // Semaphore available
#if (defined(configUSE_COUNTING_SEMAPHORES) && (configUSE_COUNTING_SEMAPHORES == 1 ))
/// Create and Initialize a Semaphore object used for managing resources.
/// \param[in]     semaphore_def semaphore definition referenced with \ref osSemaphore.
/// \param[in]     count         number of available resources.
/// \return semaphore ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osSemaphoreCreate shall be consistent in every CMSIS-RTOS.
osSemaphoreId osSemaphoreCreate (const osSemaphoreDef_t *semaphore_def, int32_t count)
{
    osSemaphoreId     mSemaphore = 0;
    SemaphoreHandle_t xSemaphore;

    if(isInterrupt())
    {
        // CMISIS forbids call from ISR
        return mSemaphore;
    }
    if (osFeature_Semaphore < count)  // defines the maximum index count
    {
      DEBOUT("parameter count exceeds defined maximum (increase osFeature_Semaphore)");
      return mSemaphore;
    }
    if(!semaphore_def)
    {
      DEBOUT("Semaphore Definition might not be NULL pointer");
      return mSemaphore;
    }
    xSemaphore = xSemaphoreCreateCounting(osFeature_Semaphore, count);
    mSemaphore = (osSemaphoreId)xSemaphore;
    if(0 == xSemaphore)
    {
      DEBOUT("Couldn't create Semaphore");
    }
#ifdef USESTATEVIEW
    else
    {
        if (semaphore_def->name)
        {
            vQueueAddToRegistry( xSemaphore, semaphore_def->name);
        }
        else
        {
            vQueueAddToRegistry( xSemaphore, "Semaphore");
        }
    }
#endif
    return mSemaphore;
}


/// Wait until a Semaphore token becomes available.
/// \param[in]     semaphore_id  semaphore object referenced with \ref osSemaphoreCreate.
/// \param[in]     millisec      timeout value or 0 in case of no time-out.
/// \return number of available tokens, or -1 in case of incorrect parameters.
/// \note MUST REMAIN UNCHANGED: \b osSemaphoreWait shall be consistent in every CMSIS-RTOS.
int32_t osSemaphoreWait (osSemaphoreId semaphore_id, uint32_t millisec)
{
    // this function is NOT thread save, so numAvailToken might returns wrong number
    //  because a thread change occurred between FreeRTOS function calls.
    int32_t  numAvailToken = -1;

    if(isInterrupt())
    {
       // CMSIS forbids call from ISR
       return numAvailToken;
    }
    if(!semaphore_id)
    {
       DEBOUT("osSemaphoreWait: NULL not allowd");
       return numAvailToken;
    }
    osStatus xcode = osMutexWait((osMutexId)semaphore_id, millisec);
    if (osOK == xcode)
    {
       if(!isInterrupt())  // Thread mode
       {
           numAvailToken = uxQueueMessagesWaiting((QueueHandle_t )semaphore_id);
       }
       else   // Exception mode
       {
         numAvailToken = uxQueueMessagesWaitingFromISR((QueueHandle_t )semaphore_id);
       }
    }
    else
    {
        DEBOUT("osSemaphoreWait: Timeout occured");
    }
    return numAvailToken +1;
}


/// Release a Semaphore token.
/// \param[in]     semaphore_id  semaphore object referenced with \ref osSemaphoreCreate.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osSemaphoreRelease shall be consistent in every CMSIS-RTOS.
osStatus osSemaphoreRelease (osSemaphoreId semaphore_id)
{
    SemaphoreHandle_t xSemaphore = (SemaphoreHandle_t)semaphore_id;
    osStatus result = osOK;

    if (0 == semaphore_id)
    {
        return osErrorParameter;
    }

    if(!isInterrupt())  // Thread mode
    {
       if (pdTRUE != xSemaphoreGive(xSemaphore))
       {
           result = osErrorResource;
           DEBOUT("Couldn't release Mutex/Sema");
       }
    }
    else   // Exception mode
    {
       BaseType_t xHigherPriorityTaskWoken = pdFALSE;
       if (pdTRUE == xSemaphoreGiveFromISR( xSemaphore, &xHigherPriorityTaskWoken))
       {
          // context switch if required....
          portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
       }
       else
       {
           result = osErrorResource;
           DEBOUT("Couldn't release Mutex/Sema in ISR (Queue Full Error)");
       }
    }
    return result;
}

/// Delete a Semaphore that was created by \ref osSemaphoreCreate.
/// \param[in]     semaphore_id  semaphore object referenced with \ref osSemaphoreCreate.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osSemaphoreDelete shall be consistent in every CMSIS-RTOS.
osStatus osSemaphoreDelete (osSemaphoreId semaphore_id)
{
    SemaphoreHandle_t xSemaphore = (SemaphoreHandle_t)semaphore_id;
    osStatus result = osOK;
    if (isInterrupt())
    {
        // CMSIS forbids call from ISR
        result = osErrorISR;
        return result;
    }
    if(!xSemaphore)
    {
        DEBOUT("Try to delete Mutex/Sema NULL pointer");
        result = osErrorParameter;
        return result;
    }

#ifdef DEBUG_CMSIS_API
    TaskHandle_t task = xSemaphoreGetMutexHolder( (QueueHandle_t)semaphore_id);
    char * taskName = "Unknown";
    if (0 != task)
    {
       // Mutex is hold by a task. No good idea to delete it.
        // maybe another Task is blocked?
        DEBOUT("Try to delete Mutex/Sema which is taken by a task");
#if (defined(INCLUDE_pcTaskGetTaskName) &&  (INCLUDE_pcTaskGetTaskName == 1))
        taskName = pcTaskGetTaskName(task);
#endif
        DEBOUT(taskName);
    }
#endif
    vSemaphoreDelete(xSemaphore);
    //prevent compile error
    return result;
}
#endif   // #if configUSE_COUNTING_SEMAPHORES == 1
#endif   // osFeature_Semaphore available

// =====[ Memory Pool Management Functions ]=====

#if (defined (osFeature_Pool)  &&  (osFeature_Pool != 0))  // Memory Pool Management available
#define MAILWITHPOOL

// JW The pool code is taken from:
// https://gentlenav.googlecode.com/svn-history/r3488/branches/MatrixPilot_beta/FreeRTOS/CMSIS_RTOS/cmsis_os.c
// http://o28.sischa.net/fifisdr/trac/browser/branches/fifisdr-pdl/pdl/libs/rtos/FreeRTOS-7.1.0/cmsis_os.c?rev=374

// start of ST Code:
//TODO
//This is a primitive and inefficient wrapper around the existing FreeRTOS memory management.
//A better implementation will have to modify heap_x.c!
//

typedef enum _marker
{
   FREE,
   USED
} Marker;

typedef struct os_pool_cb {
  void*         pool;
  Marker*       markers;
  QueueHandle_t memQueue;
  uint32_t      pool_sz;
  uint32_t      item_sz;
  union
  {
     uint32_t      currentIndex;
     QueueHandle_t mailQueue;
  };
} os_pool_cb_t;


/// Create and Initialize a memory pool.
/// \param[in]     pool_def      memory pool definition referenced with \ref osPool.
/// \return memory pool ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osPoolCreate shall be consistent in every CMSIS-RTOS.
osPoolId osPoolCreate (const osPoolDef_t *pool_def)
{

  osPoolId thePool;
  size_t itemSize = 0;
  uint32_t i;

  if (isInterrupt())
  {
    // CMISIS forbids call from ISR
    return 0;
  }
  if (!pool_def)
  {
    DEBOUT("NULL Pool Definition not allowed!");
    return 0;
  }
  itemSize = 4 * ((pool_def->item_sz + 3) / 4);

#ifdef STCODE
  /* First have to allocate memory for the pool control block. */
  thePool = (osPoolId)pvPortMalloc(sizeof(os_pool_cb_t));
  if (thePool)
  {
    thePool->pool_sz = pool_def->pool_sz;
    thePool->item_sz = itemSize;
    thePool->currentIndex = 0;

    /* Memory for markers */
    thePool->markers = (uint8_t*)pvPortMalloc(pool_def->pool_sz);
    if (thePool->markers)
    {
      /* Now allocate the pool itself. */
      thePool->pool = pvPortMalloc(pool_def->pool_sz * itemSize);
      if (thePool->pool)
      {
#ifdef DEBUG_CMSIS_API
        memset(thePool->pool, POOLPATTERN, (pool_def->pool_sz * itemSize));
#endif
        for (i = 0; i < pool_def->pool_sz; i++)
        {
          thePool->markers[i] = 0;
        }
      }
      else
      {
        vPortFree(thePool->markers);
        vPortFree(thePool);
        thePool = NULL;
        DEBOUT("Couldn't allocate memory for Mem Pool!");
      }
    }
    else
    {
      vPortFree(thePool);
      thePool = NULL;
      DEBOUT("Couldn't allocate memory for Mem Pool marker!");
    }
  }
  else
  {
    DEBOUT("Couldn't allocate memory for Mem Pool admin data!");
  }
#else    /* alternate implementation, jw                                     */
  /* First have to allocate memory for the pool control data and pool memory */
  size_t wantedSize = sizeof(os_pool_cb_t)                 /* control block  */
                    + pool_def->pool_sz * sizeof(Marker);  /* markers        */
  wantedSize = 4*((wantedSize+3)/4);             /* create 4 byte alignment! */
  wantedSize += pool_def->pool_sz * itemSize;              /* pool itself    */
  thePool = (osPoolId)pvPortMalloc(wantedSize);

  if (thePool)
  {
    thePool->pool_sz = pool_def->pool_sz;
    thePool->item_sz = itemSize;
    thePool->currentIndex = 0;
    /* Memory for markers */
    thePool->markers = (void *)thePool + sizeof(os_pool_cb_t);
    for (i = 0; i < pool_def->pool_sz; i++)
    {
      thePool->markers[i] = FREE;
    }
    /* Memory for the pool itself. (4 byte alligned)*/
    thePool->pool = (void *)(thePool) +  (wantedSize - pool_def->pool_sz * itemSize);
#ifdef DEBUG_CMSIS_API
    memset(thePool->pool, POOLPATTERN, (pool_def->pool_sz * itemSize));
#endif
  }
  else
  {
    DEBOUT("Couldn't allocate memory for Mem Pool data!");
  }
#endif
  return thePool;
}

/// Allocate a memory block from a memory pool.
/// \param[in]     pool_id       memory pool ID obtain referenced with \ref osPoolCreate.
/// \return address of the allocated memory block or NULL in case of no memory available.
/// \note MUST REMAIN UNCHANGED: \b osPoolAlloc shall be consistent in every CMSIS-RTOS.
void *osPoolAlloc (osPoolId pool_id)
{
  uint32_t isrMask = 0;
  void *p = NULL;
  uint32_t i;
  uint32_t index;

  if (!pool_id)
  {
    DEBOUT("osPoolAlloc NULL pool is not allowed!");
    return 0;
  }
  isrMask = enterCritical();   // prevent task switch
  for (i = 0; i < pool_id->pool_sz; i++)
  {
    index = (pool_id->currentIndex + i) % (pool_id->pool_sz);

    if (pool_id->markers[index] == FREE)
    {
      pool_id->markers[index] = USED;
      p = (void *)((uintptr_t)(pool_id->pool) + (index * pool_id->item_sz));
      pool_id->currentIndex = index;
      break;
    }
  }
  exitCritical(isrMask);  // enable task switch again
#ifdef DEBUG_CMSIS_API
  if (0 == p)
  {
    DEBOUT("osPoolAlloc couldn't get Memory");
  }
#endif
  return p;
}


/// Allocate a memory block from a memory pool and set memory block to zero.
/// \param[in]     pool_id       memory pool ID obtain referenced with \ref osPoolCreate.
/// \return address of the allocated memory block or NULL in case of no memory available.
/// \note MUST REMAIN UNCHANGED: \b osPoolCAlloc shall be consistent in every CMSIS-RTOS.
void *osPoolCAlloc (osPoolId pool_id)
{
  void *p = osPoolAlloc(pool_id);

  if (p != NULL)
  {
    memset(p, 0, pool_id->item_sz );  // JW: changed from MCD-ST code
  }
  else
  {
    DEBOUT("osPoolCAlloc couldn't get Memory");
  }

  return p;
}


/// Return an allocated memory block back to a specific memory pool.
/// \param[in]     pool_id       memory pool ID obtain referenced with \ref osPoolCreate.
/// \param[in]     block         address of the allocated memory block that is returned to the memory pool.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osPoolFree shall be consistent in every CMSIS-RTOS.
osStatus osPoolFree (osPoolId pool_id, void *block)
{
  uint32_t index;
  if (pool_id == NULL)
  {
    DEBOUT("Invalid PoolID");
    return osErrorParameter;
  }

  if (block == NULL)
  {
    DEBOUT("No zero Block allowed");
    return osErrorParameter;
  }

  if (block < pool_id->pool)
  {
      DEBOUT("Invalid Block ID");
      return osErrorValue;
  }

  index = (uint32_t)block - (uint32_t)(pool_id->pool);
  if (index % pool_id->item_sz)
  {
    DEBOUT("Invalid Block ID");
    return osErrorValue;
  }
  index = index / pool_id->item_sz;
  if (index >= pool_id->pool_sz)
  {
    DEBOUT("Invalid Block ID");
    return osErrorValue;
  }
  pool_id->markers[index] = FREE;
  // FIXME: Test me!!!  Added by JW Correct?????
  if (pool_id->currentIndex > index)
  {
    pool_id->currentIndex = index;   // start search at next alloc here!
  }

  return osOK;
}
#endif   // osFeature_Pool available

// =====[ Message Queue Management Functions ]=====
#if (defined (osFeature_MessageQ)  &&  (osFeature_MessageQ != 0))     // Message Queues available
/// Create and Initialize a Message Queue.
/// \param[in]     queue_def     queue definition referenced with \ref osMessageQ.
/// \param[in]     thread_id     thread ID (obtained by \ref osThreadCreate or \ref osThreadGetId) or NULL.
/// \return message queue ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osMessageCreate shall be consistent in every CMSIS-RTOS.
osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId thread_id)
{
    QueueHandle_t mPool = 0;
    UBaseType_t   queueLength = queue_def->queue_sz;
    UBaseType_t   itemSize    = queue_def->item_sz;

    if (isInterrupt())
    {
        // CMSIS forbids call from ISR
        return (osMessageQId)mPool;
    }
    if (0 == queueLength || sizeof(void *) != itemSize )  // only pointers or ints are allowed
    {
        DEBOUT("osMessageCreate: Parameter Error");
        return (osMessageQId)mPool;
    }
    // create mem Queue:
     mPool = xQueueCreate(queueLength, itemSize);
     if (0 == mPool)
     {
         DEBOUT("osMessageCreate: Couldn't create Queue");
     }
#ifdef USESTATEVIEW
     else
     {
         vQueueAddToRegistry( mPool, "MessageQueue");

     }
#endif
     //queue_def->pool = mPool;  // not allowed due to const
     return (osMessageQId)mPool;
}

/// Put a Message to a Queue.
/// \param[in]     queue_id      message queue ID obtained with \ref osMessageCreate.
/// \param[in]     info          message information.
/// \param[in]     millisec      timeout value or 0 in case of no time-out.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osMessagePut shall be consistent in every CMSIS-RTOS.
osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec)
{
    osStatus      xcode = osOK;
    QueueHandle_t mPool       = (QueueHandle_t)queue_id;
    TickType_t    ticksToWait = milliSecToTicks(millisec);      // get correct ticks, check for 0!

    if (0 == mPool)
    {
        return osErrorParameter;
    }
    if(!isInterrupt())   // Thread mode
    {
       if (pdTRUE != xQueueSend(mPool, &info, ticksToWait))
       {
          DEBOUT("osMessagePut: Queue full");
          if (0 == millisec)
          {
               xcode = osErrorResource;
          }
          else
          {
              xcode = osErrorTimeoutResource;
          }
       }
    }
    else              // Exception Mode
    {
       if(millisec == 0)
       {
          BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
          if (pdPASS == xQueueSendFromISR(mPool, &info, &xHigherPriorityTaskWoken))
          {
              // context switch if required....
              portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
          }
          else
          {
              DEBOUT("osMessagePut: Queue full");
              xcode = osErrorResource;
          }
       }
       else
       {
          xcode = osErrorParameter;
       }
    }
    return xcode;
}

/// Get a Message or Wait for a Message from a Queue.
/// \param[in]     queue_id      message queue ID obtained with \ref osMessageCreate.
/// \param[in]     millisec      timeout value or 0 in case of no time-out.
/// \return event information that includes status code.
/// \note MUST REMAIN UNCHANGED: \b osMessageGet shall be consistent in every CMSIS-RTOS.
osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec)
{
    osEvent       event;
    QueueHandle_t mPool       = (QueueHandle_t)queue_id;
    TickType_t    ticksToWait = milliSecToTicks(millisec);      // get correct ticks, check for 0!
    uint32_t      buffer;

    event.status = osOK;
    if (0 == mPool)
    {
        event.status  = osErrorParameter;
        event.value.v = 0;
        return event;
    }
    if(!isInterrupt())   // Thread mode
    {
       if (pdTRUE == xQueueReceive(mPool, (void *)&buffer, ticksToWait))
       {
           event.status  =  osEventMessage;
           event.value.p =  (void *)buffer;
       }
       else
       {
           if (0 == millisec)
           {
               event.status = osOK;   // no message in Queue
           }
            else
           {
               event.status = osEventTimeout;
           }
       }
    }
    else          // Exception Mode
    {
       if (0 == millisec)
       {
           BaseType_t  xHigherPriorityTaskWoken = pdFALSE;
           if (pdTRUE == xQueueReceiveFromISR(mPool, (void *)&buffer, &xHigherPriorityTaskWoken))
           {
               event.status  =  osEventMessage;
               event.value.p =  (void *)buffer;
           }
           else
           {
              event.status  =  osOK;    // no message was received
           }
       }
       else
       {
           event.status  = osErrorParameter;
       }
    }
    return event;
}
#endif   // Message Queues available

// =====[ Mail Queue Management Functions ]=====
#if (defined (osFeature_MailQ)  &&  (osFeature_MailQ != 0))     // Mail Queues available


#define POOLBASEDMAIL 0
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
typedef struct _MailAdmin
{
    osMailQId  id;
#ifdef MAILWITHPOOL
    osPoolId   poolId;
#else
    size_t     itemSize;
#endif
} MailAdmin;

static MailAdmin mailAdmin[MAXMAILBOXES];
static uint8_t   isMailBoxInit = FALSE;

// return index in field of given id.
// to find empty slot, set id to 0
static int32_t getMailBoxIndex(osMailQId id)
{
   int32_t  i = 0;
   int32_t  mIndex = -1;

   if(FALSE == isMailBoxInit)
   {
       memset( (void *)mailAdmin, 0, sizeof(mailAdmin));
       isMailBoxInit = TRUE;
   }
   for(i = 0; i < MAXMAILBOXES; ++i)
   {
       if (id == mailAdmin[i].id)
       {
           mIndex = i;
           i = MAXMAILBOXES;   // end of loop (I don't like break)
       }
   }
   return mIndex;
}
#endif

/// Create and Initialize mail queue.
/// \param[in]     queue_def     reference to the mail queue definition obtain with \ref osMailQ
/// \param[in]     thread_id     thread ID (obtained by \ref osThreadCreate or \ref osThreadGetId) or NULL.
/// \return mail queue ID for reference by other functions or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osMailCreate shall be consistent in every CMSIS-RTOS.
osMailQId osMailCreate (const osMailQDef_t *queue_def, osThreadId thread_id)
{
    QueueHandle_t mPool = 0;
    if (!queue_def)
    {
        DEBOUT("osMailCreate: invalid Mail Definition");
        return 0;
    }


    UBaseType_t   queueLength = queue_def->queue_sz;
    UBaseType_t   itemSize    = queue_def->item_sz;
#ifdef MAILWITHPOOL
    osPoolId     poolId = 0;
    osPoolDef_t  poolDefinition;
    poolDefinition.pool_sz = queue_def->queue_sz;
    poolDefinition.item_sz = queue_def->item_sz;
#endif

    if (0 == queueLength || 0 == itemSize )
    {
        DEBOUT("osMailCreate: Parameter Error");
        return (osMailQId)mPool;
    }

#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
    int32_t mSlot       = 0;
    mSlot = getMailBoxIndex(0);   // find free slot
    if (0 > mSlot)   // neg value returned, no free slot
    {
        DEBOUT("osMailCreate: No free Slot, increase MAXMAILBOXES");
        return (osMailQId)mPool;
    }
    // create mem Queue:
#endif
#ifdef MAILWITHPOOL
    poolId = osPoolCreate(&poolDefinition);
    if (0 == poolId)
    {
        DEBOUT("osMailCreate: No free memory for mail queue.");
        return (osMailQId)mPool;
    }
#endif

    // as there is no pool management in FreeRTOS, CMSIS Mails get their memory by malloc / osAlloc.
    // Therefore, only a pointer is stored in queue, itemSize must be sizeof(pointer)
    itemSize = sizeof(void *);
    mPool = xQueueCreate(queueLength, itemSize);
    if (0 != mPool)
    {
#ifdef USESTATEVIEW
         vQueueAddToRegistry( mPool, "MailQueue");
#endif
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
         mailAdmin[mSlot].id = (osMailQId)mPool;
#ifdef MAILWITHPOOL
        mailAdmin[mSlot].poolId  = poolId;
#else
        mailAdmin[mSlot].itemSize = (size_t)itemSize;
#endif
#else
        QueueHandle_t mMemQueue = 0;
        mMemQueue = xQueueCreate(queueLength, itemSize);
        if (0 != mMemQueue)
        {
#ifdef USESTATEVIEW
            vQueueAddToRegistry( mMemQueue, "MailMemQueue");
#endif
            for(UBaseType_t i  = 0; i < queueLength; ++i)
            {
                void* mem = osPoolAlloc(poolId);
                osMessagePut((osMessageQId)mMemQueue, (uint32_t)mem, 0);
            }
            poolId->mailQueue = mPool;
            poolId->memQueue  = mMemQueue;
            mPool = (QueueHandle_t)poolId;
        }
        else
        {
            DEBOUT("osMailCreate: Couldn't create Queue");
            vQueueDelete(mPool);
            mPool = 0;
        }

#endif
    }
    else
    {
        DEBOUT("osMailCreate: Couldn't create Queue");
    }
    //queue_def->pool = mPool;  // not allowed due to const
    return (osMailQId)mPool;
}

#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
// get memory, item size for queue is retrieved from static list
static void *allocMail(osMailQId queue_id, int32_t *slot)
{
    if(!queue_id)
    {
        DEBOUT("allocMail: NULL queue id");
        return 0;
    }

    int32_t mSlot = getMailBoxIndex(queue_id);
#ifdef MAILWITHPOOL
    osPoolId     poolId = 0;
#else
    size_t  mSize = 0;
#endif
    void *mData;

    if (0 > mSlot)   // neg value returned, slot not found
    {
        DEBOUT("allocMail: Couldn't find Mail Queue");
        return (void *)0;
    }
#ifdef MAILWITHPOOL
    poolId = mailAdmin[mSlot].poolId;
    mData  = osPoolAlloc(poolId);
#else
    mSize = mailAdmin[mSlot].itemSize;
    mData = pvPortMalloc( mSize );
#endif

    if (0 == mData)
    {
        DEBOUT("allocMail: no Memory available");
    }
    *slot = mSlot;
    return mData;
}
#endif
/// Allocate a memory block from a mail.
/// \param[in]     queue_id      mail queue ID obtained with \ref osMailCreate.
/// \param[in]     millisec      timeout value or 0 in case of no time-out
/// \return pointer to memory block that can be filled with mail or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osMailAlloc shall be consistent in every CMSIS-RTOS.
void *osMailAlloc (osMailQId queue_id, uint32_t millisec)
{
    if(isInterrupt() && millisec)
    {
        // CMISIS forbids timeout in ISR
        return 0;
    }
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
    int32_t mSlot = 0;   // not used

    void*   mData = allocMail(queue_id, &mSlot);
    return  mData;
#else
    if(!queue_id)
    {
        DEBOUT("osMailAlloc: NULL queue id");
        return 0;
    }
    void*   mData  = 0;
    osPoolId poolId = (osPoolId )queue_id;

    osEvent event = osMessageGet((osMessageQId)(poolId->memQueue), millisec);
    if(event.status == osEventMessage)
    {
       mData = event.value.p;
       uint32_t offset = mData - poolId->pool;
       uint32_t index  = offset / poolId->item_sz;
       (poolId->markers)[index] = USED;
    }
    return mData;
#endif
}

/// Allocate a memory block from a mail and set memory block to zero.
/// \param[in]     queue_id      mail queue ID obtained with \ref osMailCreate.
/// \param[in]     millisec      timeout value or 0 in case of no time-out
/// \return pointer to memory block that can be filled with mail or NULL in case of error.
/// \note MUST REMAIN UNCHANGED: \b osMailCAlloc shall be consistent in every CMSIS-RTOS.
void *osMailCAlloc (osMailQId queue_id, uint32_t millisec)
{
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
    int32_t mSlot = 0;   // needed to retrieve item size of pool
    if(isInterrupt() && millisec)
    {
        // CMISIS forbids timeout in ISR
        return 0;
    }
    void*   mData = allocMail(queue_id, &mSlot);
    if (mData)
    {
#ifdef MAILWITHPOOL
        memset(mData, 0, mailAdmin[mSlot].poolId->item_sz);
#else
        memset(mData, 0, mailAdmin[mSlot].itemSize);
#endif
    }
#else
    void *mData = osMailAlloc(queue_id, millisec);
    if (mData)
    {
        osPoolId poolId = (osPoolId )queue_id;
        memset(mData, 0, poolId->item_sz);
    }
#endif
    return mData;
}

/// Put a mail to a queue.
/// \param[in]     queue_id      mail queue ID obtained with \ref osMailCreate.
/// \param[in]     mail          memory block previously allocated with \ref osMailAlloc or \ref osMailCAlloc.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osMailPut shall be consistent in every CMSIS-RTOS.
osStatus osMailPut (osMailQId queue_id, void *mail)
{
    osStatus status;
    if (!queue_id)
    {
        status = osErrorParameter;
    }
    else if (!mail)
    {
        status = osErrorValue;

    }
    else
    {
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
        osMessageQId queueId = (osMessageQId)queue_id;
#else
        osPoolId poolId = (osPoolId )queue_id;
        osMessageQId queueId = (osMessageQId)(poolId->mailQueue);
#endif

        status = osMessagePut(queueId, (uint32_t)mail, 0);
    }
    return status;
}


/// Get a mail from a queue.
/// \param[in]     queue_id      mail queue ID obtained with \ref osMailCreate.
/// \param[in]     millisec      timeout value or 0 in case of no time-out
/// \return event that contains mail information or error code.
/// \note MUST REMAIN UNCHANGED: \b osMailGet shall be consistent in every CMSIS-RTOS.
osEvent osMailGet (osMailQId queue_id, uint32_t millisec)
{
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
    osMessageQId queueId = (osMessageQId)queue_id;
#else
    osEvent event;
    if (!queue_id)
    {
        event.status = osErrorParameter;
        event.value.v = 0;
        return event;
    }
    osPoolId poolId = (osPoolId )queue_id;
    osMessageQId queueId = (osMessageQId)(poolId->mailQueue);
#endif
    event = osMessageGet(queueId, millisec);
    if (osEventMessage == event.status)
    {
        event.status = osEventMail;
    }
    return event;
}

/// Free a memory block from a mail.
/// \param[in]     queue_id      mail queue ID obtained with \ref osMailCreate.
/// \param[in]     mail          pointer to the memory block that was obtained with \ref osMailGet.
/// \return status code that indicates the execution status of the function.
/// \note MUST REMAIN UNCHANGED: \b osMailFree shall be consistent in every CMSIS-RTOS.
osStatus osMailFree (osMailQId queue_id, void *mail)
{
    osStatus xcode = osOK;
    if (0 == queue_id)
    {
        DEBOUT("osMailFree: queue ID 0 not allowed");
        return osErrorParameter;
    }
    if (0 == mail)
    {
        DEBOUT("osMailFree: mail address 0 not allowed");
        return osErrorValue;
    }
#if (defined(POOLBASEDMAIL) && (POOLBASEDMAIL == 1))
#ifdef MAILWITHPOOL
    int32_t mSlot = getMailBoxIndex(queue_id);
    if (0 > mSlot)   // neg value returned, slot not found
    {
        DEBOUT("osMailFree: Couldn't find Mail Queue");
        return osErrorResource;
    }
    xcode = osPoolFree (mailAdmin[mSlot].poolId, mail);
#else
    vPortFree(mail);
#endif
#else
    osPoolId poolId = (osPoolId )queue_id;
    /* check if mail a valid adress in pool. */
    if (mail < poolId->pool)
    {
        DEBOUT("osMailFree: free address invalid!");
        return osErrorValue;
    }
    uint32_t offset = mail-poolId->pool;
    uint32_t index  = offset / poolId->item_sz;
    if(   (offset % poolId->item_sz)            // no block alignment!
       || (index >= poolId->pool_sz) )          // to much entries
    {
        DEBOUT("osMailFree: free address not aligned");
        return osErrorValue;
    }
    if( (poolId->markers)[index] == FREE)     //block not allocated!
    {
        DEBOUT("osMailFree: can't free unused block");
        return osErrorValue;
    }

    osMessageQId memQueueId = (osMessageQId)(poolId->memQueue);
    if(memQueueId)
    {
       (poolId->markers)[index] = FREE;
       xcode = osMessagePut(memQueueId, (uint32_t)mail, 0);
       if (xcode != osOK)
       {
          DEBOUT("osMailFree: unexpected error freeing block");
          xcode = osErrorValue;
       }
    }
    else
    {
       xcode =  osErrorParameter;
    }
#endif

    return xcode;
}
#endif  // Mail Queues available

/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_ErrorCodes.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_ErrorCodes_H
#define RXF_ErrorCodes_H

namespace RXF {
    enum ErrorCode
    {
        ERROR_TASK_CREATE_FAILED = 10, // Could not create an RTOS task. Check task configuration.
        ERROR_TASK_DELETE_FAILED = 11, // Could not delete an RTOS task.
        ERROR_TASK_SUSPEND_FAILED = 12, // Could not suspend an RTOS task.
        ERROR_TASK_RESUME_FAILED = 13, // Could not resume an RTOS task.
        ERROR_MUTEX_CREATE_FAILED = 20, // Could not create an RTOS mutex.
        ERROR_MUTEX_DELETE_FAILED = 21, // Could not cleanup an RTOS mutex.
        ERROR_MUTEX_LOCK_FAILED = 22, // Could not lock mutex.
        ERROR_MUTEX_UNLOCK_FAILED = 23, // Could not unlock mutex.
        ERROR_TICK_INIT_FAILED = 30, // Could not initialize RXF tick.
        ERROR_TIMER_RESTART_DETECTED = 40, // Detected a restart of a timer.
        ERROR_TIMEOUT_EVENT_RESTART_DETECTED = 50, // Detected a restart of a timeout event.
        ERROR_MEMORY_POOL_ALLOC_FAILED = 60, // Could not allocate memory.
        ERROR_MEMORY_POOL_FREE_FAILED = 61, // Could not free memory.
        ERROR_ACTIVE_QUEUE_EVENT_FAILED = 70, // Could not put event in queue.
        ERROR_DISCONNECTED_PORT = 80, // Called operation or event reception on disconnected port.
        ERROR_ACTIVE_MEMORY_ALLOC_FAILED = 90, // Could not allocate queue or stack memory for active class.
        ERROR_REACTIVE_EVENT_NOT_CONSUMED = 100, // Event was not consumed by reactive destination.
        ERROR_REACTIVE_TOO_FEW_NULL_CONFIGS = 101, // The null transition count has in invalid value. Check for application code generation problems.
        ERROR_REACTIVE_INFINITE_NULL_TRANSITIONS = 102, // The configured null transition count has exceeded.
        ERROR_REACTIVE_RECURSIVE_TRIGGERED_OPERATION_CALL = 103, // Detected recursive triggered operation call.
        ERROR_REACTIVE_RESTART_DETECTED = 104, // Detected restart of reactive class.
        ERROR_REACTIVE_EVENT_DESTINATION_IS_NULL = 105, // Detected Event with destination null.
        ERROR_MAIN_TASK_RTOS_INIT_FAILED = 110, // Could not init or start RTOS.
        ERROR_LIST_NO_FREE_MEMORY = 120, // Try to add new element to List but no free memory available.
        ERROR_LIST_INVALID_ITERATOR = 121, // Try to insert or erase an element at an invalid iterator position.
        ERROR_LIST_DEREFERENCING_END_ITERATOR = 122, // Accessing data from iterator pointing to EndItem will return NullValue.
        ERROR_MAP_NO_FREE_MEMORY = 130, // Try to add new element to Map but no free memory available.
        ERROR_MAP_INVALID_ITERATOR = 131, // Try to erase an element at an invalid iterator position.
        ERROR_MAP_DEREFERENCING_END_ITERATOR = 132, // Accessing data from iterator pointing to EndItem will return NullValue.
        ERROR_MAP_INVALID_KEY = 133 // Trying to access element with a key that is not contained in Map.
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_ErrorCodes.h
*********************************************************************/

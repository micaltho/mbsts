/*
 * mallocReentrant.c
 *
 *  Created on: 11.08.2017
 *      Author: Wuebbelmann
 */



/*
 * using arm-none-eabi-g++, which is installed with MCUXpresso environment, malloc and
 * free are not reentrant!
 *
 * Within FreeRtos, pvPortMalloc and vPortFree are called to handle dynamic memory. These
 * functions call vTaskSuspendAll / xTaskResumeAll before calling malloc / free and therefore
 * are reentrant.
 *
 * Within malloc/free, the functions __malloc_lock / __malloc_unlock are called to make malloc/free
 * thread safe. __malloc_lock / __malloc_unlock are functions with weak linker bindings, the
 * default implementations just contain a return statement.
 * Thus, the use of operators new / delete or malloc / free respectively is not thread safe!
 *  __malloc_lock / __malloc_unlock are overloaded here to make new / malloc calls thread safe.
 *
 *  Note: heap_3.c of FreeRtos also calls malloc/free.
 *        This decreases the performance of pvPortMalloc and vPortFree, as vTaskSuspendAll / xTaskResumeAll
 *        are called twice. This might needs some improvement.
 *
 *  LIMITATIONS: This fix makes malloc /free not interrupt safe!
 */

#ifdef __GNUC__

#ifdef __cplusplus
extern "C"
{
#endif

#include <reent.h>
#include "FreeRTOS.h"
#include <task.h>

void __malloc_lock(struct _reent* REENT)
{
    vTaskSuspendAll();
}


void __malloc_unlock(struct _reent* REENT)
{
    ( void ) xTaskResumeAll();
}

#ifdef __cplusplus
}   // extern "C"
#endif

#endif // __GNUC_


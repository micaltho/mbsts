/*
 * sbrk.c
 *
 *  Created on: 11.08.2017
 *      Author: Wuebbelmann
 */

/*
 * using arm-none-eabi-g++, which is installed with MCUXpresso environment, malloc does not check
 * if there is memory available on heap! !
 *
 *
 * Within malloc, the function _sbrk is called to check heap memory.
 * _sbrk is a function with weak linker binding, the default implementation just contains a
 * return statement.
 * Thus, the use of operators new  or malloc  respectively does not check for available memory!
 *  _sbrk is overloaded here to make new / malloc return 0 if no memory is available.
 *
 *  LIMITATION: if heap is located in data RAM, we assume 1 kiByte is used for stack!
 *  in RAM2, heap uses the whole RAM2 (32KiByte).
 *  Make sure that linkerscript heap.ldt is in project. It must contain:
 *   PROVIDE(${heap_symbol} = ADDR(.data_RAM2));
 *
 *   or in project properties (MCUXpresso):
 *   C/C++ Build -> Settings -> MCU C++ Linker -> Managed Linker Script -> Heap and Stack Placement:
 *   MCUXpresso Style is activated.
 *
 *
 */


#ifdef __GNUC__

#include <errno.h>



#ifdef __cplusplus
extern "C"
{
#endif


// start and end of Heap as defined in the linker script (_heap_start < _heap_end)
//extern unsigned int const _heap_start;

extern void *_pvHeapStart;        ///< contains start address of heap
extern void *_pvHeapLimit;        ///< contains end address of heap
extern void *_vStackTop;          ///< contains end address of stack


//extern unsigned int const _heap_end;
//unsigned int const _heap_end = 0x2007c000 + 0x8000;


/**
 * @brief                   Changes data segment space allocation (it may be called by malloc) .
 * @details                 It may be called by malloc() .
 * @param[in]   increment   Number of byte to be allocated .
 * @return                  On success the previous program break (program break = beginning of available mem) .
                            On error -1 .
 */

void *_sbrk(ptrdiff_t increment)
{
    static void *heap_free = 0;
    //static void*  _heap_end = (void *)&_pvHeapStart + 0x8000;
    static void*  _heap_end = (void *)&_pvHeapLimit;
    void *heap_prev;

    if  (heap_free == 0)
    {
        heap_free = (void *)&_pvHeapStart;      // First call
        if (heap_free < (void *)&_vStackTop)   // are we in .data RAM or in .data_RAM2?
        {
            _heap_end = (void *)&_vStackTop - 0x400;    // assume we need 1k of stack....
        }
    }

    if ((heap_free + increment) < ((void *) _heap_end))
    {
        heap_prev = heap_free;
        heap_free += increment;
        return heap_prev;
    }
    else
    {
        errno = ENOMEM;
        return ((void *) -1);
    }
}

#ifdef __cplusplus
}   // extern "C"
#endif

#endif // __GNUC_


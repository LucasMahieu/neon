/*
 * newlibStubs.c
 *
 *  Created on: 2013-01-14
 *      Author: Bryce Klippenstein
 *                Carmanah Signs inc.
 */

#include "newlibStubs.h"
#include <cstdint>
#include "errno.h"
#include "types.h"

void _exit(uint32_t code)
{
    while(1);
}

int* __errno(void)
{
    return (int*)&_impure_ptr->_errno;
}

caddr_t _sbrk(int incr)
{
    uint32_t* stack_ptr;
    extern char _end;        /* Defined by the linker */
    static char *heap_end;
    char *prev_heap_end;

    asm volatile ("MOV %[sp], SP" : [sp] "=r" (stack_ptr));

    if (heap_end == 0)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    if ((uint32_t*)(heap_end + incr) > stack_ptr)
    {
        while(1);
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}

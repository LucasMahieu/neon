/*
 * interrupt.c
 *
 *  Created on: 2012-12-31
 *      Author: Bryce Klippenstein
 */

#include "interrupt.h"
#include "MKL25Z4.h"
#include <cstdint>

void interruptEnable(uint32_t irq)
{
    if(irq < 32 && irq > 0)
        NVIC_ISER |= 1 << irq;
}

void interruptDisable(uint32_t irq)
{
    if(irq < 32 && irq > 0)
        NVIC_ICER |= 1 << irq;
}

void interruptPendingSet(uint32_t irq)
{
    if(irq < 32 && irq > 0)
        NVIC_ISPR |= 1 << irq;
}

void interruptPendingClear(uint32_t irq)
{
    if(irq < 32 && irq > 0)
        NVIC_ICPR |= 1 << irq;
}

void interruptSetPriority(uint32_t irq, uint32_t priority)
{
    uint32_t shiftValue;
    if(irq < 32 && irq > 0 && priority > 0 && priority < 4)
    {
        shiftValue = 8 * (irq%4) + 6;
        priority &= 0x00000003;

        if(irq > 0 && irq < 4) //this irq priority resides in NVIC_IPR0
        {
            NVIC_IPR0 = priority << shiftValue;
        }

        if(irq > 3 && irq < 8) //this irq priority resides in NVIC_IPR1
        {
            NVIC_IPR1 = priority << shiftValue;
        }

        if(irq > 7 && irq < 12) //this irq priority resides in NVIC_IPR2
        {
            NVIC_IPR2 = priority << shiftValue;
        }

        if(irq > 11 && irq < 16) //this irq priority resides in NVIC_IPR3
        {
            NVIC_IPR3 = priority << shiftValue;
        }

        if(irq > 15 && irq < 20) //this irq priority resides in NVIC_IPR4
        {
            NVIC_IPR4 = priority << shiftValue;
        }

        if(irq > 19 && irq < 24) //this irq priority resides in NVIC_IPR5
        {
            NVIC_IPR5 = priority << shiftValue;
        }

        if(irq > 23 && irq < 28) //this irq priority resides in NVIC_IPR6
        {
            NVIC_IPR6 = priority << shiftValue;
        }

        if(irq > 27 && irq < 32) //this irq priority resides in NVIC_IPR7
        {
            NVIC_IPR7 = priority << shiftValue;
        }
    }
}

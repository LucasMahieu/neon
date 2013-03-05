/*
 * systick.c
 *
 *  Created on: 2013-01-02
 *      Author: Bryce Klippenstein
 *              Carmanah Signs inc.
 */

#include "MKL25Z4.h"
#include <cstdint>

void systickEnable(void)
{
    SYST_CSR |= (uint32_t)0x00000001; //Set ENABLE to 1b - enable SYSTICK.
}

void systickDisable(void)
{
    SYST_CSR &= ~(uint32_t)0x00000001; //Clear ENABLE to 1b - enable SYSTICK.
}

void systickConfigure(void)
{
    SYST_CSR |= (uint32_t)0x00000004; //Set CLKSOURCE to 1b - processor clock (0b - processor clock / 16)
    SYST_CSR |= (uint32_t)0x00000002; //Set TICKINT to 1b - enable interrupt on wrap.
    SYST_RVR &= (uint32_t)0xFF000000;
    SYST_RVR |= (uint32_t)0x0000BB80; //Set Reload Register to 48000d -> 1ms.
}

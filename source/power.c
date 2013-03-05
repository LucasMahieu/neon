/*
 * power.c
 *
 *  Created on: 2013-01-02
 *      Author: Bryce Klippenstein
 *                Carmanah Signs inc.
 */

#include "MKL25Z4.h"
#include <cstdint>

void vllsEnable(void)
{
    SMC_PMPROT |= (uint8_t)0x02; //Write 1 to the AVLLS bit. Write once register, no need to clear.
}

void llsEnable(void)
{
    SMC_PMPROT |= (uint8_t)0x08; // SMC_PMPROT : ALLS=1
}

void vllsConfigure(uint8_t mode)
{
    SMC_PMCTRL &= (uint8_t)0xF8;
    SMC_PMCTRL |= (uint8_t)0x04; //write 100b (VLLSx) to the STOPM bitfield.

    if(mode == 0)
    {
        SMC_STOPCTRL &= (uint8_t)0xF8; //Write 000b to the VLLSM bitfield.
    }

    if(mode == 1)
    {
        SMC_STOPCTRL &= (uint8_t)0xF8; //Write 001b to the VLLSM bitfield.
        SMC_STOPCTRL |= (uint8_t)0x01;
    }

    if(mode == 3)
    {
        SMC_STOPCTRL &= (uint8_t)0xF8; //Write 011b to the VLLSM bitfield.
        SMC_STOPCTRL |= (uint8_t)0x03;
    }
}

void llsConfigure(void)
{
    SMC_PMCTRL &= (uint8_t)0xF8;
    SMC_PMCTRL |= (uint8_t)0x03; //SMC_PMPROT : STOPM=0b011
}

void vllsEnter(void)
{
    uint32_t DUMMY_READ;
    SCB_SCR |= (uint32_t)0x00000004; // Write 1b to the SLEEPDEEP bit in the SCR - See Arm Architecture v6m manual for details.
    DUMMY_READ = SCB_SCR;
    asm("WFI");
}

void llsEnter(void)
{
    uint32_t DUMMY_READ;
    SCB_SCR |= (uint32_t)0x00000004; // Write 1b to the SLEEPDEEP bit in the SCR - See Arm Architecture v6m manual for details.
    DUMMY_READ = SCB_SCR;
    asm("WFI");
}

void llwuConfigure(void)
{
    //uint32_t* llwu_pe2 = (uint32_t*)0x4007C000;
    SIM_SCGC5 |= 0x00000400; //enable Port B clock
    PORTB_PCR0 |= (uint32_t)0x00000102; //Configure portB0 as GPIO with pullup.
    GPIOB_PDDR &= ~(uint32_t)0x00000001; //Configure portB0 as input.

    LLWU_PE2 |= (uint8_t)0x0C; // Write 10b to WUPE5 bitfield. Configure PortB0 to trigger wake-up on falling edge.
    LLWU_FILT1 |= (uint8_t)0x65; //Configure LLWU_P5 to be filtered on both edges.
}

void wait(uint8_t ms)
{
    int i = 0;

    TPM0_SC |= 0x00000007; // Set prescaler to 128,
    TPM0_MOD = 375; // This should configure the timer to 1ms.
    TPM0_CONF |= 0x0E020000; // Set TRGSEL to 1110 and CSOO to 1
    TPM0_C0SC |= 0x00000030; //Set MSA, MSB to 11; ELSA, ELSB to 00

    for(i=0; i<ms; i++)
    {
        TPM0_SC |= (uint32_t)0x00000008; // turn on timer
        while(!(TPM0_SC & 0x00000080))
            ;
        TPM0_SC &= ~(uint32_t)0x00000008; // Turn off the timer.
        TPM0_CNT = 0; //clear the timer count
        TPM0_SC |= 0x00000080; // Reset the timer overflow flag.
    }

}

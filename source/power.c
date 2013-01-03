/*
 * power.c
 *
 *  Created on: 2013-01-02
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */

#include "MKL25Z4.h"
#include <cstdint>

void vllsEnable(void)
{
	SMC_PMPROT |= (uint8_t)0x02; //Write 1 to the AVLLS bit. Write once register, no need to clear.
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

void vllsEnter(void)
{
	uint32_t* scb_scr = (uint32_t*)0xE000ED10;
	uint32_t DUMMY_READ;
	*scb_scr |= (uint32_t)0x00000002;
	*scb_scr |= (uint32_t)0x00000004; // Write 1b to the SLEEPDEEP bit in the SCR - See Arm Architecture v6m manual for details.
	DUMMY_READ = *scb_scr;
	//__wfi();
	asm("WFI");
}

void llwuConfigure(void)
{
	SIM_SCGC5 |= 0x00000400; //enable Port B clock
	PORTB_PCR0 |= (uint32_t)0x00000102; //Configure portB0 as GPIO with pullup.
	GPIOB_PDDR &= ~(uint32_t)0x00000001; //Configure portB0 as input.

	LLWU_PE2 |= (uint8_t)0x08; // Write 10b to WUPE5 bitfield. Configure PortB0 to trigger wake-up on falling edge.
}

/*
 * board.c
 *
 *  Created on: 2013-01-03
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 *
 *	Contains functions relevant to the specific hardware implementation.
 */

#include "MKL25Z4.h"
#include <cstdint>
#include "interrupt.h"
#include "power.h"
#include "systick.h"
#include "board.h"
#include "uart.h"
#include "rtc.h"
#include "time.h"

void boardInit(void)
{
	SIM_SCGC5 |= 0x00000400; //enable Port B clock
	SIM_SCGC5 |= 0x00000200; //enable Port A clock

	PORTB_PCR19 |= (uint32_t)0x00000100; //Configure portB19 as GPIO (GREEN)
	GPIOB_PDDR |= (uint32_t)0x00080000; //Configure portB19 as output

	PORTA_PCR12 |= (uint32_t)0x000A0102; //Configure portA12 as GPIO with falling edge interrupt and pullup enabled.
	GPIOA_PDDR &= ~(uint32_t)(1<<12); //Configure portA12 as input.

	PORTB_PCR18 |= (uint32_t)0x00000100; //Configure portB18 as GPIO (RED)
	GPIOB_PSOR |= (uint32_t)0x00040000;
	GPIOB_PDDR |= (uint32_t)0x00040000; //Configure portB18 as output

	uart0Config();
	uart0Enable();

	llwuConfigure();
	vllsEnable();
	vllsConfigure(1);


	PMC_REGSC = 0x08;

	systickConfigure();

	interruptSetPriority(30,3);
	interruptEnable(30);

	interruptSetPriority(7,0); // Configure LLWU interrupt as highest priority.
	interruptEnable(7); //Enable LLWU interrupt.

	systickEnable();

	rtcInit();

	if(rtcGet() != 0)
	{
		rtcSet((time_t)1358206730);
	}

	rtcStart();

	interruptSetPriority(21,0); // Configure RTC Seconds interrupt as highest priority.
	interruptEnable(21); //Enable RTC Seconds interrupt.

}

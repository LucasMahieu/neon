/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#define PE_MCUINIT
#define wint_t uint8_t //Define this to make some of the standard libraries work.

#include "derivative.h" /* include peripheral declarations */
#include "MKL25Z4.h" //inlude register definitions
#include "interrupt.h"
#include "power.h"
#include "systick.h"
#include "board.h"
#include "uart.h"
#include <stdio.h>
#include <time.h>
#include "errno.h"
#include <cstdint>
#include "rtc.h"

volatile uint32_t buttonPushed;
volatile uint8_t systemTicked;
volatile uint8_t secondTicked;
volatile uint32_t DUMMYREAD;

void MCU_init(void); /* Device initialization function declaration */

int main(void)
{
	volatile int i = 0;
	extern volatile uint32_t buttonPushed;
	extern volatile uint8_t systemTicked;

	uint32_t ticks = 0;

	struct tm test;

	time_t etime = 0;

	buttonPushed = 0;
	systemTicked = 0;
	secondTicked = 0;
	
	MCU_init(); /* call device initialization */

	boardInit(); // Initialize board specific features. -> board.c

	uart0Send_n("System Boot\n\0");

	test.tm_sec = 0;
	test.tm_min = 0;
	test.tm_hour = 0;
	test.tm_mday = 1;
	test.tm_mon = 0;
	test.tm_year = 71;
	test.tm_isdst = -1;

	test.tm_sec = 45;
	//test.tm_min = 35;
	//test.tm_hour = 14;
	//test.tm_mday = 18;
	//test.tm_mon = 0;
	//test.tm_year = 113;
	//test.tm_isdst = -1;


	rtcStop();
	etime = mktime(&test);
	uart0Send_i(etime);
	uart0Send_n("\n\0");
	rtcSet(etime);
	rtcStart();

	printTime();

	while (1)
	{
		i = GPIOB_PDIR;

		if(systemTicked == 1)
		{
			systemTicked = 0;
			ticks++;
		}

		if(ticks >= 500)
		{
			ticks = 0;
			GPIOB_PTOR = (uint32_t)0x00080000; //toggle output of portB19
		}

		if(secondTicked)
		{
			printTime();
			secondTicked = 0;
		}

		if(buttonPushed) // What to do if the button is pushed.
		{
			buttonPushed = 0;
			vllsEnter(); //Enter Very-Low-Leakage Stop Mode
		}
	}
	//We should never get here.

	return 0;
}

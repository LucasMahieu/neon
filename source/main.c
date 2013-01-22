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

	buttonPushed = 0;
	systemTicked = 0;
	secondTicked = 0;
	
	MCU_init(); /* call device initialization */

	boardInit(); // Initialize board specific features. -> board.c

	uart0Send_n("System Boot\n\0");

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
			//secondTicked = 1;
			PORTC_PCR10 = 0x00000100; //Set PortC10 to GPIO
			PORTC_PCR11 = 0x00000100; //Set PortC11 to GPIO
			FGPIOC_PDDR |= 0x00000C00; //Set PortC10, PortC11 to HiZ
			FGPIOC_PCOR |= 0x00000C00; //Set PortC10, PortC11 to HiZ
			vllsEnter(); //Enter Very-Low-Leakage Stop Mode
		}
	}
	//We should never get here.

	return 0;
}

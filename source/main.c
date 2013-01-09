/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#define PE_MCUINIT

//#include <stdio.h>

#include "derivative.h" /* include peripheral declarations */
#include "MKL25Z4.h" //inlude register definitions
#include "interrupt.h"
#include "power.h"
#include "systick.h"
#include "board.h"
#include "uart.h"

volatile uint32_t buttonPushed;
volatile uint8_t systemTicked;
volatile uint32_t DUMMYREAD;

void MCU_init(void); /* Device initialization function declaration */

int main(void)
{
	volatile int i = 0;
	extern volatile uint32_t buttonPushed;
	extern volatile uint8_t systemTicked;
	uint32_t ticks = 0;
	uint8_t message[] = "System Boot\n\r";
	uint32_t sentData = 0;

	buttonPushed = 0;
	systemTicked = 0;
	
	MCU_init(); /* call device initialization */

	boardInit(); // Initialize board specific features. -> board.c

	sentData = uart0Send(message, 13);

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

		if(buttonPushed) // What to do if the button is pushed.
		{
			buttonPushed = 0;
			vllsEnter(); //Enter Very-Low-Leakage Stop Mode
		}
	}
	//We should never get here.

	return 0;
}

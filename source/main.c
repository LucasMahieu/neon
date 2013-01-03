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

volatile uint32_t buttonPushed;
volatile uint8_t systemTicked;

void MCU_init(void); /* Device initialization function declaration */

int main(void)
{
	//volatile int i = 0;
	extern volatile uint32_t buttonPushed;
	extern volatile uint8_t systemTicked;
	uint32_t ticks = 0;

	buttonPushed = 0;
	systemTicked = 0;
	
	MCU_init(); /* call device initialization */
		
	SIM_SCGC5 |= 0x00000400; //enable Port B clock  
	SIM_SCGC5 |= 0x00000200; //enable Port A clock
	
	PORTB_PCR19 |= (uint32_t)0x00000100; //Configure portB19 as GPIO (GREEN)
	GPIOB_PDDR |= (uint32_t)0x00080000; //Configure portB19 as output

	PORTB_PCR18 |= (uint32_t)0x00000100; //Configure portB18 as GPIO (RED)
	GPIOB_PDDR |= (uint32_t)0x00040000; //Configure portB18 as output
	GPIOB_PSOR |= (uint32_t)0x00040000;

	PORTA_PCR1 |= (uint32_t)0x000A0102; //Configure portA1 as GPIO with falling edge interrupt, and pullup enabled.
	GPIOA_PDDR &= ~(uint32_t)0x00000002; //Configure portA1 as input.

	llwuConfigure();
	vllsEnable();
	vllsConfigure(3);

	systickConfigure();

	interruptSetPriority(30,3);
	interruptEnable(30);

	interruptSetPriority(7,0); // Configure LLWU interrupt as highest priority.
	interruptEnable(7); //Enable LLWU interrupt.

	systickEnable();
		
	while (1)
	{
		//i = GPIOA_PDIR;

		if(systemTicked == 1)
		{
			systemTicked = 0;
			ticks++;
		}

		if(ticks >= 1000)
		{
			ticks = 0;
			GPIOB_PTOR = (uint32_t)0x00080000; //toggle output of portB19
		}
		//i = 0;

		if(buttonPushed) // What to do if the button is pushed.
		{
			buttonPushed = 0;
			//GPIOB_PTOR = (uint32_t)0x00040000; // Toggle the Red LED if the button was pushed.
			vllsEnter(); //Enter Very-Low-Leakage Stop Mode
		}
	}
	//We should never get here.

	return 0;
}

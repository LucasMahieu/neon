/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#define PE_MCUINIT

#include <stdio.h>

#include "derivative.h" /* include peripheral declarations */

#include "MKL25Z4.h" //inlude register definitions

void MCU_init(void); /* Device initialization function declaration */

int main(void)
{
	int counter = 0;
	volatile int i = 0;
	
	MCU_init(); /* call device initialization */
		
	SIM_SCGC5 |= 0x00000400; //enable Port B clock  
	
	PORTB_PCR19 |= (uint32_t)0x00000100; //Configure portB19 as GPIO
	GPIOB_PDDR |= (uint32_t)0x00080000; //Configure portB19 as output
		
	while (1)
	{
		GPIOB_PTOR = (uint32_t)0x00080000; //toggle output of portB19
		while(i < 5000000)
		{
			i++;
		}
		i = 0;			
	}
	//We should never get here.

	for(;;) {	   
	   	counter++;
	}
	
	return 0;
}

/*
 * board.c
 *
 *  Created on: 2013-01-03
 *      Author: Bryce Klippenstein
 *                Carmanah Signs inc.
 *
 *    Contains functions relevant to the specific hardware implementation.
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
#include "i2c.h"

void boardInit(void)
{
    SIM_SCGC5 |= 0x00000400; //enable Port B clock
    SIM_SCGC5 |= 0x00000200; //enable Port A clock
    SIM_SCGC5 |= 0x00001000; //enable Port D clock

    PORTB_PCR19 |= (uint32_t)0x00000100; //Configure portB19 as GPIO (GREEN)
    GPIOB_PDDR |= (uint32_t)0x00080000; //Configure portB19 as output

    PORTA_PCR12 |= (uint32_t)0x000A0102; //Configure portA12 as GPIO with falling edge interrupt and pullup enabled.
    GPIOA_PDDR &= ~(uint32_t)(1<<12); //Configure portA12 as input.

    PORTB_PCR18 |= (uint32_t)0x00000100; //Configure portB18 as GPIO (RED)
    GPIOB_PSOR |= (uint32_t)0x00040000;
    GPIOB_PDDR |= (uint32_t)0x00040000; //Configure portB18 as output

    PORTD_PCR1 |= (uint32_t)0x00000100; //Configure portD1 as GPIO (BLUE)
    FGPIOD_PSOR |= (uint32_t)0x00000002;
    FGPIOD_PDDR |= (uint32_t)0x00000002; //Configure portD1 as output

    //SIM_SCGC6 |= (uint8_t) 0x00800000; // Enable PIT clock

    SIM_SOPT2 |= 0x01000000; // Set TPM to use the MCGFLLCLK as a clock source
    // MCGFLLCLK is either 24MHz or 23 986 176Hz
    SIM_SCGC6 |= 0x01000000; // Enable TPM0 clock

    uart0Config();
    uart0Enable();

    llwuConfigure();
    vllsEnable();
    vllsConfigure(1);

    PMC_REGSC = 0x08;

    systickConfigure();

    interruptSetPriority(30,0); //Port A ISR
    interruptEnable(30);

    interruptSetPriority(7,0); // Configure LLWU interrupt as highest priority.
    interruptEnable(7); //Enable LLWU interrupt.

    systickEnable();

    rtcInit();
    rtcStart();

    interruptSetPriority(21,0); // Configure RTC Seconds interrupt as highest priority.
    interruptEnable(21); //Enable RTC Seconds interrupt.

    i2cInit();
    interruptSetPriority(9,3); // Configure I2C interrupt as Lowest priority.
    interruptEnable(9); //Enable I2C interrupt.

    interruptSetPriority(22,3); // Configure PIT interrupt as Lowest priority.
    interruptEnable(9); //Enable PIT interrupt.
}

void dm365_powerup(void)
{
    SIM_SCGC5 |= 0x00002000; //enable Port E clock

    PORTE_PCR2 |= (uint32_t)0x00000100; //Configure portE2 as GPIO (LDO_EN)
    PORTE_PCR3 |= (uint32_t)0x00000100; //Configure portE3 as GPIO (EN3)
    PORTE_PCR4 |= (uint32_t)0x00000100; //Configure portE4 as GPIO (EN2)
    PORTE_PCR5 |= (uint32_t)0x00000100; //Configure portE5 as GPIO (EN1)

    FGPIOE_PCOR = (uint32_t)0x0000003c; //Set portE2-E5 low.
    FGPIOE_PDDR = (uint32_t)0x0000003c; //Configure portE2-E5 as output.

    FGPIOE_PSOR = (uint32_t)0x00000020; // Set portE5 high. 5V supply
    wait(5);
    FGPIOE_PSOR = (uint32_t)0x00000010; // Set portE4 high. 1.35V supply
    wait(3);
    FGPIOE_PSOR = (uint32_t)0x00000008; // Set portE3 high. 1.8V supply
    wait(3);
    FGPIOE_PSOR = (uint32_t)0x00000004; // Set portE2 high. 3.3V supply
    wait(1);
    //FGPIOE_
}

void dm365_powerdown(void)
{

}

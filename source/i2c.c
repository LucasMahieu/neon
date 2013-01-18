/*
 * i2c.c
 *
 *  Created on: 2013-01-16
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */


#include <cstdint>
#include "MKL25Z4.h"
#include "i2c.h"

volatile uint8_t i2cState;
volatile uint8_t i2cRegister;
volatile uint8_t i2cData;

//Configure PortC10 PortC11 as I2C1 bus.
void i2cInit(void)
{
	SIM_SCGC4 |= 0x00000080; //Turn on I2C0
	SIM_SCGC5 |= 0x00000800; //Turn on PortC
	PORTC_PCR10 = 0x00000202; //Set PortC10 to I2C1 SCL
	PORTC_PCR11 = 0x00000202; //Set PortC11 to I2C1 SDA

	I2C1_A1 = 0x84; // Set address as 0x84
	I2C1_F = 0x6C; // Set MULT=1, ICR=0x2C -> this should give a baud rate of 20.821kHz at 23.986176MHz bus speed
	I2C1_C1 = 0x40; // Set IICIE=1
	//I2C1_SMB = 0x80; //Set FACK
	I2C1_C1	|= 0x80; //Set IICEN=1 (enable i2c)
}

uint8_t i2cGet(void)
{
	return 0;
}

void i2cSend(uint8_t data)
{
	//put some jazz here.
}

void i2cAck(uint8_t ack)
{
	uint8_t data;
	data = I2C1_C1;
	if(ack)
	{
		data &= 0xF7;
		I2C1_C1 = data;
	}

	else
	{
		data |= 0x08;
		I2C1_C1 = data;
	}
}

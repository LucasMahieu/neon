/*
 * i2c.h
 *
 *  Created on: 2013-01-16
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */

#ifndef I2C_C_
#define I2C_C_

#include <cstdint>

void i2cInit(void);

uint8_t i2cGet(void);

void i2cSend(uint8_t data);

void i2cAck(uint8_t ack);

#endif /* I2C_C_ */

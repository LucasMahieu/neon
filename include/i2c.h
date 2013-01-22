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

void i2cAck(uint8_t ack);

#endif /* I2C_C_ */

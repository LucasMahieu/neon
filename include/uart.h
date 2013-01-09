/*
 * uart.h
 *
 *  Created on: 2013-01-08
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */

#ifndef UART_H_
#define UART_H_

#include <cstdint>

//configures UART0. Should be done before enabling.

//uint8_t uart0Config(uint32_t baudrate); //Not working as this processor doesn't have a divider set up right.
void uart0Config(void);

//Turns on UART0 transmitter and receiver.
void uart0Enable(void);

//Turns off UART0 transmitter and receiver.
void uart0Disable(void);

//Send byte to UART0, wait until complete.
uint8_t uart0SendByte(uint8_t data);

//Send multiple bytes to UART0, wait until complete.
uint32_t uart0Send(uint8_t* data, uint8_t numBytes);

#endif /* UART_H_ */

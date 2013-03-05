/*
 * board.h
 *
 *  Created on: 2013-01-03
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 *
 *	Contains functions relevant to the specific hardware implementation.
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "MKL25Z4.h"
#include <cstdint>

// Performs initialization of processor for use on design 599-0056-00
void boardInit(void);

/* dm365_powerup
 * Performs the power up sequence for the DM365.
 * First we turn on the 1.35V supply
 * Wait a bit
 * Power up the 1.8V supply
 * Wait a bit
 * Power up the 3.3V supply
 */
void dm365_powerup(void);

/* dm365_powerdown
 * Performs the power down sequence for the DM365.
 * First we turn off the 3.3V supply
 * Wait a bit
 * Power down the 1.8V supply
 * Wait a bit
 * Power down the 1.35V supply
 */
void dm365_powerdown(void);

#endif /* BOARD_H_ */

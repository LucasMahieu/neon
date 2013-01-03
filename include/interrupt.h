/*
 * interrupt.h
 *
 *  Created on: 2012-12-31
 *      Author: bklippenstein
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <cstdint>


/* interruptEnable
 * Accepts an irq number from 0 to 31, enables irq in NVIC core.
 */
void interruptEnable(uint32_t irq);

/* interruptDisable
 * Accepts an irq number from 0 to 31, disables irq in NVIC core.
 */
void interruptDisable(uint32_t irq);

/* interruptPendingSet
 * Accepts an irq number from 0 to 31, sets irq pending in NVIC core.
 */
void interruptPendingSet(uint32_t irq);

/* interruptPendingClear
 * Accepts an irq number from 0 to 31, clears pending irq in NVIC core.
 */
void interruptPendingClear(uint32_t irq);

/* interruptSetPriority
 * Accepts an irq number from 0 to 31, and a priority from 0 to 3, sets irq priority in NVIC core.
 */
void interruptSetPriority(uint32_t irq, uint32_t priority);

#endif /* INTERRUPT_H_ */

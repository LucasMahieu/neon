/*
 * power.h
 *
 *  Created on: 2013-01-02
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */

#ifndef POWER_H_
#define POWER_H_

#include <cstdint>

//Enables the usage of the Very-Low-Leakage Stop Modes
void vllsEnable(void);

//Configure which VLLSx mode to use. Takes 0, 1 or 3  as argument - 2 is not a valid value.
void vllsConfigure(uint8_t mode);

//Enter VLLS.
void vllsEnter(void);

//Configure LLWU_P5 (portB0) as a wake-up trigger
void llwuConfigure(void);

#endif

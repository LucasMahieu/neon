/*
 * power.h
 *
 *  Created on: 2013-01-02
 *      Author: Bryce Klippenstein
 *                Carmanah Signs inc.
 */

#ifndef POWER_H_
#define POWER_H_

#include <cstdint>

//Enables the usage of the Very-Low-Leakage Stop Modes
void vllsEnable(void);

//Enables the usage of the Low-Leakage Stop Modes
void llsEnable(void);

//Configure which VLLSx mode to use. Takes 0, 1 or 3  as argument - 2 is not a valid value.
void vllsConfigure(uint8_t mode);

//Configure which LLS mode to use.
void llsConfigure(void);

//Enter VLLS.
void vllsEnter(void);

//Enter LLS.
void llsEnter(void);

//Configure LLWU_P5 (portB0) as a wake-up trigger
void llwuConfigure(void);

/* Idle for ms milliseconds.
 *
 * This is a blocking function, it won't return
 * until the wait time is complete.
 */
void wait(uint8_t ms);

#endif

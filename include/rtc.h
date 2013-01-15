/*
 * rtc.h
 *
 *  Created on: 2013-01-01
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */

#ifndef RTC_H_
#define RTC_H_

#include "cstdint"
#include "MKL25Z4.h"
#include "time.h"


//Initialize the real time clock;
void rtcInit(void);

//Set the time on the RTC. Takes unix time as an argument
void rtcSet(time_t unixTime);

//Start the RTC.
void rtcStart(void);

//Stops the RTC. Note, the RTC can not be set if it is started.
void rtcStop(void);

//Get the time from the real time clock. Return unix time.
time_t rtcGet(void);

//Outputs the current time to UART0. Ends with newline and null.
//Takes unix time as argument.
void printTime(void);

#endif /* RTC_H_ */

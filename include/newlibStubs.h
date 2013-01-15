/*
 * newlibStubs.h
 *
 *  Created on: 2013-01-14
 *      Author: Bryce Klippenstein
 *				Carmanah Signs inc.
 */

#ifndef NEWLIBSTUBS_H_
#define NEWLIBSTUBS_H_

#include <cstdint>
#include "errno.h"
#include "types.h"

void _exit(uint32_t code);

int* __errno(void);

caddr_t _sbrk(int incr);

#endif /* NEWLIBSTUBS_H_ */

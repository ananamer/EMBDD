/*
 * Clock.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#ifndef SRC_CLOCK_H_
#define SRC_CLOCK_H_
#include "stm32l4xx_hal.h"

typedef struct _clock
{
	uint32_t tick;
	uint32_t second;
	uint32_t minute;
	uint32_t hour;
	uint32_t day;

}CLOCK;


void ClockInit(CLOCK* clk);
//void time(CLOCK* clk);

void printClock(CLOCK* clk);
void ClockOnTimerPeriod(CLOCK* clk);
#endif /* SRC_CLOCK_H_ */

/*
 * Clock.c
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */
#include "main.h"
#include "Clock.h"
#include <stdio.h>
#include <stdio.h>
#include "MainTimer.h"

extern UART_HandleTypeDef huart2;


void ClockInit(CLOCK* clk)
{
	// to do : clock state, when receive "clock" swith it to start ||
	// and check if the state is on and start it
	clk->state = CLK_OFF;
	clk->tick = 0;
	clk->second = 0;
	clk->minute = 0;
	clk->hour = 0;
	clk->day = 0;
}

void clkOn(CLOCK* clk)
{
	MainTimer_registerCallback(ClockOnTimerPeriod ,clk);
	clk->state = CLK_ON;
}
void clkOff(CLOCK* clk)
{
	MainTimer_uregisterCallback(ClockOnTimerPeriod ,clk);
	clk->state = CLK_OFF;
}

void ClockOnTimerPeriod(CLOCK* clk){
	if(clk->state == CLK_ON){
		clk->tick ++;
		if(clk->tick >= 1000){
			clk->second++;
			clk->tick = 0;
			printf( "day=%d\t HH:MM:SS\t %d:%d:%d \t\r\n", (int) clk->day,(int) clk->hour,(int) clk->minute,(int) clk->second);
		}
		if(clk->second == 60){
			clk->minute ++;
			clk->second =0;
		}
		if(clk->minute == 60){
			clk->hour ++;
			clk->minute = 0;
		}
		if(clk->hour == 24){
			clk->day ++;
			clk->hour = 0;
		}
	}
}

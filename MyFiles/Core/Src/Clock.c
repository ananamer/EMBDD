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
extern UART_HandleTypeDef huart2;

void ClockInit(CLOCK* clk)
{
	clk->tick = 0;
	clk->second = 0;
	clk->minute = 0;
	clk->hour = 0;
	clk->day = 0;
}



void ClockOnTimerPeriod(CLOCK* clk){

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

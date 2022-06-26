/*
 * RGB.c
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#include "RGB.h"
#include <stdint.h>
#include <stdint.h>
#include "main.h"


void rgbInit(RGB* rgb, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	rgb->state = RGB_ON;
	rgb->counter = 0;
	rgb->GPIO_Pin = GPIO_Pin;
	rgb->GPIOx = GPIOx;
}


void rgbOn(RGB* rgb){
	HAL_GPIO_WritePin(rgb->GPIOx, rgb->GPIO_Pin, 1);
	rgb->state = RGB_ON;
}

void rgbOff(RGB* rgb)
{
	HAL_GPIO_WritePin(rgb->GPIOx, rgb->GPIO_Pin, 0);
	rgb->state = RGB_OFF;

}
void rgbBlink(RGB* rgb, int period)
{

	rgb->period = period;
	rgb->counter =0;
	rgb->state = RGB_BLINK;

}
void rgbOnTimerInterrupt(RGB* rgb)
{
//	if (rgb->state == RGB_BLINK) {
//		rgb->counter++;
//		if (rgb->counter >= rgb->period) {
			HAL_GPIO_TogglePin(rgb->GPIOx, rgb->GPIO_Pin);
//			rgb->counter=0;
//		}
//	}

}

void rgbOnPeriodTask(RGB* rgb);

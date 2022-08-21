/*
 * LED.c
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#include "LED.h"
#include <stdint.h>
#include <stdint.h>
#include "main.h"

#define maxCounter 500

void ledInit(LED* led, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	led->state = LED_ON;
	led->counter = 0;
	led->GPIO_Pin = GPIO_Pin;
	led->GPIOx = GPIOx;
//	MainTimer_registerCallback(ledOnTimerInterrupt ,led);

}

void ledOn(LED* led)
{
//	if(led->GPIO_Pin == LD3_Pin ){
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 1);
	led->state = LED_ON;
}

void ledOff(LED* led)
{
	MainTimer_uregisterCallback(ledOnTimerInterrupt ,led);
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 0);
	led->state = LED_OFF;

}

void ledBlink(LED* led, int period)
{
    //HAL_Delay(period);
	MainTimer_registerCallback(ledOnTimerInterrupt ,led);
	led->period = period;
	led->counter =0;
	led->state = LED_BLINK;
}

void ledOnTimerInterrupt(LED* led)
{
	if( led->state == LED_BLINK){
		led->counter ++;
	}
	if (led->counter >= maxCounter){
		led->counter = 0;
		HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
	}
}

void ledStart(LED* led)
{
	led->state = LED_BLINK;
}

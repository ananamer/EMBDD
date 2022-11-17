/*
 * LED.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "LED.h"
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
LED::LED() {
	// TODO Auto-generated constructor stub

}

LED::~LED() {
	// TODO Auto-generated destructor stub
}

LED::LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin, LED_STATE state){
	GPIOx = gpiox;
	GPIO_Pin = gpio_pin;
	State = state;
}

void LED::LedOn()
{
	State = LED_ON;
	HAL_GPIO_WritePin(this->GPIOx, this->GPIO_Pin, GPIO_PIN_SET);
}

void LED::LedOFF()
{
	State = LED_OFF;
	HAL_GPIO_WritePin(this->GPIOx, this->GPIO_Pin, GPIO_PIN_RESET);

}
void LED::LedBlink()
{
	State = LED_BLINK;
//	HAL_TIM_Base_Start_IT(&htim7);
}
void LED::LedStopBlink()
{
	State = LED_ON;
//	HAL_TIM_Base_Stop_IT(&htim7);
}


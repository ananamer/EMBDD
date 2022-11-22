/*
 * Button.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#include "Button.h"
//extern SW1_Pin GPIO_PIN_10
//extern SW1_GPIO_Port GPIOA
Button::Button() {
	// TODO Auto-generated constructor stub
}
Button::~Button() {
	// TODO Auto-generated destructor stub
}
Button::Button(GPIO_TypeDef* gpiox, uint16_t gpio_pin)
{
	GPIOx = gpiox;
	GPIO_Pin = gpio_pin;
}
//bool Button::isPressed()
//{
//	//NOT IN USE
//	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
//		}
//}
//void buttonOnTimerInterrupt()
//{
//
//	static uint32_t press, release;
//	if (HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 0) {
//		press = HAL_GetTick();
//	}
//	else {
//		release = HAL_GetTick();
//		if(( release - press) > 500){
//			HAL_UART_Transmit( &huart2 , (uint8_t*) "long press\r\n" , 14 , 100);
//		}
//		else{
//		HAL_UART_Transmit( &huart2 , (uint8_t*) "short press\r\n" , 15 , 100);
//		}
//	}
//
//}

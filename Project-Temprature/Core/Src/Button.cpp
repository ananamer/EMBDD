/*
 * Button.cpp
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#include "Button.h"


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


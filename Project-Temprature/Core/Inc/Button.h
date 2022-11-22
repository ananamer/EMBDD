/*
 * Button.h
 *
 *  Created on: Nov 20, 2022
 *      Author: student
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_
#include "main.h"

class Button {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
public:
	Button();
	virtual ~Button();
	Button(GPIO_TypeDef* gpiox, uint16_t gpio_pin);
	GPIO_TypeDef* getGpio(){return GPIOx;}
	uint16_t getPin(){return GPIO_Pin;}
//	bool isPressed();
};

#endif /* SRC_BUTTON_H_ */

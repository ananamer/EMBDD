/*
 * LED.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef LED_H_
#define LED_H_
#include "main.h"
typedef enum _ledState
{
	LED_OFF,
	LED_ON,
	LED_BLINK,
} LED_STATE;

class LED {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	LED_STATE State;
public:
	LED();
	virtual ~LED();
	LED(GPIO_TypeDef* gpiox, uint16_t gpio_pin, LED_STATE state);
	void LedOn();
	void LedOFF();
	void LedToggle(int delay);
	void LedBlink();
	void LedStopBlink();

	LED_STATE getState(){return State;}
	void setState(LED_STATE _state);
	GPIO_TypeDef* getGpio(){return GPIOx;}
	uint16_t getPin(){return GPIO_Pin;}
};

#endif /* LED_H_ */

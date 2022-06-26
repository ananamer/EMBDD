/*
 * RGB.h
 *
 *  Created on: Jun 14, 2022
 *      Author: student
 */

#ifndef SRC_RGB_H_
#define SRC_RGB_H_
#include <stdint.h>
#include "main.h"

typedef enum _rgbState
{
	RGB_OFF,
	RGB_ON,
	RGB_BLINK,
} RGB_STATE;


typedef struct _rgb
{
	RGB_STATE state;
	int counter;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int period;
}RGB;


void rgbInit(RGB* rgb, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void rgbOn(RGB* rgb);
void rgbOff(RGB* rgb);
void rgbBlink(RGB* rgb, int period);
void rgbOnTimerInterrupt(RGB* rgb);
void rgbOnPeriodTask(RGB* rgb);


#endif /* SRC_RGB_H_ */

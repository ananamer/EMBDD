/*
 * FlashLight.h
 *
 *  Created on: 9 Jun 2022
 *      Author: student
 */

#ifndef SRC_FLASHLIGHT_H_
#define SRC_FLASHLIGHT_H_



typedef enum FlashLightState_
{
	STATE_OFF,
	STATE_FULL,
	STATE_HALF,
	STATE_BLINK,

} FlashLightState;

FlashLightState changeState();
void LedHandle(FlashLightState);
void ledBLINK();
void ledHALF();
void ledFULL();
void LedOFF();
void setBrightness(int Brightness);
#endif /* SRC_FLASHLIGHT_H_ */

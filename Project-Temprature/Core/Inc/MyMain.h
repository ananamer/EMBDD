/*
 * MyMain.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_MYMAIN_H_
#define SRC_MYMAIN_H_

#include <stdio.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void my_main();
void HAL_GPIO_EXTI_Callback(uint16_t pin);
void measureTemp(void *argument);
void monitorInit();
void LedTask();
void dhtTask();
void TimeTask();

#ifdef __cplusplus
}
#endif


#endif /* SRC_MYMAIN_H_ */

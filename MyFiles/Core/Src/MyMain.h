/*
 * MyMain.h
 *
 *  Created on: Jun 21, 2022
 *      Author: student
 */

#ifndef SRC_MYMAIN_H_
#define SRC_MYMAIN_H_
#include "stm32l4xx_hal.h"

void My_Main();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim);
void HAL_GPIO_EXTI_Callback(uint16_t pin);
#endif /* SRC_MYMAIN_H_ */

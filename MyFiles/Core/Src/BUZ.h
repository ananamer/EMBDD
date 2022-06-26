/*
 * BUZ.h
 *
 *  Created on: Jun 19, 2022
 *      Author: student
 */

#ifndef SRC_BUZ_H_
#define SRC_BUZ_H_
#include "main.h"


typedef enum _buzState
{
	BUZ_OFF,
	BUZ_ON,
} BUZ_STATE;

typedef struct _buz
{
	BUZ_STATE state;
	int counter;
	int maxCounter;
}BUZ;

void noteChange( int i);
void buzzerStart(BUZ* buz);
void buzOnTimerInterrupt(BUZ* buz);
#endif /* SRC_BUZ_H_ */
//
///* USER CODE BEGIN PFP */
//int i=0;
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim)
//{
//	if(tim == &htim6){
//		noteChange(i);
//		i++;
//		if (i >= 12) {
//			i = 0;
//		}
//	}
//}
//
//void HAL_GPIO_EXTI_Callback(uint16_t pin)
//{
//	//HAL_TIM_Base_Start(&htim3);
//	if (HAL_GPIO_ReadPin(s_GPIO_Port, s_Pin) == 0) {
//
//		HAL_TIM_Base_Start(&htim3);
//		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//		HAL_TIM_Base_Start_IT(&htim6);
//	}
//	else {
//		HAL_TIM_Base_Stop(&htim3);
//		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//		HAL_TIM_Base_Stop_IT(&htim6);
//	}
//}
///* USER CODE END PFP */

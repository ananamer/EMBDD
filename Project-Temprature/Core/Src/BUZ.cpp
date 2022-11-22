/*
 * BUZ.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "BUZ.h"


BUZ::BUZ() {
	// TODO Auto-generated constructor stub

}
BUZ::BUZ(BUZ_STATE state)
{
	State = state;
}

BUZ::~BUZ() {
	// TODO Auto-generated destructor stub
}

void BUZ::buzzStart()
{
	State = BUZ_ON;
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void BUZ::buzzStop()
{
	State = BUZ_OFF;
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

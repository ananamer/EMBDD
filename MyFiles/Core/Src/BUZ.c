/*
 * BUZ.c
 *
 *  Created on: Jun 19, 2022
 *      Author: student
 */
#include "main.h"
#include <stdint.h>
#include <stdint.h>
#include "BUZ.h"
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;

//int notes[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
int notes[] = {294, 330, 349,    294, 330, 349,     294, 330, 349, 330, 294, 330, 294, 262};
int time[] =  {2,4,8, 8,2,8 ,2,2,4,2,2,1,4,2} ;

static int i=0;
void buzInit(BUZ* buz)
{
	buz->state = BUZ_OFF;
	buz->counter = 0;
	buz->maxCounter = 500;
}

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

void noteChange(int i)
{

	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, 100000/notes[i]);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,100000/time[i]/256);

}


void buzzerStart(BUZ* buz)
{
	buz->state = BUZ_ON;
//	noteChange(0);
}

void buzOnTimerInterrupt(BUZ* buz)
{
	if(buz->state == BUZ_ON) {
		buz->counter ++;

		if (buz->counter >= buz->maxCounter){
			buz->counter = 0;
			noteChange(i);
			i++;
			if (i >= 14) {
				i = 0;
			}
		}
	}

}

//if(tim == &htim6){
//	noteChange(i);
//	i++;
//	if (i >= 12) {
//		i = 0;
//	}

//{ 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494}
//  Do,   Do#, Re,   R#,    Mi,   Fa,   F#,   Sol,  Sol#, La,   La#,  Si

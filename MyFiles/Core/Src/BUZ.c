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
#include "MainTimer.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;
extern BUZ buz;
//int notes[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
int notes[] = {294, 330, 294, 330, 349,  0,  294, 330, 294, 330, 349,    0,       294, 330, 294, 330, 349,      330, 294, 330, 294, 262 ,0};
int time[] =  {4,4,4,4,2,                 2,  4,4,4,4,2,                  2,       4,4,4,4,2        ,2,2,4,4,2, 2} ;


//int notes [] = { mi , la , do , si, la la , so#,    mi, fa , fa, so , la, mi


//{ 262,   277, 294, 311,   330,  349, 370,   392,   415, 440,  466,  494}
//  Do,   Do#, Re,   R#,    Mi,   Fa,   F#,   Sol,  Sol#, La,   La#,  Si

//int notes[] = { 0,   330, 440, 262, 494, 440, 440, 415, 0,  330, 349, 349, 392, 440, 330 } ;
//int time [] = { 2,   2,1, 3,3,3,2,4                     ,3 ,4,2,2,2,4,2};
		//int notes[] = { 494,494,0  ,466,466,0  ,415,494,415,494,415,494,415,0 };
//int time[] =  { 4,4  ,4    ,4,4     ,4   ,2,1,1,1,1,4,8 ,4          } ;
//int notes[] = { 294,392, 440, 466, 392 ,0};
//int time [] = { 2   ,4   ,4   ,2   ,2  ,2};
size_t size = sizeof(notes)/sizeof(notes[0]);

static int i=0;
void buzInit(BUZ* buz)
{
	buz->state = BUZ_OFF;
	buz->counter = 0;
	buz->maxCounter = 500;


}

void noteChange(int i)
{
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_SET_AUTORELOAD(&htim3, 100000/notes[i]);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,100000/notes[i]/2);
}

void buzzerStart(BUZ* buz)
{
	MainTimer_registerCallback(buzOnTimerInterrupt ,buz);
	buz->state = BUZ_ON;
}
void buzzerStop(BUZ* buz)
{
	MainTimer_uregisterCallback(buzOnTimerInterrupt ,buz);
	buz->state = BUZ_OFF;
}

void buzOnTimerInterrupt(BUZ* buz)
{

	if(buz->state == BUZ_ON) {
		buz->counter ++;
		if (buz->counter >= buz->maxCounter){
			buz->counter = 0;
			noteChange(i);
			buz->maxCounter = 1000 / time[i];
			i++;
			if (i >= size) {
				i = 0;
			}
		}
	}
}

void playToneCmd(void * obj, char * param)
{
//	BUZ * buz = (BUZ *)obj;
	(void) obj;
	(void) param;
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	buzzerStart(&buz);
}
//{ 262,   277, 294, 311,   330,  349, 370,   392,   415, 440,  466,  494}
//  Do,   Do#, Re,   R#,    Mi,   Fa,   F#,   Sol,  Sol#, La,   La#,  Si

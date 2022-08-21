/*
 * Alarm.c
 *
 *  Created on: Aug 11, 2022
 *      Author: student
 */
#include "main.h"
#include "Alarm.h"
#include <stdio.h>

#define SIZE 10
#define BuffSIZE 8
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim6;
const uint32_t DaysInYear    = 365;
const uint32_t SecondsInMin  = 60;
const uint32_t SecondsInHour = 3600;
const uint32_t SecondsInDay  = 86400;

static const int _daysUntilMonth[] = {
		0,
		31,
		59,
		90,
		120,
		151,
		181,
		212,
		243,
		273,
		304,
		334,
		365
};

int numOfAlarms = 0;
ALARM alarmArr[SIZE] ;
uint8_t readBuff[BuffSIZE];
void createAlarm( DateTime* time, char* name)
{
	ALARM alarm;
//	printf("%s\r\n", name);
	Alarm_init(&alarm, time, name);

	alarmArr[numOfAlarms] = alarm;


	printf("succeed to add the alarm number #%d, the name is : %s\r\n", numOfAlarms+1, alarmArr[numOfAlarms].name);
//	printf("%s\r\n", alarmArr[numOfAlarms].name);
	numOfAlarms++;
}
void printAlarms()
{
	int i;
	printf("The alarms in the array are: \r\n");
	for ( i= 0;  i< numOfAlarms; i++) {
		printf("The name of alarm num#[%d] is: %s\r\n", i, alarmArr[i].name);
	}
}
void editAlarm()
{


}
uint32_t getSeconds(DateTime* dateTime)
{
	// calculate seconds from 00:00:00 1/1/2020


	uint32_t seconds = dateTime->sec +
			dateTime->min * SecondsInMin +
			dateTime->hours * SecondsInHour +
			dateTime->day * SecondsInDay +
			_daysUntilMonth[dateTime->month - 1] * SecondsInDay +
			dateTime->year * DaysInYear * SecondsInDay;
	if (dateTime->year % 4 == 0 && dateTime->month > 2) {
		// if current year is a leap year and month is after February
		// add seconds for February 29
		seconds += SecondsInDay;
	}
	// add seconds for all previous leap years
	seconds += (dateTime->year / 4) * SecondsInDay;
	return seconds;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * tim)
{

	if(tim==&htim6){
		DateTime time;
		HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0, 1, readBuff, 8, 0xff);
		// Calculating seconds
		uint8_t first_sec = readBuff[0] & 15;
		uint8_t last_sec = readBuff[0] >> 4;
		time.sec = first_sec + (last_sec*10);
		// Calculating minutes
		uint8_t first_min = readBuff[1] & 15;
		uint8_t last_min = readBuff[1] >> 4;
		time.min = first_min +(last_min*10);
		// Calculating minutes
		uint8_t first_hr = readBuff[2] & 15;
		uint8_t ten_hr = readBuff[2] >> 4;
		time.hours = first_hr +(ten_hr*10);
		//// Calculating days
		//time.day = readBuff[3] && 7;
		// Calculating Date
		uint8_t first_dt = readBuff[4] & 15;
		uint8_t last_dt = readBuff[4] >> 4;
		time.day = first_dt + (last_dt*10);
		// Calculating month
		uint8_t first_mn = readBuff[5] & 15;
		uint8_t last_mn = readBuff[5] >>4;
		time.month =  first_mn +(last_mn*10);
		// Calculating Year
		uint8_t first_yr = readBuff[6] & 15;
		uint8_t last_yr = readBuff[6] >>4;
		time.year =  first_yr +(last_yr*10);
		int i;
		for ( i= 0;  i< numOfAlarms; i++) {
			if(getSeconds(&time)==getSeconds(&alarmArr[i].time)){
				printf("buzzerOn\r\n");
			}
		}
	}

	//printf("%d:%d:%s:%d:%d:%d:%d\n\r", year, month, days[day-1] ,date, hours, minutes, seconds );
}

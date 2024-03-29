/*
 * Rtc.h
 *
 *  Created on: Aug 14, 2022
 *      Author: student
 */

#ifndef SRC_RTC_H_
#define SRC_RTC_H_

#include "main.h"

typedef struct Rtc_
{
	I2C_HandleTypeDef * hi2c;
	uint8_t devAddr;
} Rtc;

typedef struct DateTime_
{
	int sec;
	int min;
	int hours;
	int weekDay;
	int day;
	int month;
	int year;
} DateTime;


void rtcInit(Rtc * rtc, I2C_HandleTypeDef * hi2c, uint32_t devAddr);

void rtcWrite(Rtc * rtc, uint16_t memAddr, uint8_t * buffer, uint16_t size);

void rtcRead(Rtc * rtc, uint16_t memAddr, uint8_t * buffer, uint16_t size);

void rtcStart(Rtc * rtc);

void rtcStop(Rtc * rtc);

int rtcIsRunning(Rtc * rtc);

void rtcGetTime(Rtc * rtc, DateTime * dateTime);



void rtcSetTime( DateTime * dateTime);

#endif /* SRC_RTC_H_ */

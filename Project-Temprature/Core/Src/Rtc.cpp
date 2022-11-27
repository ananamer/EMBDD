/*
 * Rtc.cpp
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#include "Rtc.h"
#include "main.h"
#include <stdio.h>

Rtc::Rtc() {
	// TODO Auto-generated constructor stub

}

Rtc::~Rtc() {
	// TODO Auto-generated destructor stub
}

#define RTC_DATE_TIME_SIZE  7
#define RTC_START_STOP      (1 << 7)


void Rtc :: rtcWrite(uint16_t memAddr, uint8_t * buffer, uint16_t size)
{
	HAL_I2C_Mem_Write(_hi2c, _devAddr, memAddr, 1, buffer, size, 0xFF);
}

void Rtc :: rtcRead(uint16_t memAddr, uint8_t * buffer, uint16_t size)
{
	HAL_I2C_Mem_Read(_hi2c, _devAddr, memAddr, 1, buffer, size, 0xFF);
}

int Rtc :: bcdToInt(uint8_t bcd)
{
	return (bcd >> 4) * 10 + (bcd & 0x0F);
}

int Rtc :: intToBcd(int value, int minVal, int maxVal)
{
	if (value < minVal || value > maxVal)
	{
		return 0;
	}

	return ((value / 10) << 4) | (value % 10);
}
void Rtc :: rtcGetTime(DateTime* dateTime)
{
	uint8_t buffer[RTC_DATE_TIME_SIZE];
	HAL_I2C_Mem_Read(_hi2c, _devAddr, 0, 1, buffer, RTC_DATE_TIME_SIZE, 0xFF);

	// remove stop bit if set
	buffer[0] &= ~RTC_START_STOP;
	dateTime->sec = bcdToInt(buffer[0]);
	dateTime->min = bcdToInt(buffer[1]);
	dateTime->hours = bcdToInt(buffer[2]);
	dateTime->weekDay = buffer[3] & 0x07;
	dateTime->day = bcdToInt(buffer[4]);
	dateTime->month = bcdToInt(buffer[5]);
	dateTime->year = bcdToInt(buffer[6]);
}
void Rtc::printTime(DateTime * dateTime)
{
	rtcGetTime(dateTime);
	printf("%d:%d:%d - %d/%d/%d \n\r", dateTime->hours, dateTime->min, dateTime->sec ,
									   dateTime->day , dateTime->month  , dateTime->year     );


}
HAL_StatusTypeDef Rtc :: rtcSetTime( DateTime * dateTime)
{
	HAL_StatusTypeDef status;
	uint8_t buffer[RTC_DATE_TIME_SIZE];

	buffer[0] = intToBcd(dateTime->sec, 0, 59);
	buffer[1] = intToBcd(dateTime->min, 0, 59);
	buffer[2] = intToBcd(dateTime->hours, 0, 59);
	buffer[3] = dateTime->weekDay < 1 || dateTime->weekDay > 7 ? 0 : dateTime->weekDay;
	buffer[4] = intToBcd(dateTime->day, 1, 31);
	buffer[5] = intToBcd(dateTime->month, 1, 12);
	buffer[6] = intToBcd(dateTime->year, 1, 99);

	status = HAL_I2C_Mem_Write(_hi2c, _devAddr, 0, 1, buffer, RTC_DATE_TIME_SIZE, 0xFF);
	return status;
}


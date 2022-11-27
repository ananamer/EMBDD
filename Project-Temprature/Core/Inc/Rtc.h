/*
 * Rtc.h
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#ifndef SRC_RTC_H_
#define SRC_RTC_H_

#include "main.h"
#include "DateTime.h"

class Rtc {
private:
	I2C_HandleTypeDef * _hi2c;
	uint8_t _devAddr;

public:
	Rtc();
	virtual ~Rtc();

	Rtc (I2C_HandleTypeDef * hi2c, uint8_t devAddr)
		{
			_hi2c = hi2c;
			_devAddr = devAddr;
		}

	void rtcWrite(uint16_t memAddr, uint8_t * buffer, uint16_t size);
	void rtcRead(uint16_t memAddr, uint8_t * buffer, uint16_t size);
	void rtcGetTime(DateTime * dateTime);
	void printTime(DateTime * dateTime);
	HAL_StatusTypeDef rtcSetTime(DateTime * dateTime);
	int bcdToInt(uint8_t bcd);
	int intToBcd(int value, int minVal, int maxVal);

};

#endif /* SRC_RTC_H_ */

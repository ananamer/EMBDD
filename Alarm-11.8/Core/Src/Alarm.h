/*
 * Alarm.h
 *
 *  Created on: Aug 14, 2022
 *      Author: student
 */

#ifndef ALARM_H_
#define ALARM_H_
#include "Rtc.h"

#define nameSize 10

typedef enum _alarm
{
	ALARM_OFF,
	ALARM_ON,
	ALARM_SNOOZE,
	ALARM_TimeOut,
} ALARM_STATUS;


typedef struct alarm
{
	ALARM_STATUS state;
	DateTime time;
	char name[nameSize];
}ALARM;

void Alarm_init(ALARM* alarm, DateTime* time, char* name);
void printAlarms();

#endif /* ALARM_H_ */



//   HH:MM:SS


/*
 * Alarm.c
 *
 *  Created on: Aug 14, 2022
 *      Author: student
 */

#include "Alarm.h"
#include "Rtc.h"
#include <stdio.h>
#include <string.h>

#define buffSize 8

char buffer[buffSize];
DateTime getTime()
{

	printf("please enter the time in format :\t HH:MM:TT\r\n");
//	HAL_UART_Receive(&huart2, &buffer, 8, 10);


//	char str[] = "Geeks-for-Geeks"
//	    ;
//
//	    // Returns first token
//	    char* token = strtok(str, " - ");
//
//	    // Keep printing tokens while one of the
//	    // delimiters present in str[].
//	    while (token != NULL) {
//	        printf(" % s\n & quot;, token);
//	        token = strtok(NULL, " - ");
//	    }
//

}
void Alarm_init(ALARM* alarm, DateTime* time, char* name)
{


	alarm->state = ALARM_ON;
	alarm->time = *time;
//	alarm->name = name;
	strcpy(alarm->name, name);
}

/*
 * LogRecord.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#include "LogRecord.h"
#include <cstring>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "Rtc.h"

extern Rtc* rtc;
extern LogRecord Records[MAX_LOG_RECORDS];
extern int numOfRecords ;

LogRecord::LogRecord() {
	// TODO Auto-generated constructor stub

}

LogRecord::~LogRecord() {
	// TODO Auto-generated destructor stub
}
LogRecord::LogRecord(int type, double _temperature)
{
	if(type == 1){
		strcpy(Message, warningMsg);
	}
	else if(type == 2){
		strcpy(Message, criticalMsg);
	}
	else{
		printf("Error Record!\r\n");
		return;
	}

	Temperature = _temperature;
	rtc->rtcGetTime(&Time);


}

void LogRecord::printRecords(LogRecord Records[], int numOfRecords)
{
	int i;
	for (i = 0; i < numOfRecords; i++) {
		printf("%s-\r\nTemperature = %f\r\n",Records[i].Message, Records[i].Temperature);
		printf("%d:%d:%d - %d/%d/%d \n\r", Records[i].Time.hours, Records[i].Time.min, Records[i].Time.sec ,
										   Records[i].Time.day , Records[i].Time.month  , Records[i].Time.year     );

	}
}

void LogRecord::clearRecords(LogRecord Records[], int numOfRecords)
{
	int i;
	for (i = 0; i < numOfRecords; i++) {
		memset(&Records[i], 0, sizeof(Records[i]) );

	}
}
//
//void LogRecord::warningRecrod(double temperature)
//{
//
//	/*
//	 * warning time = get time from the rtc
//	 * temp = the temp passed in the function
//	 * message is strcpy with the defined warning msg
//	 * */
//
//	LogRecord Warning;
//	Warning.Temperature = temperature;
//	rtc->rtcGetTime(&Warning.Time);
//	strcpy(Warning.Message, warningMsg);
//
//	writeToRecords(Warning);)
//}
//
//void LogRecord::criticalRecrod(double temperature)
//{
//	LogRecord newCritical;
//	newCritical.Temperature = temperature;
//	rtc->rtcGetTime(&newCritical.Time);
//	strcpy(newCritical.Message, criticalMsg);
//
////	writeToRecords(Records, newCritical);
//
//
//}

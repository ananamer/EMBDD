/*
 * LogRecord.cpp
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#include "LogRecord.h"
#include <cstring>
#include <stdio.h>

LogRecord::LogRecord() {
	// TODO Auto-generated constructor stub

}

LogRecord::~LogRecord() {
	// TODO Auto-generated destructor stub
}

void LogRecord::writeToRecords(LogRecord Records[], LogRecord record, int numOfRecords)
{
	if(numOfRecords < MAX_LOG_RECORDS-1){
		Records[numOfRecords] = record;
		numOfRecords++;
	}
	else{
		printf("Out of Memory! Please clear the Log Records\r\n");
	}
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


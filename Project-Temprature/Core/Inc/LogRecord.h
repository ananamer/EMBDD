/*
 * LogRecord.h
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#ifndef SRC_LOGRECORD_H_
#define SRC_LOGRECORD_H_
#include "DateTime.h"
#include <iostream>
#include <cstring>

using namespace std;

#define MSG_LEN 20
#define MAX_LOG_RECORDS 50




char warningMsg[MSG_LEN] = "Warning!";
char criticalMsg[MSG_LEN] = "Critical!";

//string warningMsg = "Warning!";
//string criticalMsg = "Critical!";


class LogRecord {
private:
	DateTime Time;
	double Temperature;
	char Message[MSG_LEN];


public:
	LogRecord();
	virtual ~LogRecord();
	LogRecord(int type, double _temperature);

	void printRecords(LogRecord Records[], int numOfRecords);
	void clearRecords(LogRecord Records[], int numOfRecords);

	void warningRecrod(double temperature);
	void criticalRecrod(double temperature);
};
//void writeToRecords(LogRecord Records[], LogRecord record);
//void writeToRecords(LogRecord record);

#endif /* SRC_LOGRECORD_H_ */
















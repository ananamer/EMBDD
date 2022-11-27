/*
 * LogRecord.h
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

#ifndef SRC_LOGRECORD_H_
#define SRC_LOGRECORD_H_
#include "DateTime.h"

#define MSG_LEN 20
#define MAX_LOG_RECORDS 50

class LogRecord {
private:
	DateTime Time;
	double Temperature;
	char Message[MSG_LEN];


public:
	LogRecord();
	virtual ~LogRecord();

	void writeToRecords(LogRecord Records[], LogRecord record, int numOfRecords);
	void printRecords(LogRecord Records[], int numOfRecords);
	void clearRecords(LogRecord Records[], int numOfRecords);

};

#endif /* SRC_LOGRECORD_H_ */
















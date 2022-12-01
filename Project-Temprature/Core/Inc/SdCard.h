/*
 * SdCard.h
 *
 *  Created on: 1 Dec 2022
 *      Author: student
 */

#ifndef SRC_SDCARD_H_
#define SRC_SDCARD_H_

#include <string.h>
#include "fatfs.h"
#define FILE_NAME_MAX_SIZE 50

class SdCard {
private:
	char _fileName[FILE_NAME_MAX_SIZE];
	char _errorFileName[FILE_NAME_MAX_SIZE];
	FATFS _FatFs;
	FIL _fil;
	FRESULT _fres;
public:
	SdCard(){}
	virtual ~SdCard(){}
	SdCard(const char* name, const char* errorName);

	char* getFileName(){return _fileName;}
	char* getErrorFileName(){return _errorFileName;}

	void write(char* fileName, char* str);
	void clear(char* fileName);
	void print(char* fileName);
	void mount();
	void deMount();

};

#endif /* SRC_SDCARD_H_ */

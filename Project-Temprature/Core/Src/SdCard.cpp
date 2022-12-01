/*
 * SdCard.cpp
 *
 *  Created on: 1 Dec 2022
 *      Author: student
 */

#include "SdCard.h"
#include "MyMain.h"
#include <stdio.h>
#include "cmsis_os2.h"

SdCard::SdCard(const char* name, const char* errorName)
{
	strcpy(_fileName, name);
	strcpy(_errorFileName, errorName);
	mount();
}

void SdCard::print(char* fileName)
{
//	osMutexAcquire(fileMutexHandle,  osWaitForever);
	char line[100];
	_fres = f_open(&_fil, fileName, FA_READ | FA_OPEN_ALWAYS);
	if(_fres != FR_OK){
		printf("Error in file open(SdCard::print)\r\n");
	}

	while(f_gets(line, sizeof(line), &_fil)){
		printf("%s\r", line);
	}
	printf("\r\n");
	f_close(&_fil);
//	osMutexRelease(fileMutexHandle);

}

void SdCard::clear(char* fileName)
{
//	osMutexAcquire(fileMutexHandle,  osWaitForever);
	_fres = f_open(&_fil, fileName, FA_CREATE_ALWAYS);
	if(_fres != FR_OK){
		printf("Error in file open(SdCard::clear)\r\n");
	}
	else{
		printf("File cleared\r\n");
	}

	f_close(&_fil);
//	osMutexRelease(fileMutexHandle);


}

void SdCard::write(char* fileName, char* str)
{
//	osMutexAcquire(fileMutexHandle,  osWaitForever);
	_fres = f_open(&_fil, fileName, FA_WRITE | FA_OPEN_APPEND);
	if(_fres!= FR_OK){
		printf("Error in file open(SdCard::write) %d\r\n", _fres);
	}
	else{
		UINT bytesWrote;
		_fres = f_write(&_fil, str, strlen(str), &bytesWrote);
		if(_fres != FR_OK){
			printf("Error in file open(SdCard::write-else) %d\r\n", _fres);
		}
		else{
			printf("Success to write %i bytes\r\n", bytesWrote);
		}
	}
	f_close(&_fil);

//	osMutexRelease(fileMutexHandle);

}

void SdCard::mount()
{
	_fres = f_mount(&_FatFs, "", 1);
	if(_fres != FR_OK){
		printf("Error in file mount");
	}

//_fres = f_mount
//	    f_mount(fs, "", 0);                    /* Mount the default drive */

}






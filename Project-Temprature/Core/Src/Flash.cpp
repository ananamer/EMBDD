/*
 * Flash.cpp
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#include "Flash.h"
#include <stdio.h>
#include <string.h>

Flash::Flash() {
	// TODO Auto-generated constructor stub

}

Flash::~Flash() {
	// TODO Auto-generated destructor stub
}

HAL_StatusTypeDef Flash :: erasePage()
{
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef flashErase;
	flashErase.TypeErase = FLASH_TYPEERASE_PAGES;
	flashErase.Banks = _bank;
	flashErase.Page = _pageAddr;
	flashErase.NbPages = _nbPages;

	uint32_t pageError;
	HAL_FLASHEx_Erase(&flashErase, &pageError);
	if(pageError == 0xFFFFFFFF)
	{
		HAL_FLASH_Lock();
		return HAL_OK;
	}
	else
	{
		HAL_FLASH_Lock();
		return HAL_ERROR;
	}

}

HAL_StatusTypeDef Flash :: writeToPage(void* data, int dataSize)
{
	HAL_StatusTypeDef status;
	HAL_FLASH_Unlock();
	int index = 0;
	while (index < dataSize)
	{
		uint64_t Data =*(uint64_t*)(data+index); // add template
		status = HAL_FLASH_Program(_typeProgram, _pageAddr+index, Data);
		if(status != HAL_OK)
		{
			return status;
		}
		index += sizeof(uint64_t);
	}
	HAL_FLASH_Lock();
	return status;
}


void Flash :: setWarning(int warning)
{
	_thresholds.warningUsed = DATA_IN_USED;
	_thresholds.warning = warning;
	HAL_StatusTypeDef status;
	status = erasePage();
	if(status != HAL_OK)
	{
		printf("error in erase page in line %d in file %s\r\n", __LINE__, __FILE__);
	}
	status = writeToPage( &_thresholds, (sizeof(THRESHOLDS)));
	if(status != HAL_OK)
	{
		printf("error in write to page in line %d in file %s\r\n", __LINE__, __FILE__);
	}
	else
	{
		printf("saved in flash in line %d in file %s \r\n", __LINE__, __FILE__);
	}
}

void Flash :: setCritical(int critical)
{
	_thresholds.criticalUsed = DATA_IN_USED;
	_thresholds.critical = critical;
	HAL_StatusTypeDef status;
	status = erasePage();
	if(status != HAL_OK)
	{
		printf("error in erase page in line %d in file %s\r\n", __LINE__, __FILE__);
	}
	status = writeToPage( &_thresholds, (sizeof(THRESHOLDS)));
	if(status != HAL_OK)
	{
		printf("error in write to page in line %d in file %s\r\n", __LINE__, __FILE__);
	}
	else
	{
		printf("saved in flash in line %d in file %s \r\n", __LINE__, __FILE__);
	}
}

void Flash :: printThresHolds()
{
	THRESHOLDS* data = (THRESHOLDS *)(_pageAddr);
	memcpy(&_thresholds, data, sizeof(THRESHOLDS));
	_thresholds.criticalUsed == DATA_IN_USED? printf("critical = %d \r\n", _thresholds.critical):
											  printf("Please insert critical temp\r\n");

	_thresholds.warningUsed == DATA_IN_USED? printf("warning = %d \r\n", _thresholds.warning):
			  	  	  	  	  	  	  	  	 printf("Please insert warning temp\r\n");
}

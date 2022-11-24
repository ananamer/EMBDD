/*
 * Flash.h
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#ifndef SRC_FLASH_H_
#define SRC_FLASH_H_
#include "main.h"

#define DATA_IN_USED 1
#define DEFAULT_TEMP 50

struct THRESHOLDS
{
	uint16_t warningUsed;
	uint16_t warning;
	uint16_t criticalUsed;
	uint16_t critical;
};


class Flash {
private:

	uint32_t _bank;
	uint32_t _pageAddr;
	uint32_t _nbPages;
	uint32_t _typeProgram;
	THRESHOLDS _thresholds;

public:
	Flash();
	virtual ~Flash();

	Flash(uint32_t bank, uint32_t pageAddr, uint32_t nbPage, uint32_t typeProgram)
	{
		_bank = bank;
		_pageAddr = pageAddr;
		_nbPages = nbPage;
		_typeProgram = typeProgram;
	}
	HAL_StatusTypeDef erasePage();
	HAL_StatusTypeDef writeToPage(void* data, int dataSize);

	uint32_t getBank(){return _bank;}
	uint32_t getPageAddr(){return _pageAddr;}
	uint32_t getNbPages(){return _nbPages;}
	uint32_t getTypeProgram(){return _typeProgram;}

	int getWarning(){return _thresholds.warning;}
	int getCritical(){return _thresholds.critical;}


	void printThresHolds();
	void setWarning(int warning);
	void setCritical(int critical);
};

#endif /* SRC_FLASH_H_ */

/*
 * CLI.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "CLI.h"
#include "CliCommand.h"
#include "commTask.h"
#include "LED.h"
#include "MyMain.h"
#include <string.h>
#include "BUZ.h"
#include "DHT.h"
#include "Flash.h"
#include "SdCard.h"
#include <stdlib.h>

extern LED redLed;
extern LED bluLed;
extern BUZ buz;
extern DHT dht;
extern Flash Thresholds;
extern SdCard* LogSdCard;
extern char RecordsArr[50][100];

extern int numOfRecords;
int myGlobalVariable = 0;

CLI::CLI() {
	// TODO Auto-generated constructor stub
}

CLI::~CLI() {
	// TODO Auto-generated destructor stub
}


class BuzOnCmd : public CliCommand
{
	BUZ * _buz;
public:
	BuzOnCmd(BUZ * buz) : _buz(buz) {}
	void doCommand(const char* param) {
		_buz->buzzStart();
	}
};
class BuzOffCmd : public CliCommand
{
	BUZ * _buz;
public:
	BuzOffCmd(BUZ * buz) : _buz(buz) {}
	void doCommand(const char* param) {
		_buz->buzzStop();
	}
};

class LedOnCmd : public CliCommand
{
	LED * _led;
public:
	LedOnCmd(LED * led) : _led(led) {}
	void doCommand(const char* param) {
		_led->LedOn();
	}
};

class LedOffCmd : public CliCommand
{
	LED * _led;
public:
	LedOffCmd(LED * led) : _led(led) {}
	void doCommand(const char* param) {
		_led->LedOFF();
	}
};
class LedBlinkCmd : public CliCommand
{
	LED * _led;
public:
	LedBlinkCmd(LED * led) : _led(led) {}
	void doCommand(const char* param) {
		_led->LedBlink();
	}
};
// LedStopBlinkCmd may not be used
class LedStopBlinkCmd : public CliCommand
{
	LED * _led;
public:
	LedStopBlinkCmd(LED * led) : _led(led) {}
	void doCommand(const char* param) {
		_led->LedStopBlink();
	}
};

// TempCmd will read the temp from dht and print it
class TempCmd : public CliCommand
{
	DHT * _dht;
public:
	TempCmd(DHT * dht) : _dht(dht) {}
	void doCommand(const char* param) {
//		_dht->Dht_readAsync();
		_dht->DHT_main();
	}
};
class SetWarningCmd : public CliCommand
{
	Flash * _thresholds;
public:
	SetWarningCmd(Flash * thresholds) : _thresholds(thresholds) {}
	void doCommand(const char* param) {

	int value = atoi(param);
	_thresholds->setWarning(value);
	}
};
class SetCriticalCmd : public CliCommand
{
	Flash * _thresholds;
public:
	SetCriticalCmd(Flash * thresholds) : _thresholds(thresholds) {}
	void doCommand(const char* param) {

	int value = atoi(param);
	_thresholds->setCritical(value);
	}
};
class PrintThresholdsCmd: public CliCommand
{
	Flash * _thresholds;
public:
	PrintThresholdsCmd(Flash * thresholds) : _thresholds(thresholds) {}
	void doCommand(const char* param) {

	_thresholds->printThresHolds();
	}
};

void printRecords()
{
	if(numOfRecords > 0){
		printf("Records array[#%d]:\r\n", numOfRecords);
		for(int i=0; i<numOfRecords; i++){
			printf("%d-\t%s\r\n", i+1, RecordsArr[i]);
		}
	}
	else{
		printf("The RecordsArray is empty !\r\n");
	}
}
class PrintLogCmd: public CliCommand
{
public:
	void doCommand(const char* param) {
//		printRecords();
		LogSdCard->print("Log.txt");
	}
};

void clearRecords()
{
	if(numOfRecords > 0){
		for(int i=0; i<numOfRecords; i++){
			strcpy(RecordsArr[numOfRecords], "0");
			numOfRecords--;
		}
	}
	else{
		printf("The RecordsArray is empty !\r\n");
	}
}
class ClearLogCmd: public CliCommand
{
public:
	void doCommand(const char* param) {
//		clearRecords();
		LogSdCard->clear("Log.txt");
	}
};
// HelpCmd will print the commands in the CLI
class HelpCmd : public CliCommand
{
	CLI * _cli;
public:
	HelpCmd(CLI * cli) : _cli(cli) {}
	void doCommand(const char* param) {
		_cli->printCommands();
	}
};
void CLI::registerCommand(const char * name, CliCommand * command)
{
	if (commandsCount >= MAX_COMMANDS) {
			printf("Too many commands, cannot register\r\n");
			return;
		}

	container[commandsCount].name = name;
	container[commandsCount].command = command;
	commandsCount++;
}
void CLI::performCommand(char* cmd, char * param){
	for (int i = 0; i < commandsCount; i++) {
		if (strcmp(container[i].name, (char *)cmd) == 0) {
			container[i].command->doCommand(param);
			return;
		}
	}
	printf("Invalid command\r\n");
}
void CLI::printCommands()
{
	printf("Available commands:\r\n");
	for (int i = 0; i < commandsCount; i++) {
		printf("\t%s\r\n", container[i].name);
	}
}




void CLI::CliInit()
{

	registerCommand("redon", new LedOnCmd(&redLed));
	registerCommand("redoff", new LedOffCmd(&redLed));
	registerCommand("redblink", new LedBlinkCmd(&redLed));
	registerCommand("redstop", new LedStopBlinkCmd(&redLed));

	registerCommand("buzon", new BuzOnCmd(&buz));
	registerCommand("buzoff", new BuzOffCmd(&buz));

	registerCommand("temp", new TempCmd(&dht));
	registerCommand("setW", new SetWarningCmd(&Thresholds));
	registerCommand("setC", new SetCriticalCmd(&Thresholds));
	registerCommand("thresholds", new PrintThresholdsCmd(&Thresholds));

	registerCommand("printLog", new PrintLogCmd());
	registerCommand("clearLog", new ClearLogCmd());

	registerCommand("help", new HelpCmd(this));

}

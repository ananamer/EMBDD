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

extern LED redLed;
extern LED bluLed;
extern BUZ buz;
int myGlobalVariable = 0;

CLI::CLI() {
	// TODO Auto-generated constructor stub

}

CLI::~CLI() {
	// TODO Auto-generated destructor stub
}

class HelpCmd : public CliCommand
{
	CLI * _cli;
public:
	HelpCmd(CLI * cli) : _cli(cli) {}
	void doCommand(const char* param) {
		_cli->printCommands();
	}

};


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
class LedStopBlinkCmd : public CliCommand
{
	LED * _led;
public:
	LedStopBlinkCmd(LED * led) : _led(led) {}
	void doCommand(const char* param) {
		_led->LedStopBlink();
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

	registerCommand("help", new HelpCmd(this));

	registerCommand("buzon", new BuzOnCmd(&buz));
	registerCommand("buzoff", new BuzOffCmd(&buz));


//	registerCommand("blueon", new BluOnCmd(&bluLed));
//	registerCommand("blueoff", new BluOffCmd(&bluLed));

}

/*
 * CliCommand.cpp
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#include "CliCommand.h"
#include "LED.h"

extern LED redLed;
extern LED bluLed;

CliCommand::CliCommand() {
	// TODO Auto-generated constructor stub

}

CliCommand::~CliCommand() {
	// TODO Auto-generated destructor stub
}

//class LedOnCmd : public CliCommand
//{
//	LED * _led;
//public:
//	LedOnCmd(LED * led) : _led(led) {}
//	void doCommand(const char* param) {
//		_led->LedOn();
//	}
//};


//void CliCommand::CliInit()
//{
//	registerCommand("redon", new LedOnCmd(&redLed));
////	registerCommand("redoff", new LedOffCmd(&redLed));
////	registerCommand("redblink", new LedBlinkCmd(&redLed));
//
//}

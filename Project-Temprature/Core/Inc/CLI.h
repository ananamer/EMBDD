/*
 * CLI.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_CLI_H_
#define SRC_CLI_H_
#include "CliCommand.h"
#include "commTask.h"
#include "main.h"

extern int myGlobalVariable;


typedef struct _reg_comm
{
	const char* name ;
	CliCommand * command;
}REG_COMM;


class CLI {
	int commandsCount = 0;
	REG_COMM container[MAX_COMMANDS];
public:
	CLI();
	virtual ~CLI();
	void CliInit();
	void registerCommand(const char * name, CliCommand * command);
	void performCommand(char* cmd, char* param);
	void printCommands();


};

#endif /* SRC_CLI_H_ */

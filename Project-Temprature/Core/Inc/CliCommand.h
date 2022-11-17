/*
 * CliCommand.h
 *
 *  Created on: Nov 17, 2022
 *      Author: student
 */

#ifndef SRC_CLICOMMAND_H_
#define SRC_CLICOMMAND_H_

class CliCommand
{


public:
	CliCommand();
	virtual ~CliCommand();
	virtual void doCommand(const char* param) = 0 ; // pure virtual function

};

#endif /* SRC_CLICOMMAND_H_ */

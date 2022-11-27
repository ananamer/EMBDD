/*
 * Manager.h
 *
 *  Created on: Nov 22, 2022
 *      Author: student
 */

#ifndef SRC_MANAGER_H_
#define SRC_MANAGER_H_

typedef enum _system_state
{
	OK,
	WARNING,
	CRITICAL,
	CRITICAL_NO_BUZZER,

} SYSTEM_STATE;


class Manager {

	SYSTEM_STATE State;

public:
	Manager();
	Manager(SYSTEM_STATE _state)
	{
		State = _state;
	}
	SYSTEM_STATE getState(){return State;}
	void setState(SYSTEM_STATE _state)
	{
		State = _state;
	}

};


#endif /* SRC_MANAGER_H_ */


//////
/*
 * LogRecord.h
 *
 *  Created on: Nov 27, 2022
 *      Author: student
 */

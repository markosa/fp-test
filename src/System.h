/*
 * SystemState.h
 *
 *  Created on: Sep 23, 2018
 *      Author: markos
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "ProgramState.h"
#include "State.h"

class System {

public:
	System();
	State state;
	ProgramState programState;
	ProgramState nextProgramState;
	unsigned int currentDevTime;
	unsigned int currentStopTime;
	unsigned int currentFixTime;

};

#endif /* SYSTEM_H_ */

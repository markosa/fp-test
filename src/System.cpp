/*
 * SystemState.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: markos
 */

#include <stdio.h>
#include "Configuration.h"
#include "System.h"
#include "State.h"
#include "ProgramState.h"

System::System() {
	this->currentDevTime = NULL;
	this->currentFixTime = NULL;
	this->currentStopTime = NULL;
	this->programState = UNINITIALIZED;
	this->nextProgramState = UNINITIALIZED;
	this->state = INIT;
}


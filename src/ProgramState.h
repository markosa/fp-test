/*
 * ProgramState.h
 *
 *  Created on: Sep 23, 2018
 *      Author: markos
 */

#ifndef PROGRAMSTATE_H_
#define PROGRAMSTATE_H_

enum ProgramState {
	UNINITIALIZED, WAITING_USER, DEV_RUNNING, STOP_RUNNING, FIX_RUNNING, DONE
};

#endif /* PROGRAMSTATE_H_ */

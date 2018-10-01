/*
 * Button.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: markos
 */

#include "Button.h"
#include <stdio.h>

Button::Button(int adMin, int adMax, char *name) {
	this->adMin=adMin;
	this->adMax=adMax;
	this->namePtr=name;
}


/*
 * Settings.cpp
 *
 *  Created on: Sep 23, 2018
 *      Author: markos
 */

#include <stdio.h>
#include "Settings.h"
#include "Configuration.h"

Settings::Settings() {
	this->devTime=0;
	this->stopTime=0;
	this->fixTime=0;
	this->transitionTime=0;
	this->speed=0;
}

void Settings::save() {

}

void Settings::load() {

}

void Settings::debugPrintSettings() {
	debug_print("dev: %d stop: %d fix: %d transition: %d speed: %d", devTime, stopTime, fixTime, transitionTime,speed);
}


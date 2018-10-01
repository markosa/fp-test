/*
 * Settings.h
 *
 *  Created on: Sep 23, 2018
 *      Author: markos
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

class Settings {
public:
	Settings();
	unsigned int devTime;
	unsigned int stopTime;
	unsigned int fixTime;
	unsigned int transitionTime;
	unsigned int speed;
	void load();
	void save();
	void debugPrintSettings();

};

#endif /* SETTINGS_H_ */

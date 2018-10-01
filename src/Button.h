/*
 * Button.h
 *
 *  Created on: Sep 20, 2018
 *      Author: markos
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdio.h>

class Button {
public:

	Button(int adMin, int adMax, char *name);

	int getAdMax() const {
		return adMax;
	}

	void setAdMax(int adMax) {
		this->adMax = adMax;
	}

	int getAdMin() const {
		return adMin;
	}

	void setAdMin(int adMin) {
		this->adMin = adMin;
	}

	char* getNamePtr() const {
		return namePtr;
	}

	void setNamePtr(char* namePtr) {
		this->namePtr = namePtr;
	}

private:
	char *namePtr;
	int adMin;
	int adMax;

};

#endif /* BUTTON_H_ */

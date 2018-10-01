/*
 * MenuNode.h
 *
 *  Created on: Sep 25, 2018
 *      Author: markos
 */

#ifndef MENUNODE_H_
#define MENUNODE_H_

#include "Button.h"
class MenuNode {
public:

	MenuNode(char *name, Button *nextButton, void (*saveCallback)(const int));
	MenuNode(char *name, Button *prevButton, Button *nextButton, void(*saveCallback)(const int));
	Button* getNextButton();
	Button* getPrevButton();
	void (*saveCallback)(const int);
	char* getName();
private:
	char *name;
	Button* prevButton;
	Button* nextButton;

};



#endif /* MENUNODE_H_ */

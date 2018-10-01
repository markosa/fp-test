/*
 * MenuNode.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: markos
 */



#include "MenuNode.h"
#include "Configuration.h"
#include "Settings.h"
#include <stdio.h>

MenuNode::MenuNode(char *name, Button* next, void(*saveCallback)(const int)) {
	this->name=name;
	this->nextButton=next;
	this->prevButton=NULL;
	this->saveCallback=saveCallback;

}


MenuNode::MenuNode(char *name, Button* prev, Button* next, void(*saveCallback)(const int)) {
	this->name=name;
	this->nextButton=next;
	this->prevButton=prev;
	this->saveCallback=saveCallback;
}

char* MenuNode::getName() {
	return this->name;
}

Button* MenuNode::getNextButton() {
	if (nextButton == NULL)
		debug_print("nextButton is null", NULL);
	return nextButton;
}

Button* MenuNode::getPrevButton() {
	return this->prevButton;
}




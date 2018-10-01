/*
 * Menu.h
 *
 *  Created on: Sep 25, 2018
 *      Author: markos
 */

#ifndef MENU_H_
#define MENU_H_

#include "MenuNode.h"
#include "Configuration.h"

class Menu {

public:
	struct Position {
		int mainIndex;
		int subIndex;
	};

	Menu();
	void add(MenuNode* mainNode, MenuNode* subMenuNodes[], int length);
	MenuNode* getCurrentNode();
	void move(Button *button, int buttonValue);

	Position position;
	bool isMainMenuActive();

private:
	int mainMenuCount;

	MenuNode* nodes[MENU_MAX_MAIN_NODES][MENU_MAX_SUB_NODES];
	MenuNode* currentNode;
	void handleForwardMove(Button* button);
	void handleBackwardMove(Button* button);
	void moveToMainMenu();
	void handleCallback(MenuNode *node, int buttonValue);

};

#endif /* MENU_H_ */

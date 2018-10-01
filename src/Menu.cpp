/*
 * Menu.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: markos
 */

#include "Menu.h"
#include "Configuration.h"
#include <stdio.h>
#include <string.h>

Menu::Menu()
{
	this->mainMenuCount = 0;
	this->currentNode = NULL;
	this->position.mainIndex = 0;
	this->position.subIndex = 0;

	memset(this->nodes, NULL,
		   sizeof(this->nodes[0][0]) * (MENU_MAX_MAIN_NODES * MENU_MAX_SUB_NODES));
}

void Menu::add(MenuNode *mainNode, MenuNode *subMenuNodes[], int length)
{

	if (this->mainMenuCount > MENU_MAX_MAIN_NODES)
	{
		debug_print("mainNode limit reached.", NULL);
		return;
	}

	nodes[mainMenuCount][0] = mainNode;

	for (int i = 0; i < length; i++)
	{
		if (i > MENU_MAX_SUB_NODES)
		{
			debug_print("subNode limit reached", NULL);
			break;
		}
		nodes[mainMenuCount][i + 1] = subMenuNodes[i];
	}

	mainMenuCount++;
}

void Menu::moveToMainMenu()
{
	debug_print("Move to main menu \n", NULL);
	currentNode = NULL;
	position.mainIndex = 0;
	position.subIndex = 0;
}
void Menu::handleForwardMove(Button *button)
{
	if (position.subIndex + 1 > MENU_MAX_SUB_NODES)
	{
		moveToMainMenu();
		return;
	}

	MenuNode *nextNode = nodes[position.mainIndex][position.subIndex + 1];

	if (nextNode == NULL)
	{
		moveToMainMenu();
		return;
	}

	debug_print("Move from %s to %s, %d \n", currentNode->getName(), nextNode->getName(), position.subIndex);

	currentNode = nextNode;
	position.subIndex++;
}

void Menu::handleBackwardMove(Button *button)
{
	return;
}

void Menu::handleCallback(MenuNode *node, int buttonValue)
{
	if (node->saveCallback != NULL)
		node->saveCallback(buttonValue);
}

MenuNode *Menu::getCurrentNode()
{
	return this->currentNode;
}

bool Menu::isMainMenuActive()
{
	return (this->getCurrentNode() == NULL);
}

void Menu::move(Button *button, int buttonValue)
{
	if (isMainMenuActive())
	{
		for (int i = 0; i < mainMenuCount; i++)
		{
			MenuNode *mainMenuNode = nodes[i][0];
			if (mainMenuNode->getNextButton() == button)
			{
				debug_print("main menu node name: %s \n", mainMenuNode->getName());
				handleCallback(mainMenuNode, buttonValue);

				position.mainIndex = i;
				position.subIndex = 1;
				if (nodes[i][1] == NULL)
				{
					moveToMainMenu();
				}
				currentNode = nodes[i][1];
			}
		}
	}
	else
	{
		if (currentNode->getNextButton() == button)
		{
			handleCallback(currentNode, buttonValue);
			handleForwardMove(button);
		}
	}
}

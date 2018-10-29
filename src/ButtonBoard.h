#ifndef BUTTONBOARD_H_
#define BUTTONBOARD_H_

#include <stdio.h>
#include "Button.h"

class ButtonBoard
{
public:
  ButtonBoard(int pin, int threshold, Button *buttons, int buttonsLength);
  void handle();
  Button *getButton();
  void enable();
  void disable();
  bool isEnabled();
  bool isActive();

private:
  int pin;
  int threshold = 0;
  unsigned long lastPressedTime = 0;
  Button *buttons;
  Button *pressedButton;
  int buttonsSize;
  bool enabled = false;
};

#endif
#include "ButtonBoard.h"
#include "Configuration.h"
#include <Arduino.h>

ButtonBoard::ButtonBoard(int pin, int threshold, Button buttons[], int buttonsSize)
{
    this->pin = pin;
    this->threshold = threshold;
    this->buttons = buttons;
    this->buttonsSize = buttonsSize;
    this->lastPressedTime = 0;
    this->enabled = false;

    pinMode(BUTTON_SWITCH_BOARD_ANALOG_PIN, INPUT);
}

void ButtonBoard::handle()
{
    this->pressedButton = NULL;

    if ((millis() - lastPressedTime) > threshold)
    {
        int adcValue = analogRead(pin);
        for (int i = 0; i < buttonsSize; i++)
        {
            Button *b = &buttons[i];
            if (adcValue >= b->getAdMin() && adcValue <= b->getAdMax())
            {
                this->pressedButton = pressedButton;
                this->lastPressedTime = millis();
                break;
            };
        }
    }
    else
    {
        debug_print("ButtonBoard: handle: not in debounce threshold", NULL);
    }
}

bool ButtonBoard::isActive()
{
    return (this->pressedButton != NULL);
}

Button *ButtonBoard::getButton()
{
    return this->pressedButton;
}

void ButtonBoard::enable()
{
    this->enabled = true;
}
void ButtonBoard::disable()
{
    this->enabled = false;
}

bool ButtonBoard::isEnabled()
{
    return this->enabled;
}
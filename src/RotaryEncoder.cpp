#include <Arduino.h>
#include "stdio.h"
#include "Configuration.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int dtPin, int clkPin, int swPin)
{
  this->dtPin = dtPin;
  this->clkPin = clkPin;
  this->swPin = swPin;
  this->enabled = false;
  this->currentValue = 512;
  this->lastState = -1;
  pinMode(this->dtPin, INPUT);
  pinMode(this->clkPin, INPUT);
  pinMode(this->swPin, INPUT_PULLUP);
  //  digitalWrite(this->dtPin, HIGH);
  //  digitalWrite(this->clkPin, HIGH);
}

unsigned int RotaryEncoder::getCurrentValue()
{
  return this->currentValue;
}

void RotaryEncoder::setCurrentValue(unsigned int value)
{
  this->currentValue = value;
}

void RotaryEncoder::enable()
{
  this->enabled = true;
}

void RotaryEncoder::disable()
{
  this->enabled = false;
}

bool RotaryEncoder::isEnabled()
{
  return this->enabled;
}

void RotaryEncoder::interrupt()
{

  if (this->enabled)
  {

    if ((millis() - this->lastInterrupt) > ROTARY_ENCODER_DEBOUNCE_THRESHOLD)
    {
      int currentState = digitalRead(dtPin);

      if (currentState != this->lastState)
      {
        if (currentState == LOW)
        {
          currentValue--;
        }
        else
        {
          currentValue++;
        }
        this->lastState = currentState;
        this->lastInterrupt = millis();
      }
    }
  }
}

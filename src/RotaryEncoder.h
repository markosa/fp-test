#include <Arduino.h>
#include "stdio.h"
#include "Configuration.h"

class RotaryEncoder
{
public:
  RotaryEncoder(int dtPin, int clkPin, int swPin);
  void setCurrentValue(unsigned int value);
  unsigned int getCurrentValue();
  void interrupt();
  void enable();
  void disable();
  bool isEnabled();
  int lastState = -1;

private:
  int dtPin = 0;
  int clkPin = 0;
  int swPin = 0;
  volatile unsigned long lastInterrupt = 0;
  volatile unsigned int currentValue = 0;
  bool enabled;
};
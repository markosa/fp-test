#include <Arduino.h>
#include "Configuration.h"
#include "Settings.h"

#ifndef MOTOR_H_
#define MOTOR_H_

class Motor
{

public:
  enum MotorState
  {
    IDLE,
    IDLE_TO_CW,
    CW,
    IDLE_TO_CCW,
    CCW,
    TO_IDLE
  };
  Motor();
  void rotate(MotorState state, unsigned char pwm);
  void adjustSpeed(unsigned char pwm);
  void start(unsigned int pwm);
  void stop();
  MotorState getCurrentState();

private:
  MotorState state;
  int currentPWMValue;
};

#endif /* MOTOR_H_ */

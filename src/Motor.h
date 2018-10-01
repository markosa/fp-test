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
        CW,
        CCW
    };
    Motor();
    void rotate(MotorState state, unsigned int pwm);
    void start(unsigned int pwm);
    void stop();

  private:
    MotorState state;
    int currentPWMValue;
};

#endif /* MOTOR_H_ */

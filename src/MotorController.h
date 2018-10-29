#include <Arduino.h>
#include "Configuration.h"
#include "Settings.h"
#include "Motor.h"

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_
#define MOTOR_CONTROL_STATES 6
class MotorController
{

public:
  MotorController(Motor *motor, unsigned long dirChangeInterval, unsigned long transitionTime, unsigned char maxPWMSpeed);
  void setDirChangeInterval(unsigned long dirChangeInterval);
  void setTransitionTime(unsigned long transitionTime);
  void start(unsigned long duration);
  void handle();
  void stop();

private:
  Motor *motor;
  Motor::MotorState motorStates[MOTOR_CONTROL_STATES] = {Motor::IDLE_TO_CW, Motor::CW, Motor::TO_IDLE, Motor::IDLE_TO_CCW, Motor::CCW, Motor::TO_IDLE};
  void forwardState();
  void updateTransitionPWMStep();
  void handleToIdle();
  void handleIdleToRun(Motor::MotorState dir);
  void handleRunningState(Motor::MotorState dir);

  unsigned long dirChangeInterval;
  unsigned long transitionTime;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long duration;
  unsigned long transitionStartTime = 0;
  int currentControllerState = -1;
  unsigned char maxPWMSpeed;
  unsigned long lastPWMAdjustTime = 0;
  unsigned int transitionPWMStep = -1;
  unsigned char currentPWM = 0;
};

#endif
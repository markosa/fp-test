#include "MotorController.h"
#include <math.h>

static const unsigned long PWM_ADJUST_INTERVAL = 50;

MotorController::MotorController(Motor *motor, unsigned long dirChangeInterval, unsigned long transitionTime, unsigned char maxPWMSpeed)
{
    this->motor = motor;
    this->dirChangeInterval = dirChangeInterval;
    this->transitionTime = transitionTime;
    this->maxPWMSpeed = maxPWMSpeed;
    updateTransitionPWMStep();
}

void MotorController::start(unsigned long duration)
{
    this->currentControllerState = 0;
    this->duration = duration;
    updateTransitionPWMStep();
}

void MotorController::stop()
{

    for (unsigned char pwm = this->currentPWM; pwm > 0; pwm--)
    {
        this->motor->adjustSpeed(pwm);
    }
    this->currentPWM = 0;
    this->motor->stop();
    this->currentControllerState = -1;
    this->endTime = millis();
    this->transitionStartTime = 0;
    debug_print("MotorController::forwardState() Stopping motor. Stats: started: %lu ended: %lu duration: diff: %lu", this->startTime, this->endTime, this->duration, ((this->endTime - this->startTime) - duration));
}

void MotorController::handle()
{

    if (this->currentControllerState != -1)
    {
        Motor::MotorState motorState = motorStates[this->currentControllerState];

        switch (motorState)
        {
        case Motor::MotorState::TO_IDLE:
            this->handleToIdle();
            break;
        case Motor::IDLE_TO_CW:
            this->handleIdleToRun(Motor::CW);
        case Motor::IDLE_TO_CCW:
            this->handleIdleToRun(Motor::CCW);
            break;
        case Motor::MotorState::CW:
            this->handleRunningState(Motor::CW);
            break;
        case Motor::MotorState::CCW:
            this->handleRunningState(Motor::CCW);
            break;
        }
    }
}

void MotorController::handleIdleToRun(Motor::MotorState dir)
{
    if ((millis() - lastPWMAdjustTime) > PWM_ADJUST_INTERVAL)
    {

        if (this->transitionStartTime == 0)
            this->transitionStartTime = millis();

        this->currentPWM += this->transitionPWMStep;

        if (this->currentPWM >= this->maxPWMSpeed)
            this->currentPWM = this->maxPWMSpeed;

        if (this->motor->getCurrentState() == Motor::MotorState::IDLE)
        {
            this->motor->rotate(dir, this->currentPWM);
        }
        else
        {
            motor->adjustSpeed(this->currentPWM);
        }

        if (this->currentPWM = this->maxPWMSpeed)
        {

            this->forwardState();
        }
    }
}

void MotorController::handleRunningState(Motor::MotorState dir)
{
    if (this->motor->getCurrentState() == dir)
    {
        if (this->transitionStartTime == 0)
            this->transitionStartTime = millis();

        if (((millis() - this->transitionStartTime) - this->transitionTime) >= this->dirChangeInterval)
            this->forwardState();
    }
    else
    {
        debug_print("Illegal Motor state - should be %d but is %d", dir, this->motor->getCurrentState());
    }
}

void MotorController::handleToIdle()
{
    if (this->transitionStartTime == 0)
        this->transitionStartTime = millis();

    this->currentPWM -= this->transitionPWMStep;
    this->motor->adjustSpeed(this->currentPWM);

    if (motor->getCurrentState() == Motor::IDLE)
    {
        this->forwardState();
    }
}

void MotorController::updateTransitionPWMStep()
{
    float stepsInTimeline = transitionTime / PWM_ADJUST_INTERVAL;
    float stepsInPWM = this->maxPWMSpeed / stepsInTimeline;
    this->transitionPWMStep = round(stepsInPWM);
}

void MotorController::forwardState()
{
    unsigned long now = millis();

    if ((now - this->startTime) >= this->duration)
    {
        stop();
        return;
    }

    this->currentControllerState++;
    this->currentControllerState %= (MOTOR_CONTROL_STATES - 1);
    this->transitionStartTime = 0;
}

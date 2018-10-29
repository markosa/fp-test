
#include "Motor.h"
#include <stdio.h>
#include <Arduino.h>
/**
 * 
 * DC Motor Handler via H.BRIDGE
 *  
 * Markos
 * 
 **/

Motor::Motor()
{
    this->state = IDLE;
    this->currentPWMValue = 0;
}

void Motor::stop()
{
    analogWrite(HBRIDGE_PWM_PIN, 0);
    digitalWrite(HBRIDGE_ENA_A_PIN, LOW);
    digitalWrite(HBRIDGE_ENA_B_PIN, LOW);
    this->state = IDLE;
    this->currentPWMValue = 0;
}
void Motor::start(unsigned int pwm)
{
    this->rotate(CW, pwm);
}

void Motor::adjustSpeed(unsigned char pwm)
{

    this->currentPWMValue = pwm;
    analogWrite(HBRIDGE_PWM_PIN, this->currentPWMValue);

    if (this->currentPWMValue < HBRIDGE_MOTOR_SHUTDOWN_THRESHOLD)
    {
        this->stop();
    }
}

void Motor::rotate(MotorState state, unsigned char pwm)
{
    this->state = state;
    this->currentPWMValue = map(pwm, 0, 1023, 0, 255);

    if (this->currentPWMValue < HBRIDGE_MOTOR_SHUTDOWN_THRESHOLD)
        this->state = IDLE;

    switch (this->state)
    {
    case CW:
        digitalWrite(HBRIDGE_ENA_A_PIN, HIGH);
        digitalWrite(HBRIDGE_ENA_B_PIN, LOW);
        analogWrite(HBRIDGE_PWM_PIN, map(this->currentPWMValue, 0, 1023, 0, 255));
        break;
    case CCW:
        digitalWrite(HBRIDGE_ENA_A_PIN, LOW);
        digitalWrite(HBRIDGE_ENA_B_PIN, HIGH);
        analogWrite(HBRIDGE_PWM_PIN, map(this->currentPWMValue, 0, 1023, 0, 255));
        break;
    case IDLE:
        this->stop();
        break;
    }
}

Motor::MotorState Motor::getCurrentState()
{
    return this->state;
}

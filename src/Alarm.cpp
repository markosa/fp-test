#include "Alarm.h"
#include "Configuration.h"
#include <Arduino.h>

Alarm::Alarm()
{
    this->active = false;
    this->alarmOnce = false;
}

void Alarm::start()
{
    this->active = true;
    this->alarmOnce = false;
}
void Alarm::stop()
{
    this->active = false;
    this->alarmOnce = false;
}
void Alarm::once()
{
    this->alarmOnce = true;
    this->active = true;
}
void Alarm::handle()
{

    tone(ALARM_BUZZER_PIN, ALARM_BUZZER_TONE);

    if (alarmOnce)
    {
        this->alarmOnce = false;
        this->active = true;
    }
}

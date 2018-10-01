#include "Configuration.h"
#include <Arduino.h>

#ifndef ALARM_H_
#define ALARM_H_

class Alarm
{

  public:
    Alarm();

    void start();
    void stop();
    void once();
    void handle();

  private:
    bool active;
    bool alarmOnce;
};

#endif
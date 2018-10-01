
#include "Configuration.h"
#include "Settings.h"
#include <Arduino.h>
#include "ProgramState.h"

#ifndef PROGRAMHANDLER_H_
#define PROGRAMHANDLER_H_

class ProgramHandler
{

  public:
    ProgramHandler();
    void startProgram();
    void handleRunningProgram();
    void stopProgram();

  private:
    ProgramState state;
    unsigned long lastTransition;
};

#endif

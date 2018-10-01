#include "ProgramHandler.h"
#include "ProgramState.h"
#include <Arduino.h>

ProgramHandler::ProgramHandler()
{
    this->state = ProgramState::UNINITIALIZED;
}

void ProgramHandler::startProgram()
{
    this->state = ProgramState::DEV_RUNNING;
}

void ProgramHandler::stopProgram()
{
    this->state = ProgramState::DONE;
}

void ProgramHandler::handleRunningProgram()
{
}
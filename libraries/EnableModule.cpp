
#include "Arduino.h"
#include "EnableModule.h"

EnableModule::EnableModule()
{
    programTimer = 0;
    programRunDuration = 10 * 60000L; // 1 minute
    programIsRunning = false; // Not running
}

void EnableModule::reset()
{
    programTimer = 0;
    programRunDuration = 10 * 60000L; // 1 minute
    programIsRunning = false; // Not running
}

uint32_t EnableModule::addDuration(uint32_t minutes)
{
    programRunDuration += minutes * 60000L;
}

void EnableModule::toggleStart()
{
	if (programTimer == 0) programTimer = millis();
	programIsRunning = !programIsRunning;
}

bool EnableModule::isEnabled()
{
	return (!programIsRunning || isTimeUp()) ? false : true;
}

bool EnableModule::isTimeUp()
{
	return (millis() - programTimer > programRunDuration) ? true : false;
}



#include "Arduino.h"
#include "EnableModule.h"

EnableModule::EnableModule()
{
    _startTime = 0;
    _runDuration = 10 * 60000L; // 10 minute
    _isRunning = false; // Not running
}

void EnableModule::reset()
{
    _startTime = 0;
    _runDuration = 10 * 60000L; // 10 minute
    _isRunning = false; // Not running
}

int EnableModule::getDuration()
{
    return _runDuration / 60000L;
}

void EnableModule::setDuration(int minutes)
{
    _runDuration = 60000L * minutes;
}

bool EnableModule::isExpired()
{
	return (millis() - _startTime > _runDuration) ? true : false;
}

void EnableModule::start()
{
	if (_startTime == 0) _startTime = millis();
	_isRunning = true;
}

void EnableModule::stop()
{
    _isRunning = false;
}

bool EnableModule::isRunning()
{
    return _isRunning;
}

bool EnableModule::test()
{
	return (!isRunning() || isExpired()) ? false : true;
}



#include "Arduino.h"
#include "Timer.h"

Timer::Timer(unsigned long millisecond)
{
	_duration = millisecond;
	_startTime = 0;
}

/**
 * Start/Restart the timer.
 */
void Timer::start()
{
	_startTime = millis();
}

/**
 * Check whether the timer has been started.
 * 
 * @return true if timer has been started, otherwise false.
 */
bool Timer::hasStarted()
{
	return _startTime != 0;
}

/**
 * Checks whether the timer has expired.
 * 
 * @returns true if the time is up. Otherwise, false.
 */
bool Timer::isExpired()
{
	unsigned long currentTime = millis();
	unsigned long timeElapsed = currentTime - _startTime;
	
	return (timeElapsed > _duration) ? true : false;
}

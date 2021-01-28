
#include "Arduino.h"
#include "Timer.h"

Timer::Timer()
{
	_duration = 0;
	_startTime = 0;
}

Timer::Timer(unsigned long millis) 
{
	_duration = millis;
}

unsigned long Timer::getDuration()
{
    return _duration;
}

void Timer::setDuration(unsigned long millis)
{
    _duration = millis;
}

// Start/Restart the timer
void Timer::start()
{
	_startTime = millis();
}

// Returns elapsed time since start
unsigned long Timer::split()
{
	return millis() - _startTime;
}

// When elapsed time exceeds timer duration
bool Timer::isExpired()
{
	return (split() > _duration) ? true : false;
}


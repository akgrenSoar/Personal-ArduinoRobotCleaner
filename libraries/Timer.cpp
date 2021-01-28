
#include "Arduino.h"
#include "Timer.h"

///////////////Constructor///////////////

Timer::Timer()
{
	_duration = 0;
	_startTime = 0;
}

Timer::Timer(unsigned long millis) 
{
	_duration = millis;
}

///////////////Getter and Setter///////////////

unsigned long Timer::getDuration()
{
    return _duration;
}

void Timer::setDuration(unsigned long millis)
{
    _duration = millis;
}

///////////////Methods///////////////

// Reset timer
void Timer::reset()
{
	_startTime = 0;
}

// Start timer
void Timer::start()
{
	if (_startTime == 0 || isExpired()) _startTime = millis();
}

// Restart timer
void Timer::restart()
{
	reset();
	start();
}

// Returns elapsed time since start
unsigned long Timer::timeElapsed()
{
	return millis() - _startTime;
}

// When elapsed time exceeds timer duration
bool Timer::isExpired()
{
	return (timeElapsed() > _duration) ? true : false;
}


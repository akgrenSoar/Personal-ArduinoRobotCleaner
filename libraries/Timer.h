
#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer
{
	public:
		Timer(unsigned long millisecond);
		void start();
		bool hasStarted();
		bool isExpired();
		
    private:
        unsigned long _duration;
		unsigned long _startTime;
};

#endif
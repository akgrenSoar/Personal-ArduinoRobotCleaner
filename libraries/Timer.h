
#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer
{
	public:
		Timer(void);
		Timer(unsigned long millis);
		
        unsigned long getDuration();
        void setDuration(unsigned long millis);
		
		void start();
		unsigned long split();
		
		bool isExpired();
		
    private:
        unsigned long _duration; // Robot stops running after ( x minutes * 60000L )
		unsigned long _startTime; // The time that robot started running ( programTimer = millis() )
};

#endif
#ifndef EnableModule_h
#define EnableModule_h

#include "Arduino.h"

class EnableModule
{
	public:
		EnableModule(void);
		void reset();
        
        int getDuration();
        void setDuration(int minutes);
        bool isExpired();
        
        void start();
        void stop();
        bool isRunning();
        
        bool test();
		
    private:
        uint32_t _startTime; // The time that robot started running ( programTimer = millis() )
        uint32_t _runDuration; // Robot stops running after ( x minutes * 60000L )
        bool _isRunning; // If true, robot is running. If false, robot is not running.
};

#endif
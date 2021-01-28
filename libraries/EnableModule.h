#ifndef EnableModule_h
#define EnableModule_h

#include "Arduino.h"

class EnableModule
{
	public:
		EnableModule(void);
		uint32_t addDuration(uint32_t minutes);
		void toggleStart();
		bool isEnabled();
		void reset();
		
    private:
        uint32_t programTimer; // The time that robot started running ( programTimer = millis() )
        uint32_t programRunDuration; // Robot stops running after ( x minutes * 60000L )
        bool programIsRunning; // If true, robot is running. If false, robot is not running.
        bool isTimeUp();
};

#endif

#ifndef Wheel_h
#define Wheel_h

#include "Arduino.h"

#include "MotorDriver.h"

class Wheel
{
	MotorDriver *_motorDriver;
	
	public:
		Wheel(MotorDriver *motorDriver);
		void setSpeed(uint8_t speed);
        uint8_t getSpeed();
		void setDirection(uint8_t direction);
		uint8_t getDirection();
		void pause();
        bool isPaused();
        void stall(uint32_t duration);
        bool isStalled();
		bool isExpired();
		void run();
		
    private:
		int _leftSpeed;
		int _rightSpeed;
		uint32_t _endTime;
		uint8_t _speed;
		uint8_t _prevDirection;
        bool _refreshSignal;
		bool _isPaused;
		bool _isExpired;
		void setRunParameters(int leftSpeed, int rightSpeed, uint32_t duration);
};

#endif
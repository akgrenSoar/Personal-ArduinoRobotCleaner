
#ifndef Wheel_h
#define Wheel_h

#include "Arduino.h"

#include "MotorDriver.h"

class Wheel
{
	MotorDriver *_motorDriver;
	
	public:
		Wheel(MotorDriver *motorDriver, uint8_t speed);
		bool isExpired();
		void setSpeed(uint8_t speed);
		void setDirectionAndRenew(uint8_t direction);
		uint8_t getDirection();
		void pause();
		void run();
		
    private:
		uint8_t _speed;
		int _leftSpeed;
		int _rightSpeed;
		uint32_t _endTime;
		uint8_t _prevDirection;
		bool _isPaused;
		bool _isExpired;
		void set(int leftSpeed, int rightSpeed, uint16_t duration);
};

#endif
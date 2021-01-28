
#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"

class MotorDriver
{
	
	public:
		MotorDriver(uint8_t pin1A, uint8_t pin1D, uint8_t pin2A, uint8_t pin2D);
		void move(int leftSpeed, int rightSpeed);
	
	private:
		uint8_t _pin1A;
		uint8_t _pin1D;
		uint8_t _pin2A;
		uint8_t _pin2D;
		void leftWheel(uint8_t speed, uint8_t direction);
		void rightWheel(uint8_t speed, uint8_t direction);
	
};

#endif
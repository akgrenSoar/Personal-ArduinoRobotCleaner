
#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"

class MotorDriver
{
	
	public:
		MotorDriver(uint8_t pin1A, uint8_t pin1B, uint8_t pin2A, uint8_t pin2B);
		void move(int leftSpeed, int rightSpeed);
	
	private:
		const uint8_t _pin1A, _pin1B, _pin2A, _pin2B;
		void leftWheel(uint8_t valueA, uint8_t valueB);
		void rightWheel(uint8_t valueA, uint8_t valueB);
	
};

#endif
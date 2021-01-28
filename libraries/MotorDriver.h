#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"
#include "TouchCapacitive.h"

class MotorDriver
{
	TouchCapacitive *_touchCapacitive;
	
	
	public:
		MotorDriver(uint8_t pin1A, uint8_t pin1D, uint8_t pin2A, uint8_t pin2D, TouchCapacitive *touchCapacitive);
		void move(int leftSpeed, int rightSpeed, int duration);
	
	private:
		uint8_t _pin1A;
		uint8_t _pin1D;
		uint8_t _pin2A;
		uint8_t _pin2D;
		void leftWheel(uint8_t speed, uint8_t direction);
		void rightWheel(uint8_t speed, uint8_t direction);
	
};

#endif
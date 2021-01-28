#ifndef MotorDriver_h
#define MotorDriver_h

#include "Arduino.h"

class MotorDriver
{
	
	public:
		MotorDriver(int pin1A, int pin1D, int pin2A, int pin2D);
		void move(int leftSpeed, int rightSpeed);
	
	private:
		void leftWheelForward(int speed);
		void rightWheelForward(int speed);
		void leftWheelReverse(int speed);
		void rightWheelReverse(int speed);
		int _pin1A;
		int _pin1D;
		int _pin2A;
		int _pin2D;
	
};

#endif

#include "Arduino.h"
#include "MotorDriver.h"
#include "TouchCapacitive.h"

MotorDriver::MotorDriver(uint8_t pin1A, uint8_t pin1D, uint8_t pin2A, uint8_t pin2D, TouchCapacitive *touchCapacitive)
:	_touchCapacitive(touchCapacitive)
{
	
	_pin1A = pin1A;
	_pin1D = pin1D;
	_pin2A = pin2A;
	_pin2D = pin2D;
	
	pinMode(_pin1A, OUTPUT);
	pinMode(_pin1D, OUTPUT);
	pinMode(_pin2A, OUTPUT);
	pinMode(_pin2D, OUTPUT);
	
	srand(analogRead(0)); // Initialize random seed
}

void MotorDriver::leftWheel(uint8_t speed, uint8_t direction)
{
	analogWrite(_pin1A, speed);
	digitalWrite(_pin1D, direction);
}

void MotorDriver::rightWheel(uint8_t speed, uint8_t direction)
{
	analogWrite(_pin2A, speed);
	digitalWrite(_pin2D, direction);
}

// Left speed -255 to 255
// Right speed -255 to 255
// Duration is calculated as the range of (500ms to duration+500ms), duration = 0 to disable
void MotorDriver::move(int leftSpeed, int rightSpeed, int duration)
{
	if (leftSpeed >= 0) {
		leftWheel(leftSpeed, LOW);
	} else {
		leftWheel(255 + leftSpeed, HIGH);
	}
	
	if (rightSpeed >= 0) {
		rightWheel(rightSpeed, LOW);
	} else {
		rightWheel(255 + rightSpeed, HIGH);
	}
	
	if (duration > 0) {
		_touchCapacitive->block((rand() & duration) + 500);
		move(0, 0, 0);
	}
}


	

#include "Arduino.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(uint8_t pin1A, uint8_t pin1D, uint8_t pin2A, uint8_t pin2D)
:	_pin1A(pin1A), _pin1D(pin1D), _pin2A(pin2A), _pin2D(pin2D)
{
	pinMode(_pin1A, OUTPUT);
	pinMode(_pin1D, OUTPUT);
	pinMode(_pin2A, OUTPUT);
	pinMode(_pin2D, OUTPUT);
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

// Speed value from -255 to 255
void MotorDriver::move(int leftSpeed, int rightSpeed)
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
}


	

#include "Arduino.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(uint8_t pin1A, uint8_t pin1B, uint8_t pin2A, uint8_t pin2B)
:	_pin1A(pin1A), _pin1B(pin1B), _pin2A(pin2A), _pin2B(pin2B)
{
	pinMode(_pin1A, OUTPUT);
	pinMode(_pin1B, OUTPUT);
	pinMode(_pin2A, OUTPUT);
	pinMode(_pin2B, OUTPUT);
}

void MotorDriver::leftWheel(uint8_t valueA, uint8_t valueB)
{
	analogWrite(_pin2A, valueA);
	analogWrite(_pin2B, valueB);
}

void MotorDriver::rightWheel(uint8_t valueA, uint8_t valueB)
{
	analogWrite(_pin1A, valueA);
	analogWrite(_pin1B, valueB);
}

// Speed value from -255 to 255
void MotorDriver::move(int leftSpeed, int rightSpeed)
{
	if (leftSpeed >= 0) {
		leftWheel(leftSpeed, LOW);
	} else {
		leftWheel(LOW, abs(leftSpeed));
	}
	
	if (rightSpeed >= 0) {
		rightWheel(rightSpeed, LOW);
	} else {
		rightWheel(LOW, abs(rightSpeed));
	}
}


	
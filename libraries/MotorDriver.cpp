

#include "Arduino.h"
#include "MotorDriver.h"


MotorDriver::MotorDriver(int pin1A, int pin1D, int pin2A, int pin2D){
	
	_pin1A = pin1A;
	_pin1D = pin1D;
	_pin2A = pin2A;
	_pin2D = pin2D;
	
	pinMode(_pin1A, OUTPUT);
	pinMode(_pin1D, OUTPUT);
	pinMode(_pin2A, OUTPUT);
	pinMode(_pin2D, OUTPUT);
}

void MotorDriver::leftWheelForward(int speed){
	analogWrite(_pin1A, speed);
	digitalWrite(_pin1D, LOW);
}

// Speed cannot be zero or H-Bridge will fry
void MotorDriver::leftWheelReverse(int speed){
	analogWrite(_pin1A, 255 - speed);
	digitalWrite(_pin1D, HIGH);
}

void MotorDriver::rightWheelForward(int speed){
	analogWrite(_pin2A, speed);
	digitalWrite(_pin2D, LOW);
}

// Speed cannot be zero or H-Bridge will fry
void MotorDriver::rightWheelReverse(int speed){
	analogWrite(_pin2A, 255 - speed);
	digitalWrite(_pin2D, HIGH);
}


void MotorDriver::move(int leftSpeed, int rightSpeed){
	
	if(leftSpeed >= 0){
		leftWheelForward(leftSpeed);
	} else {
		leftSpeed = -leftSpeed;
		leftWheelReverse(leftSpeed);
	}
	
	if(rightSpeed >= 0){
		rightWheelForward(rightSpeed);
	} else {
		rightSpeed = -rightSpeed;
		rightWheelReverse(rightSpeed);
	}
}



	
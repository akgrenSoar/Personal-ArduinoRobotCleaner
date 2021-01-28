
#include "Arduino.h"
#include "Wheel.h"

#include "MotorDriver.h"

Wheel::Wheel(MotorDriver *motorDriver, uint8_t speed)
	:	_motorDriver(motorDriver), _speed(speed)
{
	
	_leftSpeed = 0;
	_rightSpeed = 0;
	_endTime = 0;
	
	_prevDirection = 0;
	_isPaused = true;
	_isExpired = true;
	
	srand(millis());
	Serial.println(rand());
	Serial.println(rand());
	Serial.println(rand());
}

bool Wheel::isExpired()
{
	return _isExpired;
}

void Wheel::setSpeed(uint8_t speed) {
	_speed = speed;
	uint8_t direction = _prevDirection;
	_prevDirection = 0;
	setDirectionAndRenew(direction);
}

void Wheel::set(int leftSpeed, int rightSpeed, uint16_t duration)
{
	_leftSpeed = leftSpeed;
	_rightSpeed = rightSpeed;
	_endTime = millis() + duration;
}

void Wheel::setDirectionAndRenew(uint8_t direction)
{
	int random = rand();
	
	switch (direction) {
		case 1: // Forward
			Serial.println("Forward");
			random %= 3;
			if (random == 0) {
				set(_speed - 30, _speed - 10, 16384);
			} else if (random == 1) {
				set(_speed, _speed - 40, 16384);
			} else {
				set(_speed, _speed - 10, 16384);
			}
			break;
		case 2: // Left
			Serial.println("TurnLeft");
			if (_prevDirection != direction) {
				set(-_speed, 0, ((random & 0x2FF) + 400));
			} else {
				set(-_speed, _speed, ((random & 0x3FF) + 500));
			}
			break;
		case 3: // Right
			Serial.println("TurnRight");
			if (_prevDirection != direction) {
				set(0, -_speed, ((random & 0x2FF) + 400));
			} else {
				set(_speed, -_speed, ((random & 0x3FF) + 500));
			}
			break;
		case 4: // Reverse
			Serial.println("Reverse");
			if (_prevDirection != direction) {
				(rand() & 0x01) ? set(-_speed, 0, ((random & 0x2FF) + 400)) : set(0, -_speed, ((random & 0x2FF) + 400));
			} else {
				(rand() & 0x01) ? set(-_speed, _speed, ((random & 0x3FF) + 500)) : set(_speed, -_speed, ((random & 0x3FF) + 500));
			}
			break;
	}
	
	_isPaused = true;
	_isExpired = false;
	_prevDirection = direction;
}

uint8_t Wheel::getDirection()
{
	return _prevDirection;
}

void Wheel::pause()
{
	// Currently running, pause it.
	if (!_isPaused) {
		_isPaused = true;
		_motorDriver->move(0, 0);
	}
}

void Wheel::run()
{
	// Already expired. Do nothing
	if (_isExpired) {
		return;
	}
	
	// Currently expired. Stop motor and set as expired.
	if (millis() > _endTime) {
		_isExpired = true;
		_motorDriver->move(0, 0);
		return;
	}
	
	// Currently paused, resume running
	if (_isPaused) {
		_isPaused = false;
		_motorDriver->move(_leftSpeed, _rightSpeed);
		return;
	}
}
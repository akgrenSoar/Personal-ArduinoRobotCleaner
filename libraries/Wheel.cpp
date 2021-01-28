
#include "Arduino.h"
#include "Wheel.h"

#include "MotorDriver.h"

Wheel::Wheel(MotorDriver *motorDriver)
	:	_motorDriver(motorDriver)
{
    // Run parameters
	_leftSpeed = 0;
	_rightSpeed = 0;
	_endTime = 0;
	
    // Logic/Control parameters
    _speed = 255;
	_prevDirection = 0;
    _refreshSignal = false;
	_isPaused = true;
	_isExpired = true;
	
    // Initialize random
	srand(millis());
    Serial.println("Initilializing srand() in Wheel class");
	Serial.println(rand());
	Serial.println(rand());
	Serial.println(rand());
}

void Wheel::setSpeed(uint8_t speed) {
    _leftSpeed -= _speed - speed;
    _rightSpeed -= _speed - speed;
	_speed = speed;
    _refreshSignal = true;
}

uint8_t Wheel::getSpeed()
{
    return _speed;
}

void Wheel::setDirection(uint8_t direction)
{
	int random = rand();
	
	switch (direction) {
		case 1: // Forward
			random %= 3;
			if (random == 0) {
				setRunParameters(_speed - 30, _speed - 10, 16384);
			} else if (random == 1) {
				setRunParameters(_speed, _speed - 40, 16384);
			} else {
				setRunParameters(_speed, _speed - 10, 16384);
			}
			break;
		case 2: // Left
			if (_prevDirection != direction) {
				setRunParameters(-_speed, 50, ((random & 0x2FF) + 400));
			} else {
				setRunParameters(-_speed, _speed, ((random & 0x3FF) + 500));
			}
			break;
		case 3: // Right
			if (_prevDirection != direction) {
				setRunParameters(50, -_speed, ((random & 0x2FF) + 400));
			} else {
				setRunParameters(_speed, -_speed, ((random & 0x3FF) + 500));
			}
			break;
		case 4: // Reverse
			if (_prevDirection != direction) {
				(rand() & 0x01) ? setRunParameters(-_speed, 50, ((random & 0x2FF) + 400)) : setRunParameters(50, -_speed, ((random & 0x2FF) + 400));
			} else {
				(rand() & 0x01) ? setRunParameters(-_speed, _speed, ((random & 0x3FF) + 500)) : setRunParameters(_speed, -_speed, ((random & 0x3FF) + 500));
			}
			break;
	}
	
    _refreshSignal = true; // To refresh signal
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
		_prevDirection = 0;
		_motorDriver->move(0, 0);
        return;
	}
}

bool Wheel::isPaused()
{
    return _isPaused;
}

void Wheel::stall(uint32_t duration)
{
    _refreshSignal = true; // To refresh signal
	_isExpired = false;
    setRunParameters(0, 0, duration);
}

bool Wheel::isStalled()
{
    return (_leftSpeed == 0 && _rightSpeed == 0) ? true : false;
}

bool Wheel::isExpired()
{
	return _isExpired;
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
    
    // Direction changed, update signal
    if (_refreshSignal) {
        _refreshSignal = false;
		_motorDriver->move(_leftSpeed, _rightSpeed);
    }
    
    // Already running, do nothing
}

void Wheel::setRunParameters(int leftSpeed, int rightSpeed, uint32_t duration)
{
	_leftSpeed = leftSpeed;
	_rightSpeed = rightSpeed;
	_endTime = millis() + duration;
}



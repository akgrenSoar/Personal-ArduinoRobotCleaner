
#include "MovementModule.h"

#include "Arduino.h"
#include "MotorDriver.h"
#include "Timer.h"

MovementModule::MovementModule(MotorDriver *motorDriver)
:	_motorDriver (motorDriver),
	_timer ()
{
	_speed = 255;
	_direction = 0;
	_moveCode = 0;
}

uint8_t MovementModule::getSpeed()
{
	return _speed;
}

void MovementModule::setSpeed(uint8_t speed)
{
	_speed = speed;
}

bool MovementModule::isExpired()
{
	return _timer.isExpired();
}

void MovementModule::refresh()
{
	move(_moveCode);
}

void MovementModule::pause(unsigned long duration)
{
	move(0, 0, duration);
}

uint8_t MovementModule::getDirection()
{
	return _direction;
}

void MovementModule::setDirection(uint8_t direction)
{
	switch (direction) {
		case 0: // Stop
			if (_direction != 0) move(0);
			break;
		case 1: // Forward
			if (_direction != 1) {
				int array[] = {10, 12, 13};
				move(roll(3, array));
			} else {
				int array[] = {15, 22, 23, 25, 32, 33, 35, 45};
				move(roll(8, array));
			}
			break;
		case 2: // Left
			if (_direction != 2) {
				move(20);
			} else {
				int array[] = {22, 23, 25, 42};
				move(roll(4, array));
			}
			break;
		case 3: // Right
			if (_direction != 3) {
				move(30);
			} else {
				int array[] = {32, 33, 35, 43};
				move(roll(4, array));
			}
			break;
		case 4: // Reverse
			if (_direction != 4) {
				int array[] = {20, 30, 40};
				move(roll(3, array));
			} else {
				int array[] = {15, 22, 23, 25, 32, 33, 35, 45};
				move(roll(8, array));
			}
			break;
		case 5: // No change
		default:
			break;
	}
	
	if (direction != 5) {
		_direction = direction;
	}
}

// Randomly picks one value from the array
int MovementModule::roll(int arraySize, int *array)
{
	return array[random(arraySize)];
}

void MovementModule::move(uint8_t moveCode)
{
	_moveCode = moveCode;
	
	switch (moveCode) {
		// Stop
		case 00:
			move(0, 0, 0);
			break;
		// Forward
		case 10:
			move(_speed, _speed, 8000);
			break;
		case 12:
			move(_speed - 30, _speed, 8000);
			break;
		case 13:
			move(_speed, _speed - 30, 8000);
			break;
		case 15:
			move(255, 255,  random(2047) + 2000); // 2047 + 2000
			break;
		// Left
		case 20:
			move(-_speed, _speed, random(511) + 400); // 511 + 400
			break;
		case 22:
			move(-255, 0, random(2047) + 400); // 2047 + 400
			break;
		case 23:
			move(0, 255, random(2047) + 400);
			break;
		case 25:
			move(-255, 255, random(2047) + 400);
			break;
		// Right
		case 30:
			move(_speed, -_speed, random(511) + 384); // 511 + 400
			break;
		case 32:
			move(255, 0, random(2047) + 400); // 2047 + 400
			break;
		case 33:
			move(0, -255, random(2047) + 400);
			break;
		case 35:
			move(255, -255, random(2047) + 400);
			break;
		// Reverse
		case 40:
			move(-_speed, -_speed, random(2047) + 1000); // 2047 + 1000
			break;
		case 42:
			move(-_speed, -_speed + 30, random(1500) + 500);
			break;
		case 43:
			move(-_speed + 30, -_speed, random(1500) + 500);
			break;
		case 45:
			move(-255, -255, random(2047) + 1000);
			break;
		// ERROR, debug
		default:
			move(-200, -200, 100000);
			break;
	}
}

void MovementModule::move(int leftSpeed, int rightSpeed, unsigned long duration)
{
	_motorDriver->move(leftSpeed, rightSpeed);
	_timer.setDuration(duration);
	_timer.start();
}








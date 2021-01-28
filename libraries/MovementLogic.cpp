
#include "MovementLogic.h"

#include "Arduino.h"
#include "MotorDriver.h"
#include "PauseThenMove.h"

/////////////////////////////////////////
///////////////Constructor///////////////
/////////////////////////////////////////

MovementLogic::MovementLogic(MotorDriver *motorDriver, unsigned long pauseDuration, uint8_t speed) :
	_motorDriver (motorDriver),
	_pauseThenMove (0, 0, 0, 0)
{
	_pauseDuration = pauseDuration;
	_speed = speed;
	_currentDirection = 0;
}

///////////////////////////////////////////////
///////////////Getter and Setter///////////////
///////////////////////////////////////////////

uint8_t MovementLogic::getSpeed()
{
	return _speed;
}

void MovementLogic::setSpeed(uint8_t speed)
{
	_speed = speed;
}

unsigned long MovementLogic::getPauseDuration()
{
	return _pauseDuration;
}

void MovementLogic::setPauseDuration(unsigned long pauseDuration)
{
	_pauseDuration = pauseDuration;
}

///////////////////////////////////////////////
////////////////////Movement///////////////////
///////////////////////////////////////////////

void MovementLogic::stop()
{
	_currentDirection = 0;
	_pauseThenMove = PauseThenMove(0, 0, 0, 0);
	_pauseThenMove.update(_motorDriver);
	return;
}

void MovementLogic::forward()
{
	// All movements have precedence over forward movement
	if (!_pauseThenMove.isExpired()) {
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Start a new PauseThenMoveForward movement
	if (_currentDirection != 1) {
		_currentDirection = 1;
		// Random movement of 3 possibilities
		int array[] = {10, 12, 13};
		move(roll(3, array));
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// PauseThenMoveForward movement is stuck!
	// Perform break free manoeuvre
	// Random movement of 8 possibilities
	int array[] = {15, 22, 23, 25, 32, 33, 35, 45};
	move(roll(8, array));
	_pauseThenMove.update(_motorDriver);
	return;
}

void MovementLogic::left()
{
	// Overwrite if current movement is PauseThenMoveForward movement
	if (_currentDirection == 1) {
		_currentDirection = 2;
		move(20); // Turn left
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Respect all other movements, wait for them to end
	if (!_pauseThenMove.isExpired()) {
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Currently not a PauseThenTurnLeft movement
	// Start a new PauseThenTurnLeft movement
	if (_currentDirection != 2) {
		_currentDirection = 2;
		move(20); // Turn left
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// PauseThenTurnLeft movement is stuck!
	// Perform break free manoeuvre
	// Random movement of 4 possibilities
	int array[] = {22, 23, 25, 42};
	move(roll(4, array));
	_pauseThenMove.update(_motorDriver);
	return;
}

void MovementLogic::right()
{
	// Overwrite if current movement is PauseThenMoveForward movement
	if (_currentDirection == 1) {
		_currentDirection = 3;
		move(30); // Turn right
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Respect all other movements, wait for them to end
	if (!_pauseThenMove.isExpired()) {
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Currently not a PauseThenTurnRight movement
	// Start a new PauseThenTurnRight movement
	if (_currentDirection != 3) {
		_currentDirection = 3;
		move(30); // Turn right
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// PauseThenTurnRight movement is stuck!
	// Perform break free manoeuvre
	// Random movement of 4 possibilities
	int array[] = {32, 33, 35, 43};
	move(roll(4, array));
	_pauseThenMove.update(_motorDriver);
	return;
}

void MovementLogic::reverse()
{
	// Overwrite if current movement is PauseThenMoveForward movement
	if (_currentDirection == 1) {
		_currentDirection = 4;
		// Random movement of 3 possibilities
		int array[] = {20, 30, 40};
		move(roll(3, array));
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Respect all other movements, wait for them to end
	if (!_pauseThenMove.isExpired()) {
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// Currently not a PauseThenReverse movement
	// Start a new PauseThenReverse movement
	if (_currentDirection != 4) {
		_currentDirection = 4;
		// Random movement of 3 possibilities
		int array[] = {20, 30, 40};
		move(roll(3, array));
		_pauseThenMove.update(_motorDriver);
		return;
	}
	
	// PauseThenReverse movement is stuck!
	// Perform break free manoeuvre
	// Random movement of 8 possibilities
	int array[] = {15, 22, 23, 25, 32, 33, 35, 45};
	move(roll(8, array));
	_pauseThenMove.update(_motorDriver);
	return;
}

/////////////////////////////////////
////////////////Helper///////////////
/////////////////////////////////////

void MovementLogic::move(uint8_t moveCode)
{	
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
			move(255, 255,  random(2047) + 100); // 2047 + 2000
			break;
		// Left
		case 20:
			move(-_speed, _speed, random(411) + 100); // 511 + 400
			break;
		case 22:
			move(-255, 0, random(1023) + 100); // 2047 + 400
			break;
		case 23:
			move(0, 255, random(1023) + 100);
			break;
		case 25:
			move(-255, 255, random(1023) + 100);
			break;
		// Right
		case 30:
			move(_speed, -_speed, random(411) + 100); // 511 + 400
			break;
		case 32:
			move(255, 0, random(1023) + 100); // 2047 + 400
			break;
		case 33:
			move(0, -255, random(1023) + 100);
			break;
		case 35:
			move(255, -255, random(1023) + 100);
			break;
		// Reverse
		case 40:
			move(-_speed, -_speed, random(1023) + 100); // 2047 + 1000
			break;
		case 42:
			move(-_speed, -_speed + 30, random(1023) + 100);
			break;
		case 43:
			move(-_speed + 30, -_speed, random(1023) + 100);
			break;
		case 45:
			move(-255, -255, random(2047) + 100);
			break;
		// ERROR, debug
		default:
			move(-200, -200, 100000);
			break;
	}
}

void MovementLogic::move(int leftSpeed, int rightSpeed, unsigned long moveDuration)
{
	_pauseThenMove = PauseThenMove(
		_pauseDuration,
		moveDuration,
		leftSpeed,
		rightSpeed);
}

// Randomly picks one value from the array
int MovementLogic::roll(int arraySize, int *array)
{
	return array[random(arraySize)];
}

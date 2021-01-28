
#include "PauseThenMove.h"

#include "Arduino.h"
#include "MotorDriver.h"
#include "Timer.h"


PauseThenMove::PauseThenMove(
	unsigned long pauseDuration,
	unsigned long moveDuration,
	int leftSpeed, 
	int rightSpeed)
	
:	_pauseTimer (pauseDuration),
	_moveTimer (moveDuration)
{
	_leftSpeed = leftSpeed;
	_rightSpeed = rightSpeed;
}

/**
 * Checks whether this PauseThenMove movement has expired.
 * 
 * @return true if this PauseThenMove movement has expired, otherwise false.
 */
bool PauseThenMove::isExpired()
{
	return _pauseTimer.hasStarted()
			&& _pauseTimer.isExpired()
			&& _moveTimer.hasStarted()
			&& _moveTimer.isExpired();
}

/**
 * Updates the motorDriver based on this PauseThenMove movement.
 */
void PauseThenMove::update(MotorDriver *motorDriver)
{
	if (!_pauseTimer.hasStarted()) {
		motorDriver->move(0, 0);
		_pauseTimer.start();
	}
	
	if (!_pauseTimer.isExpired()) {
		return;
	}
	
	if (!_moveTimer.hasStarted()) {
		motorDriver->move(_leftSpeed, _rightSpeed);
		_moveTimer.start();
	}
	
	if (!_moveTimer.isExpired()) {
		return;
	}
}

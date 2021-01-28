
#ifndef PauseThenMove_h
#define PauseThenMove_h

#include "Arduino.h"
#include "MotorDriver.h"
#include "Timer.h"

class PauseThenMove
{
	public:
		PauseThenMove(
			unsigned long pauseDuration,
			unsigned long moveDuration,
			int leftSpeed, 
			int rightSpeed
		);
		
		bool isExpired();
		void update(MotorDriver *motorDriver);
	
	private:
		Timer _pauseTimer;
		Timer _moveTimer;
		int _leftSpeed;
		int _rightSpeed;
};

#endif

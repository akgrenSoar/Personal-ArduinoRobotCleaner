
#ifndef MovementLogic_h
#define MovementLogic_h

#include "Arduino.h"
#include "MotorDriver.h"
#include "PauseThenMove.h"

class MovementLogic
{
	public:
		MovementLogic(
				MotorDriver *motorDriver,
				unsigned long pauseDuration,
				uint8_t speed = 255
		);
		
		uint8_t getSpeed();
		void setSpeed(uint8_t speed);
		unsigned long getPauseDuration();
		void setPauseDuration(unsigned long pauseDuration);

		void stop();
		void forward();
		void left();
		void right();
		void reverse();
		
    private:
		MotorDriver *_motorDriver;
		PauseThenMove _pauseThenMove;
		uint8_t _speed;
		unsigned long _pauseDuration;
		uint8_t _currentDirection;
		
		int roll(int arraySize, int *array);
		void move(uint8_t moveCode);
		void move(int leftSpeed, int rightSpeed, unsigned long moveDuration);
};

#endif

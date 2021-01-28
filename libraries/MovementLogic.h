
#ifndef MovementLogic_h
#define MovementLogic_h

#include "Arduino.h"
#include "MotorDriver.h"
#include "Timer.h"

class MovementLogic
{
	public:
		MovementLogic(MotorDriver *motorDriver, uint8_t speed = 255);
		
		uint8_t getSpeed();
		void setSpeed(uint8_t speed);
		uint8_t getDirection();
		void setDirection(uint8_t direction); // Move in the specified direction
		
		bool isExpired();
		void refresh(); // Refreshes speed and duration
		void pause(unsigned long duration);
		
    private:
		MotorDriver *_motorDriver;
		Timer _timer;
		uint8_t _speed;
		uint8_t _direction;
		uint8_t _moveCode;
		
		int roll(int arraySize, int *array);
		void move(uint8_t moveCode);
		void move(int leftSpeed, int rightSpeed, unsigned long duration);
};

#endif
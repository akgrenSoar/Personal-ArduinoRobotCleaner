
#ifndef DirectionModule_h
#define DirectionModule_h

#include "Arduino.h"
#include "MotorDriver.h"
#include "LightSensor.h"
#include "UltrasonicSensor.h"

class DirectionModule
{
	MotorDriver _motorDriver;
	LightSensor _frontLightSensor;
	UltrasonicSensor _leftUltrasonicSensor;
	UltrasonicSensor _rightUltrasonicSensor;
	
	public:
	    DirectionModule(MotorDriver motorDriver, LightSensor frontSensor, UltrasonicSensor leftSensor, UltrasonicSensor rightSensor);
		void run(int speed);
		void stop();
		
    private:
		uint8_t _previousDirection;
		uint8_t _currentDirection;
		int readUltrasonic();
		int confirmUltrasonic();
		int determineMoveDirection();
};

#endif
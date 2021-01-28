
#ifndef DirectionModule_h
#define DirectionModule_h

#include "Arduino.h"
#include "MotorDriver.h"
#include "LightSensor.h"
#include "UltrasonicSensor.h"
#include "TouchCapacitive.h"

class DirectionModule
{
	MotorDriver *_motorDriver;
	LightSensor *_frontLightSensor;
	UltrasonicSensor *_leftUltrasonicSensor;
	UltrasonicSensor *_rightUltrasonicSensor;
	TouchCapacitive *_touchCapacitive;
	
	public:
	    DirectionModule(MotorDriver *motorDriver, LightSensor *frontSensor, UltrasonicSensor *leftSensor, UltrasonicSensor *rightSensor, TouchCapacitive *touchCapacitive);
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
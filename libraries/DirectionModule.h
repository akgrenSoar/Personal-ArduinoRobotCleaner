
#ifndef DirectionModule_h
#define DirectionModule_h

#include "Arduino.h"

#include "LightSensor.h"
#include "UltrasonicSensor.h"

class DirectionModule
{
	LightSensor *_frontLightSensor;
	UltrasonicSensor *_leftUltrasonicSensor;
	UltrasonicSensor *_rightUltrasonicSensor;
	
	public:
	    DirectionModule(LightSensor *frontSensor, UltrasonicSensor *leftSensor, UltrasonicSensor *rightSensor);
		int getDirection();
		
    private:
		uint8_t _previousDirection;
		uint8_t _currentDirection;
		int readUltrasonic();
		int readUltrasonicAndDoubleConfirm();
};

#endif
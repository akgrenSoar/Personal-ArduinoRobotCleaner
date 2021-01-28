
#ifndef DirectionLogic_h
#define DirectionLogic_h

#include "Arduino.h"

#include "SonicSensor.h"

class DirectionLogic
{
	SonicSensor *_frontSensor;
	SonicSensor *_leftSensor;
	SonicSensor *_rightSensor;
	
	public:
	    DirectionLogic(SonicSensor *frontSensor, SonicSensor *leftSensor, SonicSensor *rightSensor);
		int getDirection();
		
    private:
		unsigned long _frontThreshold;
		unsigned long _leftThreshold;
		unsigned long _rightThreshold;
		int readSensor();
		int readAndConfirmSensor();
};

#endif
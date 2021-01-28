
#ifndef DirectionTeller_h
#define DirectionTeller_h

#include "Arduino.h"

#include "LightSensor.h"
#include "SonicSensor.h"

class DirectionTeller
{
	LightSensor *_frontLightSensor;
	SonicSensor *_leftUltrasonicSensor;
	SonicSensor *_rightUltrasonicSensor;
	
	public:
	    DirectionTeller(LightSensor *frontSensor, SonicSensor *leftSensor, SonicSensor *rightSensor);
		int getDirection();
		
    private:
		int readUltrasonic();
		int readUltrasonicAndDoubleConfirm();
};

#endif
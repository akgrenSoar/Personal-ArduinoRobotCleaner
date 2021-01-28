
#ifndef SonicSensor_h
#define SonicSensor_h

#include "Arduino.h"

class SonicSensor {

    public:
        SonicSensor(uint8_t trigPin, uint8_t echoPin);
        unsigned long getDistance();
		
	private:
		const uint8_t _trigPin;
		const uint8_t _echoPin;

};

#endif
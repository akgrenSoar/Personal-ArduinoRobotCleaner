
#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include "Arduino.h"

class UltrasonicSensor {

    public:
        UltrasonicSensor(uint8_t trigPin, uint8_t echoPin);
        int getDistance();

    private:
        uint8_t _trigPin;
        uint8_t _echoPin;
  
};

#endif
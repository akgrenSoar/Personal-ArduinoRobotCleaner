
#include "Arduino.h"
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t pinIn)
:    _pinIn(pinIn)
{
    pinMode(_pinIn, INPUT);
}

bool LightSensor::isObstacleDetected()
{
    return digitalRead(_pinIn) == LOW ? true : false ;
}

#include "Arduino.h"
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t pinIn)
:    _pinIn(pinIn)
{
    pinMode(_pinIn, INPUT);
}

bool LightSensor::isTriggered()
{
    return digitalRead(_pinIn) == LOW ? true : false ;
}
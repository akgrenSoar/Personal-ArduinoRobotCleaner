
#include "Arduino.h"
#include "LightSensor.h"

LightSensor::LightSensor(uint8_t pinIn)
:    _pinIn(pinIn)
{
    pinMode(_pinIn, INPUT);
}

/**
 * Reads the state of the light sensor
 * 
 * @return true if obstacle is detected, otherwise false.
 */
bool LightSensor::isTriggered()
{
    return digitalRead(_pinIn) == LOW ? true : false ;
}
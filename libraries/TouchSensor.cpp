
#include "Arduino.h"
#include "TouchSensor.h"

TouchSensor::TouchSensor(uint8_t pinIn)
:	_pinIn(pinIn)
{	
    pinMode(_pinIn, INPUT);
}

/**
 * Check the current button state
 * 
 * @returns true if button is pressed, otherwise false.
 */
bool TouchSensor::isPressed()
{
	return (digitalRead(_pinIn) == HIGH) ? true : false;
}


#include "Arduino.h"
#include "TouchSensor.h"

TouchSensor::TouchSensor(uint8_t pinIn)
:	_pinIn(pinIn)
{	
    pinMode(_pinIn, INPUT);
	prevState = false;
}

/**
 * Check the current button state
 * 
 * Returns true if isPressed, false if notPressed
 */
bool TouchSensor::getState()
{
	return (digitalRead(_pinIn) == HIGH) ? true : false;
}

/**
 * Check for change in button state from notPressed to isPressed
 *
 * Returns true if there is a state change from notPressed to isPressed
 * Otherwise, returns false.
 */
bool TouchSensor::isPressed()
{
	bool isPressed = getState();
	bool wasPressed = prevState;
	prevState = isPressed;
	
	return (!wasPressed && isPressed) ? true : false;
}

/**
 * Check for change in button state from isPressed to notPressed
 *
 * Returns true if there is a state change from isPressed to notPressed
 * Otherwise, returns false.
 */
bool TouchSensor::isReleased()
{
	bool isPressed = getState();
	bool wasPressed = prevState;
	prevState = isPressed;
	
	return (wasPressed && !isPressed) ? true : false;
}









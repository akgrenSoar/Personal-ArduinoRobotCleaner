
#include "Arduino.h"
#include "TouchSensor.h"

TouchSensor::TouchSensor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
:	_pins{pin1, pin2, pin3, pin4}
{	
    pinMode(_pins[0], INPUT);
    pinMode(_pins[1], INPUT);
    pinMode(_pins[2], INPUT);
    pinMode(_pins[3], INPUT);
}

uint8_t TouchSensor::getButtonReleased()
{
	uint8_t memory = 0;
	uint8_t result = getButtonPressed();
	
	while (result != 0) {
		memory = result;
		result = getButtonPressed();
	}
	
	return memory;
}

uint8_t TouchSensor::getButtonPressed()
{
	// Check buttons 1 to 4
	for (uint8_t i = 1; i < 5; i++) {
		if (isButtonPressed(i)) {
			return i;
		}
	}
	
	// No buttons pressed
	return 0;
}

bool TouchSensor::isButtonPressed(uint8_t buttonNumber)
{
	return (digitalRead(_pins[buttonNumber - 1]) == HIGH) ? true : false;
}









#include "Arduino.h"
#include "TouchCapacitive.h"


TouchCapacitive::TouchCapacitive(int pin1, int pin2, int pin3, int pin4)
{
	_delayTime = 300;
	
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;
	
    pinMode(_pins[0], INPUT);
    pinMode(_pins[1], INPUT);
    pinMode(_pins[2], INPUT);
    pinMode(_pins[3], INPUT);
}

bool TouchCapacitive::isButtonPressed(uint8_t buttonNumber)
{
	return digitalRead(_pins[buttonNumber - 1]) == HIGH ? true : false;
}

uint8_t TouchCapacitive::getButtonPressed()
{
	// Check buttons 1 to 4
	for (int i = 1; i < 5; i++) {
		if (isButtonPressed(i)) {
			pauseWhilePressed(i);
			return i;
		}
	}
	
	// No buttons pressed
	return 0;
}

// To prevent multiple triggers on a single press
void TouchCapacitive::pauseWhilePressed(uint8_t buttonNumber) {
    while (isButtonPressed(buttonNumber)) {
		delay(_delayTime);
	}
}






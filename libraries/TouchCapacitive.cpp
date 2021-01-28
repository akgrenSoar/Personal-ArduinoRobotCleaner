
#include "Arduino.h"
#include "TouchCapacitive.h"

TouchCapacitive::TouchCapacitive(int pin1, int pin2, int pin3, int pin4)
{	
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;
	
    pinMode(_pins[0], INPUT);
    pinMode(_pins[1], INPUT);
    pinMode(_pins[2], INPUT);
    pinMode(_pins[3], INPUT);
	
	_isBufferUsed = false;
	_bufferValue = 0;
}

void TouchCapacitive::block(int duration)
{
	uint32_t endTime = millis() + duration;
	uint8_t buttonPressed;
	while (endTime > millis()) {
		// Check buttons 1 to 4
		for (int i = 1; i < 5; i++) {
			if (isButtonPressed(i)) {
				_isBufferUsed = true;
				_bufferValue = i;
			}
		}
		delay(100);
	}
}

uint8_t TouchCapacitive::getButtonPressed()
{
	// Check buttons 1 to 4
	for (int i = 1; i < 5; i++) {
		if (isButtonPressed(i)) {
			_isBufferUsed = false;
			return i;
		}
	}
	
	// Check buffer
	if (_isBufferUsed) {
		_isBufferUsed = false;
		return _bufferValue;
	}
	
	// No buttons pressed
	return 0;
}

bool TouchCapacitive::isButtonPressed(uint8_t buttonNumber)
{
	return (digitalRead(_pins[buttonNumber - 1]) == HIGH) ? true : false;
}







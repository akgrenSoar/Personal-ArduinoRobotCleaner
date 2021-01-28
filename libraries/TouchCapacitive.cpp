

#include "Arduino.h"
#include "TouchCapacitive.h"


TouchCapacitive::TouchCapacitive(int pin1, int pin2, int pin3, int pin4)
{
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;
	
	for(int i = 0; i < 4; i ++){
		pinMode(_pins[i], INPUT);
	}
}

bool TouchCapacitive::isPressed (int button)
{
	return digitalRead(_pins[button - 1]) == HIGH ? true : false;
}


#include "Arduino.h"
#include "DirectionLogic.h"

#include "SonicSensor.h"

DirectionLogic::DirectionLogic(SonicSensor *frontSensor, SonicSensor *leftSensor, SonicSensor *rightSensor)
	:	_frontSensor(frontSensor),
		_leftSensor(leftSensor),
		_rightSensor(rightSensor)
{
	_frontThreshold = 5;
	_leftThreshold = 17;
	_rightThreshold = 17;
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionLogic::getDirection()
{
	return readAndConfirmSensor();
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionLogic::readSensor()
{
	//unsigned long frontDistance = _frontSensor->getDistance();
	unsigned long leftDistance = _leftSensor->getDistance();
	unsigned long rightDistance = _rightSensor->getDistance();
	
	//if (frontDistance <= _frontThreshold) {
	//	return 4; // Reverse
	//}
	
    if (leftDistance > _leftThreshold && rightDistance > _rightThreshold) {
        return 1; // Move forward
    } else if (leftDistance <= _leftThreshold && rightDistance <= _rightThreshold) {
        return 4; // Reverse
    } else if (leftDistance > _leftThreshold && rightDistance <= _rightThreshold) {
        return 2; // Turn left
    } else if (leftDistance <= _leftThreshold && rightDistance > _rightThreshold) {
        return 3; // Turn right
    } else {
		return 0; // Error
	}
	
} 

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionLogic::readAndConfirmSensor()
{
	int count = 0;
	int prevDirection = readSensor();
	int currDirection;
    unsigned long startTime = millis();
	do{
        if (millis() - startTime > 3000UL) { // 3 sec
            return 4;
        }
		currDirection = readSensor();
		if(prevDirection == currDirection){
			count += 1;
		} else {
			count = 0;
			prevDirection = currDirection;
		}
	} while (count < 4);
	
	return currDirection;
}



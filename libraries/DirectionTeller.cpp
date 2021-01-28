
#include "Arduino.h"
#include "DirectionTeller.h"

#include "LightSensor.h"
#include "SonicSensor.h"

DirectionTeller::DirectionTeller(LightSensor *frontSensor, SonicSensor *leftSensor, SonicSensor *rightSensor)
	:	_frontLightSensor(frontSensor),
		_leftUltrasonicSensor(leftSensor),
		_rightUltrasonicSensor(rightSensor)
{
	// Nothing to initialize
}


// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionTeller::getDirection()
{
	bool hasFrontObstacle = _frontLightSensor->isObstacleDetected();
	
	if (hasFrontObstacle) {
		return 4;
	} else {
		return readUltrasonicAndDoubleConfirm();
	}
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionTeller::readUltrasonic()
{
	unsigned long leftDistance = _leftUltrasonicSensor->getDistance();
	unsigned long rightDistance = _rightUltrasonicSensor->getDistance();
	
	unsigned long _sd = 17;
	
    if (leftDistance > _sd && rightDistance > _sd) {
        return 1; // Move forward
    } else if (leftDistance <= _sd && rightDistance <= _sd) {
        return 4; // Reverse
    } else if (leftDistance > _sd && rightDistance <= _sd) {
        return 2; // Turn left
    } else if (leftDistance <= _sd && rightDistance > _sd) {
        return 3; // Turn right
    }
	
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionTeller::readUltrasonicAndDoubleConfirm()
{
	int count = 0;
	int prevDirection = readUltrasonic();
	int currDirection;
	do{
		currDirection = readUltrasonic();
		if(prevDirection == currDirection){
			count += 1;
		} else {
			count = 0;
			prevDirection = currDirection;
		}
	} while (count < 4);
	
	return currDirection;
}



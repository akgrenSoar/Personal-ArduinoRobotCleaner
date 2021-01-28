
#include "Arduino.h"
#include "DirectionModule.h"

#include "LightSensor.h"
#include "UltrasonicSensor.h"

DirectionModule::DirectionModule(
	LightSensor *frontSensor,
	UltrasonicSensor *leftSensor,
	UltrasonicSensor *rightSensor)
	:	_frontLightSensor(frontSensor),
		_leftUltrasonicSensor(leftSensor),
		_rightUltrasonicSensor(rightSensor)
{
	_previousDirection = 0;
	_currentDirection = 0; // 0 Stop 1 forward 2 left 3 right 4 reverse
}


// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::getDirection()
{
	int tentativeDirection = readUltrasonicAndDoubleConfirm();
	bool hasFrontObstacle = _frontLightSensor->isObstacleDetected();
	
	if (hasFrontObstacle && tentativeDirection == 1) {
		return 4;
	} else {
		return tentativeDirection;
	}
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::readUltrasonicAndDoubleConfirm()
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
	} while (count < 3);
	
	return currDirection;
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::readUltrasonic()
{
	int leftDistance = _leftUltrasonicSensor->getDistance();
	int rightDistance = _rightUltrasonicSensor->getDistance();
	
    if (leftDistance > 19 && rightDistance > 19) {
        return 1; // Move forward
    } else if (leftDistance < 20 && rightDistance < 20) {
        return 4; // Reverse
    } else if (leftDistance > 19 && rightDistance < 20) {
        return 2; // Turn left
    } else if (leftDistance < 20 && rightDistance > 19) {
        return 3; // Turn right
    }
	
}





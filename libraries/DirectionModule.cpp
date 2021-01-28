
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
	// Nothing to initialize
}


// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::getDirection()
{
	bool hasFrontObstacle = _frontLightSensor->isObstacleDetected();
	
	if (hasFrontObstacle) {
		return 4;
	} else {
		return readUltrasonicAndDoubleConfirm();
	}
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::readUltrasonic()
{
	uint32_t leftDistance = _leftUltrasonicSensor->getDistance();
	uint32_t rightDistance = _rightUltrasonicSensor->getDistance();
	
	uint32_t _sd = 17;
	
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



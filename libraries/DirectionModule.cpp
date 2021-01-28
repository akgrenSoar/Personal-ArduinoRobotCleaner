
#include "Arduino.h"
#include "DirectionModule.h"
#include "MotorDriver.h"
#include "LightSensor.h"
#include "UltrasonicSensor.h"
#include "TouchCapacitive.h"

DirectionModule::DirectionModule(
	MotorDriver *motorDriver,
	LightSensor *frontSensor,
	UltrasonicSensor *leftSensor,
	UltrasonicSensor *rightSensor,
	TouchCapacitive *touchCapacitive)
	:	_motorDriver(motorDriver),
	    _frontLightSensor(frontSensor),
		_leftUltrasonicSensor(leftSensor),
		_rightUltrasonicSensor(rightSensor),
		_touchCapacitive(touchCapacitive)
{
	//*_motorDriver = motorDriver;
	//*_frontLightSensor = frontSensor;
	//*_leftUltrasonicSensor = leftSensor;
	//*_rightUltrasonicSensor = rightSensor;
	
	_previousDirection = 0;
	_currentDirection = 0; // 0 Stop 1 forward 2 left 3 right 4 reverse
	
	srand(analogRead(0)); // Initialize random seed
}

void DirectionModule::stop()
{
	_currentDirection = 0;
	_motorDriver->move(0, 0, 0);
}

void DirectionModule::run(int speed)
{
	_previousDirection = _currentDirection;
	_currentDirection = determineMoveDirection();
	
    // Forward
	if (_currentDirection == 1) {
		if (_currentDirection != _previousDirection) {
			Serial.println("Forward");
			if (rand() & 0x01) {
				if (rand() & 0x01) {
					_motorDriver->move(speed - 30, speed - 10, 0);
				} else {
					_motorDriver->move(speed, speed - 40, 0);
				}
			}  else {
				_motorDriver->move(speed, speed - 10, 0);
			}
		}
	} else {
		_motorDriver->move(0, 0, 0);
		_touchCapacitive->block(600);
		
		switch (_currentDirection) {
			case 2:
				Serial.println("TurnLeft");
				if (_currentDirection != _previousDirection) {
					_motorDriver->move(-speed, 0, 0x7FF);
				} else {
					_motorDriver->move(-speed, speed, 0x3FF); // Full left
				}
				break;
			case 3:
				Serial.println("TurnRight");
				if (_currentDirection != _previousDirection) {
					_motorDriver->move(0, -speed, 0x7FF);
				} else {
					_motorDriver->move(speed, -speed, 0x3FF); // Full right
				}
				break;
			case 4:
				Serial.println("Reverse");
				if (_currentDirection != _previousDirection) {
					(rand() & 0x01) ? _motorDriver->move(-speed, 0, 0x7FF) : _motorDriver->move(0, -speed, 0x7FF);
				} else {
					(rand() & 0x01) ? _motorDriver->move(-speed, speed, 0x7FF) : _motorDriver->move(speed, -speed, 0x7FF);
				}
				break;
		}
	}
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::determineMoveDirection()
{
	int tentativeDirection = confirmUltrasonic();
	bool hasFrontObstacle = _frontLightSensor->isObstacleDetected();
	
	if (hasFrontObstacle && tentativeDirection == 1) {
		return 4;
	} else {
		return tentativeDirection;
	}
}


// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::confirmUltrasonic()
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
	
    //Serial.print(leftDistance);
    //Serial.print("/");
    //Serial.println(rightDistance);
	
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





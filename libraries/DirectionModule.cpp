
#include "Arduino.h"
#include "DirectionModule.h"
#include "MotorDriver.h"
#include "LightSensor.h"
#include "UltrasonicSensor.h"

DirectionModule::DirectionModule(
	MotorDriver motorDriver,
	LightSensor frontSensor,
	UltrasonicSensor leftSensor,
	UltrasonicSensor rightSensor)
	:	_motorDriver(motorDriver),
	    _frontLightSensor(frontSensor),
		_leftUltrasonicSensor(leftSensor),
		_rightUltrasonicSensor(rightSensor)
{
	//_motorDriver = motorDriver;
	//_frontLightSensor = frontSensor;
	//_leftUltrasonicSensor = leftSensor;
	//_rightUltrasonicSensor = rightSensor;
	
	_previousDirection = 0;
	_currentDirection = 0; // 0 Stop 1 forward 2 left 3 right 4 reverse
	
	srand(analogRead(0)); // Initialize random seed
}

void DirectionModule::stop()
{
	_currentDirection = 0;
	_motorDriver.move(0, 0, 0);
}

void DirectionModule::run(int speed)
{
	_previousDirection = _currentDirection;
	_currentDirection = determineMoveDirection();
	
	if (_currentDirection == 1) {
		_motorDriver.move(speed, speed, 0);
		
	} else if (_currentDirection == 4) {
		_motorDriver.move(0, 0, 0);
		delay(500);
		(rand() & 0x01) == 0 ? _motorDriver.move(-speed, 0, 0x7FF) : _motorDriver.move(0, -speed, 0x7FF);
		
	} else {
		_motorDriver.move(0, 0, 0);
		delay(700);
		switch (_currentDirection) {
			case 2:
				if (_currentDirection != _previousDirection) {
					_motorDriver.move(-speed, 0, 0x7FF);
				} else {
					_motorDriver.move(-speed, speed, 0x3FF); // Full left
				}
				break;
			case 3:
				if (_currentDirection != _previousDirection) {
					_motorDriver.move(0, -speed, 0x7FF);
				} else {
					_motorDriver.move(speed, -speed, 0x3FF); // Full right
				}
				break;
		}
	}
}

// Returns 1 Forward 2 Left 3 Right 4 Reverse
int DirectionModule::determineMoveDirection()
{
	int tentativeDirection = confirmUltrasonic();
	bool hasFrontObstacle = _frontLightSensor.isObstacleDetected();
	
	//Serial.print("Has front obstacle ");
	//Serial.println(hasFrontObstacle);
	
	if (hasFrontObstacle && tentativeDirection == 1) {
		Serial.println("Reversing");
		return 4;
	} else {
		if (tentativeDirection == 1) {
			Serial.println("Forward");
		} else if (tentativeDirection == 2) {
			Serial.println("TurnLeft");
		} else if (tentativeDirection == 3) {
			Serial.println("TurnRight");
		} else {
			Serial.println("Reversing");
		}
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
	int leftDistance = _leftUltrasonicSensor.getDistance();
	int rightDistance = _rightUltrasonicSensor.getDistance();
	
    //Serial.print(leftDistance);
    //Serial.print("/");
    //Serial.println(rightDistance);
	
    if (leftDistance > 18 && rightDistance > 18) {
        return 1; // Move forward
    } else if (leftDistance < 19 && rightDistance < 19) {
        return 4; // Reverse
    } else if (leftDistance > 18 && rightDistance < 19) {
        return 2; // Turn left
    } else if (leftDistance < 19 && rightDistance > 18) {
        return 3; // Turn right
    }
	
}





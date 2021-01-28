
#include <SonicSensor.h>
#include <TouchSensor.h>
#include <MotorDriver.h>
#include <DirectionLogic.h>
#include <MovementLogic.h>
#include <Timer.h>

// Program Configuration
const unsigned long RUN_DURATION = 60000UL * 30; // 30 minutes
const unsigned long PAUSE_BEFORE_MOVE_DURATION = 230;
const uint8_t ROBOT_SPEED = 255; // 0-255

SonicSensor frontSonic (A0, A1); // TriggerPin, EchoPin
SonicSensor leftSonic (4, 5); // TriggerPin, EchoPino
SonicSensor rightSonic (7, 8); // TriggerPin, EchoPin
TouchSensor touchSensor (A5); // InputPin
MotorDriver motorDriver (9, 6, 11, 10); // Digital_PWM_1, Digital_PWM_2 (Right), Digital_PWM_4, Digital_PWM_3 (Left)

// Program constants (Do not touch)
#define DIR_STOP 0
#define DIR_FORWARD 1
#define DIR_LEFT 2
#define DIR_RIGHT 3
#define DIR_REVERSE 4

// Additional modules and variables (Do not touch)
DirectionLogic directionLogic (&frontSonic, &leftSonic, &rightSonic);
MovementLogic movementLogic (&motorDriver, PAUSE_BEFORE_MOVE_DURATION, ROBOT_SPEED);
Timer timer (RUN_DURATION);
bool isEnabled;
int i;

void setup()
{
  Serial.begin(9600);
  randomSeed((unsigned long) (analogRead(A0) % 47 + 1) * (analogRead(A1) % 41 + 1) * (analogRead(A6) % 43 + 1) * (analogRead(A7) % 37 + 1));
	stop();
}

void start()
{
	timer.start();
	isEnabled = true;
}

void stop()
{
	movementLogic.stop();
	isEnabled = false;
}

void checkUserInput()
{
	if (!touchSensor.isPressed()) {
		return;
	}
	
	movementLogic.stop();
	
	while (touchSensor.isPressed()) {
		delay(10);
	}
	
	// Toggle start/stop
	(isEnabled) ? stop() : start();
}

void loop()
{
  delay(10);
  
  checkUserInput();
	
  if (!isEnabled) {
		return;
  }
	
  if (timer.isExpired()) {
		stop();
		return;
  }

  i = i + 1;
  i = i % 10;
  if (i != 0) {
    return;
  }
  
	int direction = directionLogic.getDirection();
	
	switch (direction) {
		case DIR_FORWARD:
			movementLogic.forward();
			break;
		case DIR_LEFT:
			movementLogic.left();
			break;
		case DIR_RIGHT:
			movementLogic.right();
			break;
		case DIR_REVERSE:
			movementLogic.reverse();
			break;
		default:
			motorDriver.move(-255,-255);
	}

}

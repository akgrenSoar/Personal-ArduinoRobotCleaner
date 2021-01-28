
#include <SonicSensor.h>
#include <TouchSensor.h>
#include <MotorDriver.h>
#include <DirectionLogic.h>
#include <MovementLogic.h>
#include <Timer.h>

// Program Configuration
const unsigned long RUN_DURATION = 60000UL * 30; // 30 minutes
const uint8_t ROBOT_SPEED = 255; // 0-255

SonicSensor frontSonic (A0, A1); // TriggerPin, EchoPin
SonicSensor leftSonic (4, 5); // TriggerPin, EchoPino
SonicSensor rightSonic (7, 8); // TriggerPin, EchoPin
TouchSensor button1 (A2); // InputPin
TouchSensor button2 (A3); // InputPin
TouchSensor button3 (A4); // InputPin
TouchSensor button4 (A5); // InputPin
MotorDriver motorDriver (9, 6, 11, 10); // Digital_PWM_1, Digital_PWM_2 (Right), Digital_PWM_4, Digital_PWM_3 (Left)

// Program constants (Do not touch)
#define DIR_STOP 0
#define DIR_FORWARD 1
#define DIR_LEFT 2
#define DIR_RIGHT 3
#define DIR_REVERSE 4

// Additional modules and variables (Do not touch)
DirectionLogic directionLogic (&frontSonic, &leftSonic, &rightSonic);
MovementLogic wheel (&motorDriver, ROBOT_SPEED);
Timer timer(RUN_DURATION);
bool isEnabled;
bool isPausedBetweenMovements;

void setup()
{
  Serial.begin(9600);
  randomSeed((unsigned long) (analogRead(A0) % 47 + 1) * (analogRead(A1) % 41 + 1) * (analogRead(A6) % 43 + 1) * (analogRead(A7) % 37 + 1));
  resetRobot();
}

void resetRobot()
{
  timer.reset();
  isEnabled = false;
  isPausedBetweenMovements = false;
  wheel.setDirection(0);
}

void userInput()
{
  if (button1.isPressed() || button2.isPressed() || button3.isPressed() || button4.isPressed()) {
    bool wasEnabled = isEnabled;
    resetRobot();
    while(button1.getState() || button2.getState() || button3.getState() || button4.getState()) delay(32);
    isEnabled = !wasEnabled;
    timer.start();
  }
}

void pauseBetweenMovements() {
  isPausedBetweenMovements = true;
  wheel.setDirection(DIR_STOP);
  wheel.pause(230);
}

void loop()
{
  // Mini pause
  delay(32);
  
  // Check for user input
  userInput();

  // Stop running if not enabled
  if (!isEnabled) {
    if (wheel.getDirection() != DIR_STOP) wheel.setDirection(DIR_STOP);
    return;
  }
  
  // Stop running if timer is expired
  if (timer.isExpired()) {
    isEnabled = false;
    if (wheel.getDirection() != DIR_STOP) wheel.setDirection(DIR_STOP);
    return;
  }

  // Robot is paused, perform next movement
  if (wheel.isExpired() && isPausedBetweenMovements) {
    isPausedBetweenMovements = false;
    wheel.setDirection(directionLogic.getDirection());
    return;
  }
  
  // Current movement has expired, pause before next movement
  if (wheel.isExpired() && !isPausedBetweenMovements) {
    pauseBetweenMovements();
    return;
  }
  
  int prevDirection = wheel.getDirection();
  int currDirection = directionLogic.getDirection();
   
  // All movements has priority over DIR_FORWARD, pause before changing movement
  if (prevDirection == DIR_FORWARD && currDirection != DIR_FORWARD) {
    pauseBetweenMovements();
    return;
  }
  
  // Continue in current direction
  // Nothing to do
  return;
}

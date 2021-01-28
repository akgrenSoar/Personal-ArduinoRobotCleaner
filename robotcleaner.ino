#include <DirectionTeller.h>
#include <LightSensor.h>
#include <MotorDriver.h>
#include <MovementModule.h>
#include <SonicSensor.h>
#include <Timer.h>
#include <TouchSensor.h>



// Initialize Inputs and Output devices
LightSensor frontSensor (12); // Input
SonicSensor leftSonic (7, 8); // Trigger, Echo
SonicSensor rightSonic (9, 10); // Trigger, Echo
TouchSensor touchMenu (A2, A3, A4, A5); // Input1, Input2, Input3, Input4
MotorDriver motorDriver (5, 4, 3, 2); // Analog1, Digital1, Analog2, Digital2

// Initialize program modules
DirectionTeller directionTeller (&frontSensor, &leftSonic, &rightSonic);
MovementModule wheel (&motorDriver);

// Initialize Program Variables
const unsigned long RUN_DURATION = 60000UL * 10;
Timer timer;
bool isEnabled;
bool isPausedBetweenMovements;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
  resetRobot();
  unsigned long seed = (analogRead(A0) % 47 + 1) * (analogRead(A1) % 41 + 1) * (analogRead(A6) % 43 + 1) * (analogRead(A7) % 37 + 1);
  randomSeed(seed);
}

void resetRobot()
{
  timer.setDuration(RUN_DURATION);
  isEnabled = false;
  isPausedBetweenMovements = false;
  wheel.setDirection(0);
  wheel.setSpeed(255);
}

void userInterface(uint8_t buttonPressed)
{
  switch (buttonPressed)
  {
    case 0:
      // do nothing
      break;
    case 1:
      timer.setDuration(timer.getDuration() + RUN_DURATION);
      break;
    case 2:
      resetRobot();
      break;
    case 3:
      isEnabled = !isEnabled;
      break;
    case 4:
      wheel.setSpeed( (wheel.getSpeed() < 200) ? 255 : wheel.getSpeed() - 20 );
      wheel.refresh();
      break;
    default:
      break;
  }
}

int pauseBeforeMove(int tentativeDirection) {
    if (isPausedBetweenMovements == false) {
      isPausedBetweenMovements = true;
      wheel.pause(230);
      return 5;
    } else {
      isPausedBetweenMovements = false;
      return tentativeDirection;
    }
}

// 0 stop, 1 forward, 2 left, 3 right, 4 reverse, 5 no change
int determineDirection()
{
  
  // Direction has expired, change direction
  if (wheel.isExpired()) {
    return pauseBeforeMove(directionTeller.getDirection());
  }
  
  // Direction override due to priority
  int prevDirection = wheel.getDirection();
  int currDirection = directionTeller.getDirection();
  if (prevDirection == 1 && currDirection != 1) {
    wheel.setDirection(0);
    isPausedBetweenMovements = true;
    wheel.pause(230);
    return 5;
  }
  
  // Not expired, no change in direction
  return 5;
}

void loop()
{
  // Check for user input
  userInterface(touchMenu.getButtonReleased());

  if (isEnabled) {
    wheel.setDirection(determineDirection());
  } else {
    if (wheel.getDirection() != 0) wheel.setDirection(0);
  }

  // Mini pause
  delay(32);

}
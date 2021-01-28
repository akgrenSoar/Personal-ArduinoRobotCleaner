
#include <DirectionModule.h>
#include <EnableModule.h>
#include <LightSensor.h>
#include <MotorDriver.h>
#include <TouchCapacitive.h>
#include <UltrasonicSensor.h>
#include <Wheel.h>

// Initialize Inputs and Output devices
UltrasonicSensor leftSonic (7, 8); // Trigger, Echo
UltrasonicSensor rightSonic (9, 10); // Trigger, Echo
LightSensor frontSensor (12); // Input
TouchCapacitive touchMenu (A2, A3, A4, A5); // Input1, Input2, Input3, Input4
MotorDriver motorDriver (3, 2, 5, 4); // Analog1, Digital1, Analog2, Digital2

// Initialize program modules
DirectionModule directionModule (&frontSensor, &leftSonic, &rightSonic);
EnableModule enableModule;

// Initialize Program Variables
int moveSpeed = 255;
Wheel wheel(&motorDriver, moveSpeed);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
}

void resetRobot() {
  enableModule.reset();
  moveSpeed = 255;
  wheel.pause();
}

uint8_t getInput() {
  uint8_t buttonPressed = 0;
  uint8_t temp = touchMenu.getButtonPressed();
  while (temp != 0) {
    delay(100);
    buttonPressed = temp;
    temp = touchMenu.getButtonPressed();
  };
  return buttonPressed;
}

void userInterface(uint8_t buttonPressed) {

  if (buttonPressed != 0) {
    wheel.pause();
    delay(300);
  }

  switch (buttonPressed) {
    case 1:
      enableModule.addDuration(10);
      Serial.println("Pressed Button 1 (Add 10 minutes)");
      break;
    case 2:
      resetRobot();
      Serial.println("Pressed Button 2 (Reset)");
      break;
    case 3:
      enableModule.toggleStart();
      Serial.println("Pressed Button 3 (Toggle start/stop)");
      break;
    case 4:
      moveSpeed = (moveSpeed < 165) ? 255 : moveSpeed - 35;
      wheel.setSpeed(moveSpeed);
      Serial.println("Pressed Button 4 (Decrease move speed)");
      break;
    case 0:
    default:
      return;
  }
}

void verifyAndSetDirection() {
  
  uint8_t nextDirection = directionModule.getDirection();

  // Direction has expired, set next direction
  if (wheel.isExpired()) {
    delay(600);
    wheel.setDirectionAndRenew(nextDirection);
  }

  // Obstacle detected while moving forward, overwrite direction
  if (wheel.getDirection() == 1 && wheel.getDirection() != nextDirection) {
    wheel.pause();
    delay(500);
    wheel.setDirectionAndRenew(nextDirection);
    
  }
  
}

void loop() {

  // Check for user input
  userInterface(getInput());

  // Movement enabled
  if (enableModule.isEnabled()) {
    verifyAndSetDirection();
    wheel.run();

  // Movement disabled
  } else {
    wheel.pause();
  }
  
  // Mini pause
  delay(32);
  
}

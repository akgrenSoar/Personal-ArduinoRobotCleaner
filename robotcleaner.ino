
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
MotorDriver motorDriver (5, 4, 3, 2); // Analog1, Digital1, Analog2, Digital2

// Initialize program modules
DirectionModule directionModule (&frontSensor, &leftSonic, &rightSonic);
EnableModule enableModule;

// Initialize Program Variables
Wheel wheel(&motorDriver);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
}

void resetRobot() {
  enableModule.reset();
  wheel.pause();
  wheel.setSpeed(255);
}

uint8_t getInput() {
  uint8_t buttonPressed = 0;
  uint8_t temp = touchMenu.getButtonPressed();
  while (temp != 0) {
    delay(100);
    buttonPressed = temp;
    temp = touchMenu.getButtonPressed();
    wheel.pause();
  };
  return buttonPressed;
}

void userInterface(uint8_t buttonPressed) {

  if (buttonPressed != 0) {
    wheel.stall(500);
  }

  switch (buttonPressed) {
    case 1:
      enableModule.setDuration( enableModule.getDuration() + 15 );
      Serial.print("Duration: ");
      Serial.print(enableModule.getDuration());
      Serial.println(" minutes");
      break;
    case 2:
      resetRobot();
      Serial.println("Status: Reset");
      break;
    case 3:
      if (!enableModule.isRunning()) {
        enableModule.start();
        Serial.println("Status: Start");
      } else {
        enableModule.stop();
        Serial.println("Status: Stop");
      }
      break;
    case 4:
      wheel.setSpeed( (wheel.getSpeed() < 200) ? 255 : wheel.getSpeed() - 20 );
      Serial.print("Speed: ");
      Serial.println(wheel.getSpeed());
      break;
    case 0:
    default:
      break;
  }
}

void setDirection() {

  uint8_t nextDirection = directionModule.getDirection();

  // Expired and stalled, change direction
  if (wheel.isStalled()) {
    if (wheel.isExpired()) {
      Serial.print("Direction: ");
      Serial.println(nextDirection);
      wheel.setDirection(nextDirection);
    }
    
  } else {
    // Expired, going into stall
    if (wheel.isExpired()) {
      Serial.println("Expired Stall");
      wheel.stall(600);
    }
    
    // Obstacle detected while moving forward, overwrite direction
    if (wheel.getDirection() == 1 && wheel.getDirection() != nextDirection) {
      Serial.println("Direction Stall");
      wheel.stall(500);
    }
  }
  
}

void loop() {

  // Check for user input
  userInterface(getInput());

  // Movement enabled
  if (enableModule.test()) {
    setDirection();
    wheel.run();

    // Movement disabled
  } else {
    wheel.pause();
  }

  // Mini pause
  delay(32);

}

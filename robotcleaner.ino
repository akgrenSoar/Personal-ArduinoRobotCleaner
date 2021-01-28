
#include <DirectionModule.h>
#include <EnableModule.h>
#include <LightSensor.h>
#include <MotorDriver.h>
#include <TouchCapacitive.h>
#include <UltrasonicSensor.h>


UltrasonicSensor leftSonic (7, 8); // Trigger, Echo
UltrasonicSensor rightSonic (9, 10); // Trigger, Echo
LightSensor frontSensor (12); // Input

MotorDriver motorDriver (3, 2, 5, 4); // Analog1, Digital1, Analog2, DIgital2
TouchCapacitive touchMenu (A2, A3, A4, A5); // Input1, Input2, Input3, Input4
DirectionModule directionModule (motorDriver, frontSensor, leftSonic, rightSonic);
EnableModule enableModule;

int moveSpeed = 255;

void resetRobot() {
  motorDriver.move(0, 0, 0);
  enableModule.reset();
  moveSpeed = 255;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
  resetRobot();
}

void userInterface(uint8_t buttonPressed) {

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
      moveSpeed = (moveSpeed < 130) ? 255 : moveSpeed - 35;
      Serial.println("Pressed Button 4 (Decrease move speed)");
      break;
    default:
      return;
  }
}


void loop() {

  // Check for user input
  userInterface(touchMenu.getButtonPressed());
  
  // Mini pause to save battery
  delay(100);

  // Check for user input
  userInterface(touchMenu.getButtonPressed());

  // 
  if (enableModule.isEnabled()) {
    directionModule.run(moveSpeed);
  } else {
    directionModule.stop();
  }
  
  
}

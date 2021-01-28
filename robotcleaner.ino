
#include <DirectionModule.h>
#include <EnableModule.h>
#include <LightSensor.h>
#include <MotorDriver.h>
#include <TouchCapacitive.h>
#include <UltrasonicSensor.h>


UltrasonicSensor leftSonic (7, 8); // Trigger, Echo
UltrasonicSensor rightSonic (9, 10); // Trigger, Echo
LightSensor frontSensor (12); // Input

TouchCapacitive touchMenu (A2, A3, A4, A5); // Input1, Input2, Input3, Input4
MotorDriver motorDriver (3, 2, 5, 4, &touchMenu); // Analog1, Digital1, Analog2, Digital2

DirectionModule directionModule (&motorDriver, &frontSensor, &leftSonic, &rightSonic, &touchMenu);
EnableModule enableModule;

int moveSpeed = 255;

void resetRobot() {
  directionModule.stop();
  enableModule.reset();
  moveSpeed = 255;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
  resetRobot();
}

void userInterface(uint8_t buttonPressed) {

  if (buttonPressed != 0) {
    // 1. Stop for 300ms to acknowledge button is pressed
    directionModule.stop();
    touchMenu.block(300);
    // 2. User can make correction to the button pressed within that 500ms
    uint8_t newButtonPressed = touchMenu.getButtonPressed();
    if (newButtonPressed != 0) {
      buttonPressed = newButtonPressed;
    }
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
      moveSpeed = (moveSpeed < 130) ? 255 : moveSpeed - 35;
      Serial.println("Pressed Button 4 (Decrease move speed)");
      break;
    case 0:
    default:
      return;
  }
}


void loop() {
  
  // Mini pause to save battery. Robot is only responsive every 100ms
  delay(100);

  // Check for user input
  userInterface(touchMenu.getButtonPressed());

  // Move
  if (enableModule.isEnabled()) {
    directionModule.run(moveSpeed);
  } else {
    directionModule.stop();
  }
  
  
}

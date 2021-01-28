#include <MotorDriver.h>
#include <TouchCapacitive.h>
#include <Ultrasonic.h>


MotorDriver wheel (3, 2, 5, 4); // Analog1, Digital1, Analog2, DIgital2
TouchCapacitive touchMenu (A2, A3, A4, A5); // Input1, Input2, Input3, INput4
Ultrasonic leftSonic (7, 8); // Trigger, Echo
Ultrasonic rightSonic (9, 10); // Trigger, Echo
int leftSonicDistance;
int rightSonicDistance;

uint32_t programTimer; // The time that robot started running ( programTimer = millis() )
uint32_t programRunDuration; // Robot stops running after ( x minutes * 60000L )
bool programIsRunning; // If true, robot is running. If false, robot is not running.

int robotMoveSpeed; // Forward move speed
int robotTurnSpeed; // Turn left, turn right speed
int currMoveState; // Available states: Forward(1), left(2), right(3), reverse(4), stop(0)
int nextMoveState;
int robotMoveDelay; // Pauses for x milliseconds before changing direction

int touchCapacitiveDelay; // Touch capacitive cannot be pressed again within x milliseconds

void resetRobot() {
  programTimer = 0;
  programRunDuration = 1 * 60000L; // 1 minute
  programIsRunning = false; // Not running
  robotMoveSpeed = 180;
  robotTurnSpeed = 180;
  currMoveState = 0;
  nextMoveState = 0;
  wheel.move(0, 0);
  robotMoveDelay = 500;
  touchCapacitiveDelay = 100;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Starts the serial communication
  srand (analogRead(0)); // Initialise random with seedm
  resetRobot();
}

void userInterface() {

  if ( touchMenu.isPressed(1) && !programIsRunning)
  { // Add 30 minutes to run duration
    programRunDuration += 30 * 60000L; // Increment by 30 minutes
    Serial.print("Run duration is: ");
    Serial.println(programRunDuration / 60000L);
    while ( touchMenu.isPressed(1) ) delay ( touchCapacitiveDelay );
  }
  else if ( touchMenu.isPressed(2) )
  { // Reset run parameters
    resetRobot();
    Serial.println("reset");
    while ( touchMenu.isPressed(2) ) delay ( touchCapacitiveDelay );
  }
  else if ( touchMenu.isPressed(3) )
  { // If running, set to pause. If paused, set to run.
    programIsRunning = !programIsRunning;
    robotMove(0);
    Serial.println("Run/Pause");
    while ( touchMenu.isPressed(3) ) delay ( touchCapacitiveDelay );
  }
  else if ( touchMenu.isPressed(4) )
  { // Change speed -> [150, 180, 210, 240]
    //( robotMoveSpeed == 240 ) ? robotMoveSpeed = 150 : robotMoveSpeed += 30;
    //Serial.print("Speed: ");
    //Serial.println(robotMoveSpeed);
    while ( touchMenu.isPressed(4) ) delay ( touchCapacitiveDelay );
  }

}

int robotConfirmSonic(){
  int count = 0;
  int prevDirection = robotCheckSonic();
  int currDirection;
  do{
    currDirection = robotCheckSonic();
    if(prevDirection == currDirection){
      count += 1;
    } else {
      count = 0;
      prevDirection = currDirection;
    }
  } while (count < 3);
}

int robotCheckSonic () {

  leftSonicDistance = leftSonic.read();
  rightSonicDistance = rightSonic.read();

  Serial.print(leftSonicDistance);
  Serial.print("/");
  Serial.println(rightSonicDistance);

  if (leftSonicDistance > 18 && rightSonicDistance > 18) {
    return 1; // Move forward
  } else if (leftSonicDistance < 19 && rightSonicDistance < 19) {
    return 4; // Reverse
  } else if (leftSonicDistance > 18 && rightSonicDistance < 19) {
    return 2; // Turn left
  } else if (leftSonicDistance < 19 && rightSonicDistance > 18) {
    return 3; // Turn right
  }
}

void robotMove (int moveDirection) {
  switch (moveDirection) {
    case 1: // Forward
      wheel.move(robotMoveSpeed, robotMoveSpeed);
      break;
    case 2: // Left
      wheel.move(-robotTurnSpeed, 0);
      delay( rand() % 2000 + 500 ); // 500-2500ms
      break;
    case 3: // Right
      wheel.move(0, -robotTurnSpeed);
      delay( rand() % 2000 + 500 );
      break;
    case 4: // Reverse
      ( rand() % 2 == 1 ) ? wheel.move(-robotTurnSpeed, 0) : wheel.move(0, -robotTurnSpeed);
      delay( rand() % 2000 + 500 );
      break;
    case 12: // Full Left
      wheel.move(-robotTurnSpeed, robotTurnSpeed);
      delay( rand() % 1000 + 500 ); // 500-1500ms
      break;
    case 13: // Full Right
      wheel.move(robotTurnSpeed, -robotTurnSpeed);
      delay( rand() % 1000 + 500 );
      break;
    case 0:
    default:
      wheel.move(0, 0);
      delay(robotMoveDelay);
  }
  currMoveState = moveDirection;
}


void loop() {

  // Mini pause to save battery
  delay(100);

  // Check for user input
  userInterface();

  // Skip if program is paused
  if ( programIsRunning == false ) return;

  // Record the current time (if not yet recorded)
  if ( programTimer == 0 ) programTimer = millis();

  // Stop robot if time is up
  if ( millis() - programTimer > programRunDuration ) {
    resetRobot();
    Serial.println("time is up");
    return;
  }

  // Start of main program

  // Robot must come to complete stop before moving
  // Robot states: Foward(1), Left(2), Right(3), Reverse(4), Stop(0)
  nextMoveState = robotConfirmSonic();
  if (currMoveState == 0) { // Robot is not moving
    robotMove( robotConfirmSonic() );
  } else if (currMoveState == nextMoveState) { // Robot is already in the correct direction
    // If previous action was to soft turn, make a hard turn next
    if (currMoveState == 2 || currMoveState == 3){
      robotMove(currMoveState + 10);
    }
  } else { // Robot needs to change direction
    robotMove(0);
    delay(500);
    robotMove(robotConfirmSonic());
  }

}

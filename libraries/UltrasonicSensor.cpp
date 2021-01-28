
#include "Arduino.h"
#include "UltrasonicSensor.h"
#include "MotorDriver.h"
#include "LightSensor.h"
#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(uint8_t trigPin, uint8_t echoPin)
{
	_trigPin = trigPin;
	_echoPin = echoPin;
	pinMode(_trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(_echoPin, INPUT); // Sets the echoPin as an Input
}

int UltrasonicSensor::getDistance()
{
	digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    int duration = pulseIn(_echoPin, HIGH);
    // Calculating the distance
    int distance = duration >> 6; // duration / 58.2
  
    return distance;
}
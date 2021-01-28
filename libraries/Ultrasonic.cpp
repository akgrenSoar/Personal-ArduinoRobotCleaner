

#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trigPin, int echoPin)
{
	_trigPin = trigPin;
	_echoPin = echoPin;
	pinMode(_trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(_echoPin, INPUT); // Sets the echoPin as an Input
}

int Ultrasonic::read()
{
	return getDistance();
}

int Ultrasonic::getDistance()
{
	digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    int duration = pulseIn(_echoPin, HIGH);
    // Calculating the distance
    int distance = duration / 58.2;
  
    return distance;
}
#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

class Ultrasonic {

  public:
    Ultrasonic(int trigPin, int echoPin);
    int read ();

  private:
    int _trigPin;
    int _echoPin;
	int getDistance (void);
  
};

#endif
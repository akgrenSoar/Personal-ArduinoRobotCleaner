
#ifndef TouchSensor_h
#define TouchSensor_h

#include "Arduino.h"

class TouchSensor {

  public:
	TouchSensor(uint8_t pinIn);
	bool getState();
    bool isPressed();
	bool isReleased();

  private:
    const uint8_t _pinIn;
	bool prevState;

};

#endif

#ifndef TouchSensor_h
#define TouchSensor_h

#include "Arduino.h"

class TouchSensor {

  public:
	TouchSensor(uint8_t pinIn);
    bool isPressed();

  private:
    const uint8_t _pinIn;
};

#endif

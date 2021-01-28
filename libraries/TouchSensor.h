
#ifndef TouchSensor_h
#define TouchSensor_h

#include "Arduino.h"

class TouchSensor {

  public:
	TouchSensor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
	uint8_t getButtonReleased();
    uint8_t getButtonPressed();

  private:
    const uint8_t _pins[4];
	bool isButtonPressed(uint8_t buttonNumber);

};

#endif
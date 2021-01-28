#ifndef TouchCapacitive_h
#define TouchCapacitive_h

#include "Arduino.h"

class TouchCapacitive {

  public:
	TouchCapacitive(int pin1, int pin2, int pin3, int pin4);
    uint8_t getButtonPressed();

  private:
	int _delayTime;
    int _pins[4];
	bool isButtonPressed(uint8_t buttonNumber);
	void pauseWhilePressed(uint8_t buttonNumber);

};

#endif
#ifndef TouchCapacitive_h
#define TouchCapacitive_h

#include "Arduino.h"

class TouchCapacitive {

  public:
	TouchCapacitive(int pin1, int pin2, int pin3, int pin4);
	void block(int duration);
    uint8_t getButtonPressed();

  private:
    int _pins[4];
	bool _isBufferUsed;
	uint8_t _bufferValue;
	bool isButtonPressed(uint8_t buttonNumber);

};

#endif
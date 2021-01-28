#ifndef TouchCapacitive_h
#define TouchCapacitive_h

#include "Arduino.h"

class TouchCapacitive {

  public:
	TouchCapacitive(int pin1, int pin2, int pin3, int pin4);
    bool isPressed(int button);

  private:
    int _pins [4];

};

#endif
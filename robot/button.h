#ifndef BUTTON_H
#define BUTTON_H

#include "pins.h"

class Button {
public:
  Button(int pinNum) {
    pin = Pin(pinNum, PULL_UP);
    lastState = false;
  };

  bool isPressed() {
    return pin.read() == LOW;
  }

  bool isPressedPulse() {
    bool state = pin.read() == LOW;
    if (state && !lastState) { // turned on
      lastState = state;
      return true;
    } else {
      lastState = state;
      return false;
    }
  }

  bool isUnpressedPulse() {
    bool state = pin.read() == LOW;
    if (!state && lastState) { // turned off
      lastState = state;
      return true;
    } else {
      lastState = state;
      return false;
    }
  }
private:
  Pin pin;
  bool lastState;
};

#endif

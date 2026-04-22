#ifndef LED_H
#define LED_H

#include "pins.h"

class LED {
  public:
   LED(int pinnum) {
    pin = Pin(pinnum, OUTPUT);
    pin.write(LOW);
    mode = LOW;
   }
   LED(int pinnum, int defaultState) {
    pin = Pin(pinnum, OUTPUT);
    pin.write(defaultState);
    mode = defaultState;
   }

    void Toggle() {
      if (mode == HIGH) {
        pin.write(LOW);
        mode = LOW;
      } else {
        pin.write(HIGH);
        mode = HIGH;
      }
    }

   void On() {
    pin.write(HIGH);
    mode = HIGH;
   }

   void Off() {
    pin.write(LOW);
    mode = LOW;
   }
  private:
    Pin pin;
    int mode;
};

#endif
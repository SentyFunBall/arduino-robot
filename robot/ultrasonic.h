#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pins.h"

class Ultrasonic {
  public:
    Ultrasonic(int trigPin, int echoPin) {
      trig = Pin(trigPin, OUTPUT);
      echo = Pin(echoPin, INPUT);
    };

    float getDistance() {
      trig.write(LOW);
      delayMicroseconds(2);
      trig.write(HIGH);
      delayMicroseconds(10);
      trig.write(LOW);

      float duration = pulseIn(echo.pinnum, HIGH);
      return (duration * 0.343f)/2;
    };

  private:
    Pin trig;
    Pin echo;
};

#endif

#ifndef MOTOR_H
#define MOTOR_H

#include "pins.h"

class Motor {
public:
  Motor(int dir1pin, int dir2pin, int encpin) {
    enc = Pin(encpin, OUTPUT);
    dir1 = Pin(dir1pin, OUTPUT);
    dir2 = Pin(dir2pin, OUTPUT);
  }

  // 1 = forward -1 = backward
  void setDirection(int dir) {
    if (dir == 1) {
      dir1.write(HIGH);
      dir2.write(LOW);
    } else {
      dir2.write(LOW);
      dir2.write(HIGH);
    }
  }

  // 0-255
  void setSpeed(signed int speed) {
    analogWrite(enc.pinnum, speed);
  }

  void off() {
    // Turn off motors - Initial state
    analogWrite(enc.pinnum, 0);
    dir1.write(LOW);
    dir2.write(LOW);
  }
private:
  Pin enc;
  Pin dir1;
  Pin dir2;
};

#endif
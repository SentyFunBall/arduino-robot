#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
  Motor(int dir1pin, int dir2pin, int encpin) {
    enc = encpin;
    dir1 = dir1pin;
    dir2 = dir2pin;
    pinMode(enc, OUTPUT);
    pinMode(dir1, OUTPUT);
    pinMode(dir2, OUTPUT);
  }

  // 1 = forward -1 = backward
  void setDirection(int dir) {
    if (dir == 1) {
      digitalWrite(dir1, HIGH);
      digitalWrite(dir2, LOW);
    } else {
      digitalWrite(dir1, LOW);
      digitalWrite(dir2, HIGH);
    }
  }

  // 0-255
  void setSpeed(signed int speed) {
    analogWrite(enc, speed);
  }

  void off() {
    // Turn off motors - Initial state
    analogWrite(enc, 0);
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
  }
private:
  int enc;
  int dir1;
  int dir2;
};

#endif
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class Ultrasonic {
  public:
    Ultrasonic(int trigPin, int echoPin) {
      trig = trigPin;
      echo = echoPin;
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    };

    float getDistance() {
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);

      float duration = pulseIn(echo, HIGH);
      return (duration * 0.343f)/2;
    };

  private:
    int trig;
    int echo;
};

#endif

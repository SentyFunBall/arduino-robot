#include "uart.h"
#include "ultrasonic.h"
#include "motor.h"
#include "led.h"
#include "button.h"

Ultrasonic sensor(9, 10);
Motor moto(4, 3, 2);
LED led(21);
Button btn(20);

void setup() {
  U0init(9600);
  moto.off();
  moto.setDirection(1);
}

void loop() {
  /*U0putstr("Distance: ");
  float d = sensor.getDistance();
  unsigned char* dstr = floatToUChar(d, 0);

  int speed = clamp(d, 0, 255);
  U0putstrln(floatToUChar(float(speed), 0));
  //moto.setSpeed(speed);
  delay(100);*/
  if (btn.isPressedPulse()) {
    led.Toggle();
    //U0putstrln("pressed");
  }
  delay(10);
}

unsigned char* floatToUChar(float value, int decimals) {
  static unsigned char buffer[20];
  dtostrf(value, 0, decimals, (char*)buffer);
  return buffer;
}

int clamp(float v, int min, int max) {
  if (v < min) return min;
  if (v > max) return max;
  return v;
}
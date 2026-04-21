#include "uart.h"
#include "ultrasonic.h"
#include "motor.h"

Ultrasonic sensor(9, 10);
Motor moto(4, 3, 2);

void setup() {
  U0init(9600);
  moto.off();
  moto.setDirection(1);
}

void loop() {
  /*U0putstr("Distance: ");
  float d = sensor.getDistance();
  unsigned char* dstr = floatToUChar(d, 0);
  U0putstr(dstr);
  U0putstrln("mm");
  delay(1);*/

  while (U0kbhit()==0){}; // wait for RDA = true
  signed int speed = U0getint();
  moto.setSpeed(speed);
}

unsigned char* floatToUChar(float value, int decimals) {
  static unsigned char buffer[20];
  dtostrf(value, 0, decimals, (char*)buffer);
  return buffer;
}
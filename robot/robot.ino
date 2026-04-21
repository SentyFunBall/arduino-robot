#include "uart.h"
#include "ultrasonic.h"

Ultrasonic sensor(9, 10);

void setup() {
  U0init(9600);
}

void loop() {
  U0putstr("Distance: ");
  float d = sensor.getDistance();
  unsigned char* dstr = floatToUChar(d, 0);
  U0putstr(dstr);
  U0putstrln("mm");
  delay(1);
}

unsigned char* floatToUChar(float value, int decimals) {
  static unsigned char buffer[20];
  dtostrf(value, 0, decimals, (char*)buffer);
  return buffer;
}
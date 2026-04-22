#include "uart.h"
#include "ultrasonic.h"
#include "motor.h"
#include "led.h"
#include "button.h"

#include "LiquidCrystal.h"

Ultrasonic sensor(9, 10);
Motor moto(4, 3, 2);
LED led(11);
Button btn(12);
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

void setup() {
  U0init(9600);
  moto.off();
  moto.setDirection(1);
  lcd.begin(16, 2);
}

void loop() {
  /*U0putstr("Distance: ");
  float d = sensor.getDistance();
  unsigned char* dstr = floatToUChar(d, 0);

  int speed = clamp(d, 0, 255);
  U0putstrln(floatToUChar(float(speed), 0));
  //moto.setSpeed(speed);
  delay(100);*/
  /*if (btn.isPressedPulse()) {
    led.Toggle();
    //U0putstrln("pressed");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  if (btn.isPressed()) {
    lcd.print("pressed");
  } else {
    lcd.print("not lol");
  }*/

  float d = sensor.getDistance();
  unsigned char* dstr = floatToUChar(d, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print((char*)dstr);
  lcd.print("mm");
  if (d < 60) {
    led.On();
  } else {
    led.Off();
  }

  delay(100);
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
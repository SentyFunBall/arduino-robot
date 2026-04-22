#include "uart.h"
#include "ultrasonic.h"
#include "motor.h"
#include "led.h"
#include "button.h"

#include "LiquidCrystal.h"
#include "RTClib.h"

Ultrasonic sensor(9, 10);
Motor motoR(4, 3, 2);
Motor motoL(6, 7, 5);
//LED led(11);
//Button btn(12);
//LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  U0init(9600);
  motoR.off();
  motoR.setDirection(1);
  motoL.off();
  motoL.setDirection(1);
  //lcd.begin(16, 2);

  rtc.begin();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
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

  /*float d = sensor.getDistance();
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
  }*/

    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days, 12 hours, 30 minutes, and 6 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

    Serial.println();
    delay(3000);

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
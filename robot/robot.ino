#include "uart.h"
#include "ultrasonic.h"
#include "motor.h"
#include "led.h"
#include "button.h"

#include "LiquidCrystal.h"
#include "RTClib.h"

volatile unsigned char* myEIFR  = (unsigned char*) 0x3C;
volatile unsigned char* myEICRA = (unsigned char*) 0x69;
volatile unsigned char* myEICRB = (unsigned char*) 0x6A;
volatile unsigned char* myEIMSK = (unsigned char*) 0x3D;

Ultrasonic luss(23, 25);
Ultrasonic russ(27, 29);
Motor motoL(7, 6, 5);
Motor motoR(10, 9, 8);
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);
Pin pwr(4, OUTPUT);

LED redled(40);
LED yelled(38);
LED greled(36);
LED bluled(34);

Button srtbtn(2);
Button resbtn(46);
Button offbtn(44);
Button gobtn(42);

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

volatile int state = 0; // 0 = off, 1 = idle, 2 = wander
long unsigned int accumulator = 0;
long unsigned int oldMillis = 0;
long unsigned int curMillis = 0;
long unsigned int oneMinute = 0;
int minuteTimer = 30;

volatile uint8_t pressed = 0;

int actionTimer = 0;
int actionSetter = 30; // number of ticks between actions
int turnTimer = 0;
int turnSetter = 13;

bool completedPeriphSetup = false;

void setupPeriphs() {
  rtc.begin();
  lcd.begin(16, 2);
  lcd.clear();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  printRTC();

  motoR.off();
  motoR.setDirection(1);
  motoL.off();
  motoL.setDirection(-1);
  
  completedPeriphSetup = true;
}

void printRTC() {
  DateTime now = rtc.now();

  U0putint(now.year());
  U0putchar('/');
  U0putint(now.month());
  U0putchar('/');
  U0putint(now.day());
  U0putstr(" (");
  U0putstr(daysOfTheWeek[now.dayOfTheWeek()]);
  U0putstr(") ");
  U0putint(now.hour());
  U0putchar(':');
  U0putint(now.minute());
  U0putchar(':');
  U0putint(now.second());
  U0putchar('\n');
}

void setup() {
  U0init(9600);
  motoR.off();
  motoR.setDirection(1);
  motoL.off();
  motoL.setDirection(-1);
  pwr.write(LOW);

  *myEIFR = 0b00010000;
  *myEICRA = 0b00000000;
  *myEICRB = 0b00000010;
  *myEIMSK = 0b00010000;
  sei();
}

int rolledLDist = 0;
int rolledRDist = 0;

void loop() {
  curMillis = millis();
  accumulator += curMillis - oldMillis;
  oneMinute += curMillis - oldMillis;
  lcd.setCursor(0, 0);

  if (offbtn.isPressed()) {
    motoR.setSpeed(0);
    motoL.setSpeed(0);
    completedPeriphSetup = false;

    state = 0;
    lcd.clear();
  }

  if (resbtn.isPressed()) {
    motoR.setSpeed(0);
    motoL.setSpeed(0);

    state = 1;
    lcd.clear();
  }

  switch(state) {
  case 0: {
    pwr.write(LOW);
    redled.Off();
    bluled.Off();
    greled.Off();
    yelled.Off();
    rolledRDist = rolledLDist = 0;
    while(1) {
      if (pressed) {
        pressed = 0;
        state = 1; // start
        lcd.clear();
        break;
      }
    }
    break;
  }

  case 1: {
    pwr.write(HIGH);

    if (!completedPeriphSetup) {
      setupPeriphs();
    }

    if (gobtn.isPressed()) {
      state = 2;
      lcd.clear();
    }

    lcd.print("State: Idle");

    redled.Off();
    bluled.On();
    greled.Off();
    yelled.Off();
    break;
  }

  case 2: {
    if (accumulator > 100) {
      accumulator = 0;
      float lDist = luss.getDistance();
      float rDist = russ.getDistance();

      if (rDist == 0 || lDist == 0) {
        state = 4;
        lcd.clear();
        break;
      }

      rolledLDist = rolledLDist - (rolledLDist / 2) + (int)lDist / 2;
      rolledRDist = rolledRDist - (rolledRDist / 2) + (int)rDist / 2;
      rolledLDist = clamp(rolledLDist, 0, 500);
      rolledRDist = clamp(rolledRDist, 0, 500);

      redled.Off();
      bluled.Off();
      greled.On();
      yelled.Off();

      if (oneMinute > 60000) {
        oneMinute = 0;
        minuteTimer = 30;
      }
      if (minuteTimer-- > 0) {
        lcd.print("State: Wandering");
        lcd.setCursor(0, 1);
        lcd.print("LD: ");
        lcd.print(rolledLDist);
        lcd.setCursor(8, 1);
        lcd.print(" RD: ");
        lcd.print(rolledRDist);
      } else {
        lcd.clear();
        lcd.print("State: Wandering");
      }

      if (rolledLDist < 200 || rolledRDist < 200) {
        motoR.setSpeed(0);
        motoL.setSpeed(0);
        lcd.clear();
        state = 3;
        turnTimer = turnSetter;
        break;
      }

      if (actionTimer-- <= 0) {
        unsigned long m = millis();
        int rand = random(255);
        if (rand < 40) { // left
          motoR.setSpeed(250);
          motoL.setSpeed(200);
        } else if (rand < 80) { // right
          motoR.setSpeed(200);
          motoL.setSpeed(250);
        } else { // forward
          motoR.setSpeed(255);
          motoL.setSpeed(255);
        }
      }
    }
    break;
  }

  case 3: {
    if (accumulator > 100) {
      accumulator = 0;
      lcd.print("State: Avoiding");

      redled.Off();
      bluled.Off();
      greled.Off();
      yelled.On();

      if (turnTimer > 0) {
        turnTimer--;
        if (rolledLDist < rolledRDist) {
          // turn right
          motoR.setDirection(-1);
          motoL.setDirection(-1);
          motoR.setSpeed(255);
          motoL.setSpeed(255);
          lcd.setCursor(0, 1);
          lcd.print("Mv: Right");
        } else {
          // turn left
          motoR.setDirection(1);
          motoL.setDirection(1);
          motoR.setSpeed(255);
          motoL.setSpeed(255);
          lcd.setCursor(0, 1);
          lcd.print("Mv: Left");
        }
      } else {
        // back to forward drive
        state = 2;
        lcd.clear();
        motoR.setDirection(1);
        motoL.setDirection(-1);
      }
    }
    break;
  }

  case 4: {
    lcd.print("ERROR");
    motoR.off();
    motoL.off();

    redled.On();
    bluled.Off();
    greled.Off();
    yelled.Off();
  }
  }

  oldMillis = curMillis;
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

int clamp(int v, int min, int max) {
  if (v < min) return min;
  if (v > max) return max;
  return v;
}

ISR(INT4_vect) {
  pressed = 1;
}

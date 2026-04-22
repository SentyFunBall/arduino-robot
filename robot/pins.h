#ifndef PINS_H
#define PINS_H

#define INPUT 0
#define OUTPUT 1
#define PULL_UP 2

#define LOW 0
#define HIGH 1

struct PinMap {
  volatile unsigned char* ddr;
  volatile unsigned char* port;
  volatile unsigned char* pin;
  unsigned char bitMask;
};

// :skull: don't even bother
static PinMap pinMap[] = {
  // D0-D7
  { (volatile unsigned char*)0x2D, (volatile unsigned char*)0x2E, (volatile unsigned char*)0x2C, (unsigned char)(1 << 0) }, // D0  -> PE0
  { (volatile unsigned char*)0x2D, (volatile unsigned char*)0x2E, (volatile unsigned char*)0x2C, (unsigned char)(1 << 1) }, // D1  -> PE1
  { (volatile unsigned char*)0x2D, (volatile unsigned char*)0x2E, (volatile unsigned char*)0x2C, (unsigned char)(1 << 4) }, // D2  -> PE4
  { (volatile unsigned char*)0x2D, (volatile unsigned char*)0x2E, (volatile unsigned char*)0x2C, (unsigned char)(1 << 5) }, // D3  -> PE5
  { (volatile unsigned char*)0x33, (volatile unsigned char*)0x34, (volatile unsigned char*)0x32, (unsigned char)(1 << 5) }, // D4  -> PG5
  { (volatile unsigned char*)0x2D, (volatile unsigned char*)0x2E, (volatile unsigned char*)0x2C, (unsigned char)(1 << 3) }, // D5  -> PE3
  { (volatile unsigned char*)0x101, (volatile unsigned char*)0x102, (volatile unsigned char*)0x100, (unsigned char)(1 << 3) }, // D6  -> PH3
  { (volatile unsigned char*)0x101, (volatile unsigned char*)0x102, (volatile unsigned char*)0x100, (unsigned char)(1 << 4) }, // D7  -> PH4

  // D8-D15
  { (volatile unsigned char*)0x101, (volatile unsigned char*)0x102, (volatile unsigned char*)0x100, (unsigned char)(1 << 5) }, // D8  -> PH5
  { (volatile unsigned char*)0x101, (volatile unsigned char*)0x102, (volatile unsigned char*)0x100, (unsigned char)(1 << 6) }, // D9  -> PH6
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 4) }, // D10 -> PB4
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 5) }, // D11 -> PB5
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 6) }, // D12 -> PB6
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 7) }, // D13 -> PB7
  { (volatile unsigned char*)0x104, (volatile unsigned char*)0x105, (volatile unsigned char*)0x103, (unsigned char)(1 << 1) }, // D14 -> PJ1
  { (volatile unsigned char*)0x104, (volatile unsigned char*)0x105, (volatile unsigned char*)0x103, (unsigned char)(1 << 0) }, // D15 -> PJ0

  // D16-D23
  { (volatile unsigned char*)0x101, (volatile unsigned char*)0x102, (volatile unsigned char*)0x100, (unsigned char)(1 << 1) }, // D16 -> PH1
  { (volatile unsigned char*)0x101, (volatile unsigned char*)0x102, (volatile unsigned char*)0x100, (unsigned char)(1 << 0) }, // D17 -> PH0
  { (volatile unsigned char*)0x2A, (volatile unsigned char*)0x2B, (volatile unsigned char*)0x29, (unsigned char)(1 << 3) }, // D18 -> PD3
  { (volatile unsigned char*)0x2A, (volatile unsigned char*)0x2B, (volatile unsigned char*)0x29, (unsigned char)(1 << 2) }, // D19 -> PD2
  { (volatile unsigned char*)0x2A, (volatile unsigned char*)0x2B, (volatile unsigned char*)0x29, (unsigned char)(1 << 1) }, // D20 -> PD1
  { (volatile unsigned char*)0x2A, (volatile unsigned char*)0x2B, (volatile unsigned char*)0x29, (unsigned char)(1 << 0) }, // D21 -> PD0
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 0) }, // D22 -> PA0
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 1) }, // D23 -> PA1

  // D24-D31
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 2) }, // D24 -> PA2
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 3) }, // D25 -> PA3
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 4) }, // D26 -> PA4
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 5) }, // D27 -> PA5
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 6) }, // D28 -> PA6
  { (volatile unsigned char*)0x21, (volatile unsigned char*)0x22, (volatile unsigned char*)0x20, (unsigned char)(1 << 7) }, // D29 -> PA7
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 7) }, // D30 -> PC7
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 6) }, // D31 -> PC6

  // D32-D39
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 5) }, // D32 -> PC5
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 4) }, // D33 -> PC4
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 3) }, // D34 -> PC3
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 2) }, // D35 -> PC2
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 1) }, // D36 -> PC1
  { (volatile unsigned char*)0x27, (volatile unsigned char*)0x28, (volatile unsigned char*)0x26, (unsigned char)(1 << 0) }, // D37 -> PC0
  { (volatile unsigned char*)0x2A, (volatile unsigned char*)0x2B, (volatile unsigned char*)0x29, (unsigned char)(1 << 7) }, // D38 -> PD7
  { (volatile unsigned char*)0x33, (volatile unsigned char*)0x34, (volatile unsigned char*)0x32, (unsigned char)(1 << 2) }, // D39 -> PG2

  // D40-D47
  { (volatile unsigned char*)0x33, (volatile unsigned char*)0x34, (volatile unsigned char*)0x32, (unsigned char)(1 << 1) }, // D40 -> PG1
  { (volatile unsigned char*)0x33, (volatile unsigned char*)0x34, (volatile unsigned char*)0x32, (unsigned char)(1 << 0) }, // D41 -> PG0
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 7) }, // D42 -> PL7
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 6) }, // D43 -> PL6
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 5) }, // D44 -> PL5
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 4) }, // D45 -> PL4
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 3) }, // D46 -> PL3
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 2) }, // D47 -> PL2

  // D48-D53
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 1) }, // D48 -> PL1
  { (volatile unsigned char*)0x10A, (volatile unsigned char*)0x10B, (volatile unsigned char*)0x109, (unsigned char)(1 << 0) }, // D49 -> PL0
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 3) }, // D50 -> PB3
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 2) }, // D51 -> PB2
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 1) }, // D52 -> PB1
  { (volatile unsigned char*)0x24, (volatile unsigned char*)0x25, (volatile unsigned char*)0x23, (unsigned char)(1 << 0) }, // D53 -> PB0
};

class Pin {
  public:
    int pinnum;
    Pin(int num, int mode) {
      ddr = pinMap[num].ddr;
      port = pinMap[num].port;
      pin = pinMap[num].pin;
      bitMask = pinMap[num].bitMask;
      pinnum = num;

      this->mode(mode);
    }

    Pin() {}

    void write(int value) {
      if (value == HIGH)
        *port |= bitMask;
      else
        *port &= ~bitMask;
    }

    int read() {
      return (*pin & bitMask) ? HIGH : LOW;
    }

    void mode(int mode) {
      if (mode == OUTPUT) {
        *ddr |= bitMask;
      } else if (mode == INPUT) {
        *ddr &= ~bitMask;
        *port &= ~bitMask;
      } else if (mode == PULL_UP) {
        *ddr &= ~bitMask;
        *port |= bitMask;
      }
    }
  private:
    volatile unsigned char* ddr;
    volatile unsigned char* port;
    volatile unsigned char* pin;
    unsigned char bitMask;
};

#endif
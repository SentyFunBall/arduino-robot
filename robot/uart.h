#ifndef UART_H
#define UART_H

#define RDA 0x80
#define TBE 0x20  

volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;

void U0init(unsigned int brate) {
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / brate - 1);
  // Same as (FCPU / (16 * U0baud)) - 1;
  *myUCSR0A = 0x20; // Start with read buffer empty and ready
  *myUCSR0B = 0x18; // Enable UDRIEn interrupts, enable reciever
  *myUCSR0C = 0x06; // Master SPI mode
  *myUBRR0  = tbaud;
}

unsigned char U0kbhit() {
  return (*myUCSR0A) & RDA; // Check RXC0 (RDA) flag
}

unsigned char U0getchar() {
  return *myUDR0; // Get data buffer, also causing RXC0 reset
}

void U0putchar(unsigned char* U0pdata) {
  //*myUCSR0B = 0x48; // Enable trasmit interrupts, and enable transmitter
  while (!(*myUCSR0A & 0x20)); // Check TXC0 flag and wait for it to be set
  *myUDR0 = U0pdata;
}

void U0putstr(unsigned char* str) {
  while (*str) {
    U0putchar(*str);
    str++;
  }
}

void U0putint(unsigned short n) {
  char buf[5] = {'0'};
  char max = 0;
  for (char i = 0; n;i++) {
    char digit = n % 10;
    n /= 10;
    buf[i] = '0' + digit;
    if (digit > 0)
      max = i;
  }
  for (char i = max; i >= 0; i--)
    U0putchar(buf[i]);
  //U0putchar('\n');
}

void U0putstrln(unsigned char* str) {
  while (*str) {
    U0putchar(*str);
    str++;
  }
  U0putchar('\n');
}

int U0getint() {
  char buffer[16];
  int index = 0;

  while (1) {
    char c = U0getchar();

    if (c == '\n' || c == '\r') {
      buffer[index] = '\0';
      break;
    }

    if (index < 15) {
      buffer[index++] = c;
    }
  }

  return atoi(buffer);
}

#endif

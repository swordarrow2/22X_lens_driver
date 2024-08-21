#include "system_config.h"

#include "intrins.h"

#define FOSC 11059200UL
#define BRT (65536 - FOSC / 115200 / 4)

sbit m1a1 = P2 ^ 1;
sbit m1a2 = P2 ^ 0;
sbit m1b1 = P2 ^ 3;
sbit m1b2 = P2 ^ 2;

sbit m2a1 = P1 ^ 0;
sbit m2a2 = P1 ^ 4;
sbit m2b1 = P1 ^ 6;
sbit m2b2 = P1 ^ 3;

sbit ap_ap = P2 ^ 4;
sbit ap_an = P2 ^ 5;
sbit ap_bp = P2 ^ 6;
sbit ap_bn = P2 ^ 7;

sbit filterP = P0 ^ 0;
sbit filterN = P0 ^ 1;
sbit UnuseP = P0 ^ 2;
sbit UnuseN = P0 ^ 3;

sbit servo6 = P3 ^ 2;
sbit servo7 = P3 ^ 3;
sbit servo8 = P3 ^ 7;

sbit limit1 = P1 ^ 1;
sbit limit2 = P1 ^ 3;

bit busy = 0;

char focus1 = 0;
char focus2 = 0;
char filter = 0;

void UartIsr() interrupt 4 {
  if (TI) {
    TI = 0;
    busy = 0;
  }
  if (RI) {
    RI = 0;
    switch (SBUF) {
    case 1:
      focus1 = 1;
      break;
    case 2:
      focus1 = 2;
      break;
    case 3:
      focus2 = 1;
      break;
    case 4:
      focus2 = 2;
      break;
    case 5:
      filter = 1;
      break;
    case 6:
      filter = 2;
      break;
    default:
      break;
    }
  }
}

void UartInit() {
  SCON = 0x50;
  TMOD = 0x00;
  TL1 = BRT;
  TH1 = BRT >> 8;
  TR1 = 1;
  AUXR = 0x40;
  busy = 0;
}

void UartSend(char dat) {
  while (busy)
    ;
  busy = 1;
  SBUF = dat;
}

void Delay100ms(void) { //@11.0592MHz
  unsigned char data i, j, k;
  _nop_();
  i = 2;
  j = 1;
  k = 1;
  do {
    do {
      while (--k)
        ;
    } while (--j);
  } while (--i);
}

void moto1Far(void) {
  m1a1 = 1;
  Delay100ms();
  m1a1 = 0;
  m1b1 = 1;
  Delay100ms();
  m1b1 = 0;
  m1a2 = 1;
  Delay100ms();
  m1a2 = 0;
  m1b2 = 1;
  Delay100ms();
  m1b2 = 0;
}
void moto1Close(void) {
  m1a1 = 1;
  Delay100ms();
  m1a1 = 0;
  m1b2 = 1;
  Delay100ms();
  m1b2 = 0;
  m1a2 = 1;
  Delay100ms();
  m1a2 = 0;
  m1b1 = 1;
  Delay100ms();
  m1b1 = 0;
}
void moto2Close(void) {
  m2a1 = 1;
  Delay100ms();
  m2a1 = 0;
  m2b1 = 1;
  Delay100ms();
  m2b1 = 0;
  m2a2 = 1;
  Delay100ms();
  m2a2 = 0;
  m2b2 = 1;
  Delay100ms();
  m2b2 = 0;
}
void moto2Far(void) {
  m2a1 = 1;
  Delay100ms();
  m2a1 = 0;
  m2b2 = 1;
  Delay100ms();
  m2b2 = 0;
  m2a2 = 1;
  Delay100ms();
  m2a2 = 0;
  m2b1 = 1;
  Delay100ms();
  m2b1 = 0;
}
void openIrFilter() {
  filterP = 1;
  filterN = 0;
  Delay100ms();
  filterP = 0;
}
void closeIrFilter() {
  filterN = 1;
  filterP = 0;
  Delay100ms();
  filterN = 0;
}
int main(void) {
  int i = 0;
  unsigned char sendFlag = 0;
  int delay = 10;
  GpioInit();
  limit1 = 1;
  limit2 = 1;
  UartInit(); // 串口初始化
  ES = 1;
  EA = 1;
  while (1) {

    if (!sendFlag++) {
      UartSend(0x5A);
      UartSend(focus1);
      UartSend(focus2);
      UartSend(limit1);
      UartSend(limit2);
      UartSend(filter);
      UartSend(0xA5);
    }

    if (1 == limit1) {
    }
    if (1 == limit2) {
    }
    if (1 == filter) {
      openIrFilter();
      filter = 0;
    }
    if (2 == filter) {
      closeIrFilter();
      filter = 0;
    }

    if (1 == focus1) {
      for (i = 0; i < 1; i++) {
        moto1Far();
      }
      focus1 = 0;
    }

    if (2 == focus1) {
      for (i = 0; i < 1; i++) {
        moto1Close();
      }
      focus1 = 0;
    }

    if (1 == focus2) {
      for (i = 0; i < 1; i++) {
        moto2Close();
      }
      focus2 = 0;
    }
    if (2 == focus2) {
      for (i = 0; i < 1; i++) {
        moto2Far();
      }
      focus2 = 0;
    }
    // UartSend(vcc >> 8);                         //输出电压值到串口
    // UartSend(vcc);
  }
}

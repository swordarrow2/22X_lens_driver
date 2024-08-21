#include "motor_driver.h"
#include "intrins.h"
#include "stc8h.h"
#include "system_config.h"

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

void Delay_unit_ms(void) {
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
  Delay_unit_ms();
  m1a1 = 0;
  m1b1 = 1;
  Delay_unit_ms();
  m1b1 = 0;
  m1a2 = 1;
  Delay_unit_ms();
  m1a2 = 0;
  m1b2 = 1;
  Delay_unit_ms();
  m1b2 = 0;
}

void moto1Close(void) {
  m1a1 = 1;
  Delay_unit_ms();
  m1a1 = 0;
  m1b2 = 1;
  Delay_unit_ms();
  m1b2 = 0;
  m1a2 = 1;
  Delay_unit_ms();
  m1a2 = 0;
  m1b1 = 1;
  Delay_unit_ms();
  m1b1 = 0;
}

void moto2Far(void) {
  m2a1 = 1;
  Delay_unit_ms();
  m2a1 = 0;
  m2b2 = 1;
  Delay_unit_ms();
  m2b2 = 0;
  m2a2 = 1;
  Delay_unit_ms();
  m2a2 = 0;
  m2b1 = 1;
  Delay_unit_ms();
  m2b1 = 0;
}

void moto2Close(void) {
  m2a1 = 1;
  Delay_unit_ms();
  m2a1 = 0;
  m2b1 = 1;
  Delay_unit_ms();
  m2b1 = 0;
  m2a2 = 1;
  Delay_unit_ms();
  m2a2 = 0;
  m2b2 = 1;
  Delay_unit_ms();
  m2b2 = 0;
}

void openIrFilter(void) {
  filterP = 1;
  filterN = 0;
  Delay_unit_ms();
  filterP = 0;
}

void closeIrFilter(void) {
  filterN = 1;
  filterP = 0;
  Delay_unit_ms();
  filterN = 0;
}

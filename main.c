#include "system_config.h"

#include "intrins.h"
#include "motor_driver.h"
#include "system_uart.h"

char focus1 = 0;
char focus2 = 0;
char filter = 0;

extern bit busy;
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

int main(void) {
  int i = 0;
  unsigned char sendFlag = 0;
  int delay = 10;
  GpioInit();
  UartInit();
  ES = 1;
  EA = 1;
  while (1) {

    if (!sendFlag++) {
      UartSend(0x5A);
      UartSend(focus1);
      UartSend(focus2);
      UartSend(filter);
      UartSend(0xA5);
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

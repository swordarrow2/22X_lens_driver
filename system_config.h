
#ifndef __SYSTEM_CONFIG__
#define __SYSTEM_CONFIG__

#include "stc8h.h"

#define FOSC 11059200UL
#define BRT (65536 - FOSC / 115200 / 4)

void GpioInit(void);

#endif

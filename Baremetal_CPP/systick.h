// systick.h

#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f4xx.h"

void SBL_SysTickInit(void);
void SBL_DelayMs(volatile int Delay);

#endif
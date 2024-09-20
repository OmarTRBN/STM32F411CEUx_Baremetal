// systick.c

#include "systick.h"

#define SYSTICK_MS_LOAD_VALUE 16000 // Reload value for 1ms delay (16Mhz/1000)
#define SYSTICK_CTRL_ENABLE (1<<0)
#define SYSTICK_CTRL_INTERNAL_CLK_SRC (1<<2)
#define SYSTICK_CTRL_COUNTFLAG (1<<16)

void systickDelayMs(int delay)
{
	SysTick->LOAD = SYSTICK_MS_LOAD_VALUE;
	SysTick->VAL = 0; // Clear RVR
	SysTick->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_INTERNAL_CLK_SRC;
	
	for (int i=0; i<delay; i++)
	{
		while((SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG) == 0);
	}
	
	SysTick->CTRL = 0;
}
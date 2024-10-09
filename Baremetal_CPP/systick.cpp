// systick.cpp

#include "systick.h"

#define SYSTICK_CTRL_ENABLE (1 << 0)
#define SYSTICK_CTRL_TICKINT (1 << 1)
#define SYSTICK_CTRL_INTERNAL_CLK_SRC (1 << 2)
#define SYSTICK_CTRL_COUNTFLAG (1 << 16)

// User functions
void SBL_SysTickInit(void) {
    // Set SysTick reload value for 1 ms
		uint32_t sysclk = SystemCoreClock;  // SystemCoreClock is automatically updated
    uint32_t systick_load_value = (sysclk / 1000) - 1;
    SysTick->LOAD = systick_load_value;
    
    SysTick->VAL = 0; // Clear current value register (VAL)

    // Enable SysTick with internal clock source, but without enabling interrupts
    SysTick->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_INTERNAL_CLK_SRC;
}

void SBL_DelayMs(volatile int Delay) {
	SysTick->VAL = 0; // Ensure SysTick starts counting from zero

	for (volatile int i = 0; i < Delay; i++) {
			// Wait until COUNTFLAG is set, indicating 1 ms has passed
		while ((SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG) == 0);
	}
}
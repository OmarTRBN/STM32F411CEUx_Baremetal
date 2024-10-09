// main.cpp

#include "sbl_drivers.h"

void delay(volatile uint32_t count) {
    while (count--);
		// delay(1000000);

}

#define LEDPIN PC13

int main()
{
	SBL_InitTimer(TIM2, 160, 2000);
	SBL_InitTimer(TIM5, 160, 2000);
	SBL_SetChannelMode(TIM2, 3, PWM_MODE_1, PA2, GPIO_SPEED_HIGH, AF1);
	SBL_SetChannelMode(TIM5, 1, PWM_MODE_1, PA0, GPIO_SPEED_HIGH, AF2);
	
	SBL_PinMode(LEDPIN, OUTPUT);
	while(1)
	{
		SBL_DutyCycle(TIM2, 3, 25);
		SBL_DutyCycle(TIM5, 1, 25);
		delay(1000000);
		delay(1000000);
		delay(1000000);
		SBL_DutyCycle(TIM2, 3, 50);
		SBL_DutyCycle(TIM5, 1, 50);
		delay(1000000);
		delay(1000000);
		delay(1000000);
		SBL_DutyCycle(TIM2, 3, 75);
		SBL_DutyCycle(TIM5, 1, 75);
		delay(1000000);
		delay(1000000);
		delay(1000000);
	}
}


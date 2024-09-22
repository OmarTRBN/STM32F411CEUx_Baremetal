// main.c

#include "stm32f4xx.h"
#include "stm32_omar.h"

#define LEDPIN PC13

int main(void)
{
	pinMode(LEDPIN, OUTPUT);
	
	initTim2();
	
	while (1)
	{
		while(!(TIM2->SR & TIM2_SR_UIF));
		
		TIM2->SR &= ~(TIM2_SR_UIF);
	  togglePin(PC13);
	}
}
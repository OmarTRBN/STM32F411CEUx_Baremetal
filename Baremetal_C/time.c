// time.c

#include "time.h"
// 16 000 000 / (16 000 * 1000)
// So for 1Hz 
// PSC = 1600 - 1
// ARR = 10000 - 1
void initTim2()
{
	RCC->APB1ENR |= RCC_APB1_TIM2_EN;
	
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM2_CR1_CEN;
}
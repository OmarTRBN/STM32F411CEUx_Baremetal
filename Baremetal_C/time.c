// time.c

#include "time.h"
// 16 000 000 / (16 000 * 1000)
// So for 1Hz 
// PSC = 1600 - 1
// ARR = 10000 - 1
void initTim2(){
	RCC->APB1ENR |= RCC_APB1_TIM2_EN;
	
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM2_CR1_CEN;
}

void tim2_pa5_output_compare()
{
	RCC->AHB1ENR |= 0b1<<0; // Enable GPIOA
	RCC->APB1ENR |= RCC_APB1_TIM2_EN;
	
	GPIOA->MODER &= ~(0b1 << 10);
	GPIOA->MODER |= (0b1 << 11);
	
	GPIOA->AFR[0] &= ~(0b1111 << 20);
	GPIOA->AFR[0] |= 0b0001 << 20;
	
	TIM2->PSC = 1600-1;
	TIM2->ARR = 2500-1;
	
	TIM2->CCMR1 &= ~(0b111 << 4);
	TIM2->CCMR1 |= TIM2_CCMR1_OC1M_TOGGLE;
	
	TIM2->CCER |= TIM2_CCER_CC1E;
	
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM2_CR1_CEN;
}



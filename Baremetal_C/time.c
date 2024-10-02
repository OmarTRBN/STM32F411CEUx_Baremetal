// time.c

#include "time.h"
// 16 000 000 / (1600 * 10000)
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
	
	TIM2->PSC = 160-1;
	TIM2->ARR = 2000-1;
	
	TIM2->CCMR1 &= ~(0b111 << 4);
	TIM2->CCMR1 |= TIM2_CCMR1_OC1M_TOGGLE;
	
	TIM2->CCER |= TIM2_CCER_CC1E;
	
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM2_CR1_CEN;
}

void SBL_TIM2_PA1_PWM()
{
	// PA1 is TIM2_CH2
	RCC->AHB1ENR |= 0b1<<0; // Enable GPIOA
	RCC->APB1ENR |= RCC_APB1_TIM2_EN; // Enable TIM2 peripheral clock

	// Set PA1 to AF mode (10) and AF01 (0001)
	GPIOA->MODER &= ~(0b1 << 2); // Clear bit 2
	GPIOA->MODER |= (0b1 << 3); // Set bit 3 to 1
	GPIOA->AFR[0] &= ~(0b1111 << 4); // Clear bits 4-7
	GPIOA->AFR[0] |= 0b0001 << 4; // Set bits 4-7 to 0b0001
	
	TIM2->PSC = 160-1;
	TIM2->ARR = 2000-1;
	
	TIM2->CCMR1 &= ~(0b111 << 12); // Clear bits 12-14
	TIM2->CCMR1 |= (0b110 << 12); // Set PWM mode 1 (0b110)
	
	TIM2->CCER |= (0b1 << 4); // Capture/compare 2 output enable
	
	TIM2->CCR2 = 499;
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM2_CR1_CEN; // Enable counter
}

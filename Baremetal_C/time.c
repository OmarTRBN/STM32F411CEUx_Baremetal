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

int tim2_set_frequency(uint32_t desired_frequency, uint32_t timer_clock_frequency){
	if (desired_frequency > MAX_DES_FREQ)
	{
		return 0;
	}
	else
	{
		uint32_t psc = 0;
		
    // Calculate PSC based on the desired frequency and fixed ARR
    psc = (timer_clock_frequency / (desired_frequency * (ARR_VALUE + 1))) - 1;
		
		// Stop Timer
		TIM2->CR1 &= ~TIM_CR1_CEN;

    // Set the timer configuration
    TIM2->PSC = psc;

    // Reset counter and enable timer
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;

    return 1; // Successfully set the frequency
	}
}

void tim2_pa5_output_compare(){
	RCC->AHB1ENR |= 0b1<<0; // Enable GPIOA
	RCC->APB1ENR |= RCC_APB1_TIM2_EN;
	
	GPIOA->MODER &= ~(0b1 << 10);
	GPIOA->MODER |= (0b1 << 11);
	
	GPIOA->AFR[0] &= ~(0b1111 << 20);
	GPIOA->AFR[0] |= 0b0001 << 20;
	
	GPIOA->OSPEEDR |= (0b11 << 10); // Set high-speed mode for PA5
	
	TIM2->PSC = 16-1;
	TIM2->ARR = ARR_VALUE;
	
	TIM2->CCMR1 &= ~(0b111 << 4);
	TIM2->CCMR1 |= TIM2_CCMR1_OC1M_TOGGLE; // Set mode to toggle
	
	TIM2->CCER |= TIM2_CCER_CC1E; // Capture enable
	
	TIM2->CNT = 0; // Reset count value
	TIM2->CR1 |= TIM2_CR1_CEN; // Start counter
}

void SBL_TIM2_PA1_PWM(){
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

void SBL_TIM2_SetDutyCycle(uint8_t dutyCycle){
    // Ensure duty cycle is between 0 and 100%
    if(dutyCycle > 100) dutyCycle = 100;

    // Calculate and set CCR2 value based on duty cycle and ARR value
    TIM2->CCR2 = (TIM2->ARR + 1) * dutyCycle / 100;
}
void initTim2Interrupt(){
	RCC->APB1ENR |= RCC_APB1_TIM2_EN;
	
	TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	
	TIM2->CNT = 0;
	TIM2->CR1 |= TIM2_CR1_CEN;
	
	TIM2->DIER |= DIER_UIE;
	
	NVIC_EnableIRQ(TIM2_IRQn);
}
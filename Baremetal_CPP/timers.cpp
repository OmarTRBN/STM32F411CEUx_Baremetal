// timers.cpp

#include "timers.h"

// Useful functions
static void EnableTimerClock(TIM_TypeDef* TIMx) {
    uint32_t tmask = 0;
    __IO uint32_t *pRCC_ENR;

    if ((uint32_t)TIMx >= APB2PERIPH_BASE) {
        pRCC_ENR = &RCC->APB2ENR;
        tmask = 1 << (((uint32_t)TIMx - APB2PERIPH_BASE) >> 10);
    } else {
        pRCC_ENR = &RCC->APB1ENR;
        tmask = 1 << (((uint32_t)TIMx - APB1PERIPH_BASE) >> 10);
    }

    *pRCC_ENR |= tmask;
}

// TIMx functions
void SBL_InitTimer(TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t Period){
	if (TIMx == TIM1){
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	else if (TIMx == TIM2) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	else if (TIMx == TIM3) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
	else if (TIMx == TIM4) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	else if (TIMx == TIM5) {
			RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	}

	TIMx->PSC = Prescaler;
	TIMx->ARR = Period;
	
	TIMx->CNT = 0;
}
void SBL_StartTimer(TIM_TypeDef* TIMx){
	TIMx->CR1 |= TIM_CR1_CEN;
}
void SBL_StopTimer(TIM_TypeDef* TIMx){
	TIMx->CR1 &= ~TIM_CR1_CEN;
}
void SBL_ResetTimer(TIM_TypeDef* TIMx){
	TIMx->CNT = 0;
}
uint32_t SBL_GetTimerValue(TIM_TypeDef* TIMx){
	return TIMx->CNT;
}

// TIMx and channel functions
void SBL_SetChannelMode(TIM_TypeDef* TIMx, int Channel, int Mode, int Pin, int PinSpeed, int AFMode){
	SBL_PinMode(Pin, ALTERNATE, PinSpeed, AFMode);
	
	switch (Channel){
		case 1:
			TIMx->CCMR1 &= ~(0x1111 << 4);
			TIMx->CCMR1 |= (Mode << 4);
			break;
		case 2:
			TIMx->CCMR1 &= ~(0x1111 << 12);
			TIMx->CCMR1 |= (Mode << 12);
			break;
		case 3:
			TIMx->CCMR2 &= ~(0x1111 << 4);
			TIMx->CCMR2 |= (Mode << 4);
			break;
		case 4:
			TIMx->CCMR2 &= ~(0x1111 << 12);
			TIMx->CCMR2 |= (Mode << 12);
			break;
	}
	
	TIMx->CCER |= (0b1 << (Channel-1)*4); // Capture/compare enable
	TIMx->CR1 |= TIM_CR1_CEN; // Enable counter
}
void SBL_DutyCycle(TIM_TypeDef* TIMx, int Channel, uint32_t DutyCycle){
	if(DutyCycle > 100) DutyCycle = 100;
	
	// TIMx->CR1 &= ~TIM_CR1_CEN;
	
	switch (Channel){
		case 1:
			TIMx->CCR1 = (TIMx->ARR + 1) * DutyCycle / 100;
			break;
		case 2:
			TIMx->CCR2 = (TIMx->ARR + 1) * DutyCycle / 100;
			break;
		case 3:
			TIMx->CCR3 = (TIMx->ARR + 1) * DutyCycle / 100;;
			break;
		case 4:
			TIMx->CCR4 = (TIMx->ARR + 1) * DutyCycle / 100;
			break;
	}
	
	// TIMx->CNT = 0;
	// TIMx->CR1 |= TIM_CR1_CEN;
}

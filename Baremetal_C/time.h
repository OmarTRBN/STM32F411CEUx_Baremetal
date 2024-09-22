// time.h

#include "stm32f4xx.h"

#define RCC_APB1_TIM2_EN 0b1 << 0
#define TIM2_CR1_CEN 0b1 << 0 // Counter enable
#define TIM2_SR_UIF 0b1 << 0
#define TIM2_CCMR1_OC1M_TOGGLE 0b011 << 4
#define TIM2_CCER_CC1E 0b1 << 0

void initTim2();
void tim2_pa5_output_compare();
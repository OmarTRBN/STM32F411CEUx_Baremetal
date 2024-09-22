// time.h

#include "stm32f4xx.h"

#define RCC_APB1_TIM2_EN 0b1 << 0
#define TIM2_CR1_CEN 0b1 << 0 // Counter enable
#define TIM2_SR_UIF 0b1 << 0

void initTim2();
// time.h

#include "stm32f4xx.h"

#define RCC_APB1_TIM2_EN 0b1 << 0
#define TIM2_CR1_CEN 0b1 << 0 // Counter enable
#define TIM2_SR_UIF 0b1 << 0
#define TIM2_CCMR1_OC1M_TOGGLE 0b011 << 4
#define TIM2_CCER_CC1E 0b1 << 0

#define ARR_VALUE 159  // Fixed ARR value
#define MAX_PSC 65535  // Maximum value for PSC
#define MAX_DES_FREQ 100000

void initTim2();
void tim2_pa5_output_compare();
int tim2_set_frequency(uint32_t desired_frequency, uint32_t timer_clock_frequency);
void SBL_TIM2_PA1_PWM();
void SBL_TIM2_SetDutyCycle(uint8_t dutyCycle);

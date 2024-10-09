// timers.h

#ifndef TIMERS_H
#define TIMERS_H

#include "stm32f4xx.h"
#include "gpio.h"

#define TOGGLE     0b011
#define PWM_MODE_1 0b110
#define PWM_MODE_2 0b111

// TIMx functions
void SBL_InitTimer(TIM_TypeDef* TIMx, uint32_t Prescaler, uint32_t Period);
void SBL_StartTimer(TIM_TypeDef* TIMx);
void SBL_StopTimer(TIM_TypeDef* TIMx);
void SBL_ResetTimer(TIM_TypeDef* TIMx);
uint32_t SBL_GetTimerValue(TIM_TypeDef* TIMx);

// TIMx and CH mode functions
void SBL_SetChannelMode(TIM_TypeDef* TIMx, int Channel, int Mode, int Pin, int PinSpeed, int AFMode);
void SBL_DutyCycle(TIM_TypeDef* TIMx, int Channel, uint32_t DutyCycle);
#endif // TIMERS_
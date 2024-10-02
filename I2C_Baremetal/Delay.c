/**
  ******************************************************************************

  Timer Setup for Delay in STM32F446RE using TIM2
  Author:   ControllersTech
  Updated:  2nd Aug 2020

  ******************************************************************************

*/

#include "Delay.h"
#include "RccConfig.h"

void TIM2Config (void)
{
    /************** STEPS TO FOLLOW *****************
    1. Enable Timer clock
    2. Set the prescaler and the ARR
    3. Enable the Timer, and wait for the update Flag to set
    ************************************************/

    // 1. Enable Timer clock
    RCC->APB1ENR |= (1<<0);  // Enable the TIM2 clock (bit 0 for TIM2 in APB1ENR)
    
    // 2. Set the prescaler and the ARR
    // With 16 MHz clock, we want a 1 MHz timer frequency for 1 µs increments.
    TIM2->PSC = 16 - 1;  // 16 MHz/16 = 1 MHz, so 1 count = 1 µs
    TIM2->ARR = 0xFFFF;  // Maximum ARR value
    
    // 3. Enable the Timer, and wait for the update Flag to set
    TIM2->CR1 |= (1<<0); // Enable the Counter
    while (!(TIM2->SR & (1<<0)));  // Wait until the update interrupt flag is set
}

void Delay_us (uint16_t us)
{
    /************** STEPS TO FOLLOW *****************
    1. RESET the Counter
    2. Wait for the Counter to reach the entered value. As each count will take 1 µs, 
         the total waiting time will be the required us delay
    ************************************************/
    TIM2->CNT = 0;  // Reset the counter
    while (TIM2->CNT < us);  // Wait until the counter reaches the desired delay
}

void Delay_ms (uint16_t ms)
{
    for (uint16_t i=0; i<ms; i++)
    {
        Delay_us (1000); // delay of 1 ms
    }
}

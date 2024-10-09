// main.c

#include "stm32f4xx.h"
#include "stm32_omar.h"

#define LEDPIN PC13
#define DIRPIN PB12
#define STEPPIN PA5
#define SYS_CLOCK 16000000

int position=0;
int dest = 10;

static void tim2_callback();

int main(void)
{
	pinMode(DIRPIN, OUTPUT);
	digitalWrite(DIRPIN, LOW);
	
	pinMode(LEDPIN, OUTPUT);
	initTim2Interrupt();
	
	while (1)
	{
		
	}
}

static void tim2_callback()
{
	togglePin(LEDPIN);
	position++;
	if (position == dest)
	{
		// Disable timer
		TIM2->CR1 &= ~TIM_CR1_CEN; // Disable the timer
	}
}

void TIM2_IRQHandler()
{
	TIM2->SR &= ~(TIM2_SR_UIF);
	tim2_callback();
}

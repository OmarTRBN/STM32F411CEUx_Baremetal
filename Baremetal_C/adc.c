// adc.c

#include "adc.h"

void PA1_adc_init(void)
{
	// Configure ADC GPIO pin
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	
	// Set mode of PA1 to analog mode
	GPIOA->MODER |= (3U<<2);
	
	// Enable clock access for ADC
	RCC->APB2ENR |= ADC1EN;
	
	// Conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	
	// Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	
	// Enable ADC module
	ADC1->CR2 |= CR2_AD0N;
}

void start_conversion(void)
{
	ADC1->CR2 |= CR2_SWSTART;
}

void start_cont_conversion(void)
{
	// Enable cont conversion
	ADC1->CR2 |= CR2_CONT;

	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void)
{
	// Wait for conversion to be complete
	while (!(ADC1->SR & SR_EOC)){}
	
	// Return converted result
	return (ADC1->DR);
}







// clock.c

#include "clock.h"

void activateMCO1(int division)
{
	// Make PA8 AF and High Speed
	RCC->AHB1ENR |= GPIOA_EN;
	GPIOA->MODER &= ~(0b11 << 16); // Clear bits
	GPIOA->MODER |= 0b10 << 16; // Set PA8 to AF
	GPIOA->OSPEEDR |= 0b11 << 16; // Set PA8 to HIGH SPEED
	GPIOA->AFR[1] &= ~(0b1111 << 0); // Clear AF selection bits for PA8
	GPIOA->AFR[1] |= 0b0000 << 0;    // Set PA8 to AF0
	
	// Configure clock source and PSC
	RCC->CFGR &= ~(0b11 << 21); // Clear MCO1 bits
	RCC->CFGR &= ~(0b111 << 24); // Clear MCO1_PRE Bits
	
	if (division < 2 || division > 5)
	{
		RCC->CFGR &= ~(0b111 << 24); // No division
	}
	else
	{
		RCC->CFGR &= ~(0b111 << 24); // Clear bits
		RCC->CFGR |= (division+2) << 24; 
	}
	
}

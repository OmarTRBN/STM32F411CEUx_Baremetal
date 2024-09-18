// main.c

#include "stm32f4xx.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"

#define LEDPIN PC13

void delay(volatile uint32_t count) {
    while (count--);
}
// delay(1000000);

int main(void)
{
	uint32_t adc_value = 0; 
	PA1_adc_init();
	start_cont_conversion();
	pinMode(LEDPIN, OUTPUT);
	
	while(1)
	{
		delay(1000000);
		adc_value = adc_read();
		if (adc_value > 2048)
		{
			digitalWrite(LEDPIN, HIGH);
		}
		else
		{
			digitalWrite(LEDPIN, LOW);
		}
		while (1)
		{
			// Do none
		}
		// togglePin(LEDPIN);
	}
    
}

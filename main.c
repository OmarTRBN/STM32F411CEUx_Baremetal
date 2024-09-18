// main.c

#include "stm32f4xx.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define LEDPIN PC13

void delay(volatile uint32_t count) {
    while (count--);
}
// delay(1000000);

int main(void)
{
	uint32_t adc_value = 0; 
	uart2_tx_init();
	char adcString[20];
	PA1_adc_init();
	start_cont_conversion();
	pinMode(LEDPIN, OUTPUT);
	
	while(1)
	{
		adc_value = adc_read();
		uint32_to_str(adc_value, adcString);
		strcat(adcString, "\r\n");
		uart2_transmit_string("ADC Value:");
		uart2_transmit_string(adcString);
	}
    
}

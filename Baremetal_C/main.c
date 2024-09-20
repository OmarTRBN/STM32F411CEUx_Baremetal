// main.c

#include "stm32f4xx.h"
#include "gpio.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define LEDPIN PC13


int main(void)
{
	
	pinMode(LEDPIN, OUTPUT);
	
	while(1)
	{
		digitalWrite(LEDPIN, HIGH);
		systickDelayMs(1000);
		digitalWrite(LEDPIN, LOW);
		systickDelayMs(1000);
	}
    
}

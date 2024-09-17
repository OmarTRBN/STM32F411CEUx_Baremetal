// main.c

#include "stm32f4xx.h"
#include "gpio.h"
#include "uart.h"

#define LEDPIN PC13

void delay(volatile uint32_t count) {
    while (count--);
}
// delay(1000000);

int main(void)
{
	uart2_tx_init();
	pinMode(LEDPIN, OUTPUT);
	
	while(1)
	{
		uart2_write_char('y');
		uart2_write_char('\r');
		uart2_write_char('\n');
		delay(1000000);
		togglePin(LEDPIN);
	}
    
}

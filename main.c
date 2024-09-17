#include "stm32f4xx.h"
#include "gpio.h"

#define LEDPIN PB10

void delay(volatile uint32_t count) {
    while (count--);
}

int main(void)
{
    pinMode(LEDPIN, OUTPUT);
		digitalWrite(LEDPIN, HIGH);


    while (1)
    {
			togglePin(LEDPIN);
			delay(1000000);
    }
}

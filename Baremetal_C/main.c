// main.c

#include "stm32f4xx.h"
#include "stm32_omar.h"

#define LEDPIN PC13
#define DIRPIN PB12
#define STEPPIN PA5
#define SYS_CLOCK 16000000
int main(void)
{
	pinMode(DIRPIN, OUTPUT);
	digitalWrite(DIRPIN, LOW);
	
	tim2_pa5_output_compare();

	while (1)
	{
		tim2_set_frequency(1600, SYS_CLOCK);
		systickDelayMs(4000);
		tim2_set_frequency(3200, SYS_CLOCK);
		systickDelayMs(4000);
		tim2_set_frequency(6400, SYS_CLOCK);
		systickDelayMs(4000);
		tim2_set_frequency(12800, SYS_CLOCK);
		systickDelayMs(4000);
	}
}
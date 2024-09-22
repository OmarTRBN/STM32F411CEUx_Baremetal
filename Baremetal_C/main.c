// main.c

#include "stm32f4xx.h"
#include "stm32_omar.h"

#define LEDPIN PC13

int main(void)
{

	tim2_pa5_output_compare();
	
	while (1)
	{
	}
}
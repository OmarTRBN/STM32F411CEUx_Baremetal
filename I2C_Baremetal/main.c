
#include "Delay.h"
#include "I2C.h"
#include "gpio.h"

int main ()
{
	TIM2Config();
	pinMode(PC13, OUTPUT);
	I2C_Config();
	
	
	while (1)
	{
		
		for (int i=0; i<8; i++)
		{
			I2C_Start();
			I2C_Address(0x4E);
			I2C_Write(1<<i);
			I2C_Stop();
			
			// if (i==1) i+=2;
			Delay_ms(50);
		}
		// togglePin(PC13);
		// Delay_ms(1000);
		
	}
}



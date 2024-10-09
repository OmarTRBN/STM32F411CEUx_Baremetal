// main.cpp

#include "sbl_drivers.h"

#define LEDPIN PC13

int main()
{
	SBL_SysTickInit();
	SBL_PinMode(LEDPIN, OUTPUT);
	
	while(1)
	{
		SBL_TogglePin(LEDPIN);
		SBL_DelayMs(1000);	
	}
}


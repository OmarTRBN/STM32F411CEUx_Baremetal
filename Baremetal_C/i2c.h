// i2c.h

#include "stm32f4xx.h"

void initI2C1();
void I2C1_byteRead(char saddr, char maddr, char *data);
void I2C_burstRead(char saddr, char maddr, int n, char *data);
void I2C_burstWrite(char saddr, char maddr, int n, char *data);
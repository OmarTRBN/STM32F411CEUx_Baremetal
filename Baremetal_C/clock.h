// clock.h

#include "stm32f4xx.h"

#define GPIOA_EN 0b1 << 0

#define MCO_DIV_1  0b000
#define MCO_DIV_2  0b100
#define MCO_DIV_3  0b101
#define MCO_DIV_4  0b110
#define MCO_DIV_5  0b111

void activateMCO1(int division);
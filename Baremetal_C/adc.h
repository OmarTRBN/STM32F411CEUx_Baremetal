// adc.h

#include "stm32f4xx.h"
#include <stdint.h>

#define GPIOAEN 			(1U<<0)
#define ADC1EN 				(1U<<8)
#define ADC_CH1 			(1U<<0)
#define ADC_SEQ_LEN_1 0x00
#define CR2_AD0N 			(1U<<0)
#define CR2_SWSTART 	(1U<<30)
#define SR_EOC        (1U<<1)
#define CR2_CONT      (1U<<1)

void PA1_adc_init(void);
void start_conversion(void);
void start_cont_conversion(void);
uint32_t adc_read(void);

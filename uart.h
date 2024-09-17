// uart.h

/* 
UART 1
PA8 -> CK
PA9 -> TX
PA10 -> RX
PA11 -> CTS
PA12 -> RTS
*/

/* 
UART 2
PA0 -> CTS
PA1 -> RTS
PA2 -> TX
PA3 -> RX
PA4 -> CK
*/

#include "stm32f4xx.h"

#define UART2EN (0b1<<17)
#define AF7 0b0111
#define AF 0b10
#define CR1_UE (0b1<<13)
#define CR1_TE (0b1<<3)
#define CR1_RE (0b1<<2)
#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define SR_TXE (0b1<<7)
#define SR_RXNE (0b1<<5)

static uint16_t compute_uart_baudrate(uint32_t periphalClk, uint32_t baudrate);
static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphalClk, uint32_t baudrate);

void uart2_write_char(int ch);
void uart2_tx_init(void);
void uart2_rxtx_init(void);
void uart2_transmit_string(char* str);
char uart2_read(void);




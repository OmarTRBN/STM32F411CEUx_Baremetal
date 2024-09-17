#include "uart.h"
#include "gpio.h"

void uart2_write_char(int ch)
{
	// Make sure transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}
	// Write to transmit data register
	USART2->DR = (ch & 0xFF); // Perform & operation to only transmit 8 bits
	
}

char uart2_read(void){
	while(!(USART2->SR & SR_RXNE)){}
	return USART2->DR;
}


void uart2_rxtx_init(){
	/********* Configure UART GPIO pins *********/
	
	// Enable clock for GPIOA
	RCC->AHB1ENR |= (0b1 << PORTA);
	
	// Set PA2 mode to AF07 (UART_TX)
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	
	GPIOA->AFR[0] |= 1U<<8;
	GPIOA->AFR[0] |= 1U<<9;
	GPIOA->AFR[0] |= 1U<<10;
	GPIOA->AFR[0] &= ~(1U<<11); 
	
	// Set PA3 mode to AF07 (UART_RX)
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);
	
	GPIOA->AFR[0] |= 1U<<12;
	GPIOA->AFR[0] |= 1U<<13;
	GPIOA->AFR[0] |= 1U<<14;
	GPIOA->AFR[0] &= ~(1U<<15); 
	
	/********* Configure UART module *********/
	// Enable clock acces
	RCC->APB1ENR |= UART2EN;
	
	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, 115200);
	
	// Configure the transfer direction
	USART2->CR1 = (CR1_TE | CR1_RE); 
	
	// Enable UART module
	USART2->CR1 |= CR1_UE; 
	
	// Flush the buffer
	for(int i = 0; i < 10; i++)
	{
			uart2_write_char('\r');
			uart2_write_char('\n');
	}
}

void uart2_tx_init(){
	/********* Configure UART GPIO pins *********/
	
	// Enable clock for GPIOA
	RCC->AHB1ENR |= (0b1 << PORTA);
	
	// Set PA2 mode to AF07 (UART_TX)
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	
	GPIOA->AFR[0] |= 1U<<8;
	GPIOA->AFR[0] |= 1U<<9;
	GPIOA->AFR[0] |= 1U<<10;
	GPIOA->AFR[0] &= ~(1U<<11); 
	
	/********* Configure UART module *********/
	// Enable clock acces
	RCC->APB1ENR |= UART2EN;
	
	// Configure baudrate
	uart_set_baudrate(USART2, APB1_CLK, 115200);
	
	// Configure the transfer direction
	USART2->CR1 = CR1_TE; // Only bit 3 will be 1
	
	// Enable UART module
	USART2->CR1 |= CR1_UE; 
	
	// Flush the buffer
	for(int i = 0; i < 10; i++)
	{
			uart2_write_char('\r');
			uart2_write_char('\n');
	}
}

void uart2_transmit_string(char* str){
    while(*str != '\0')
    {
        uart2_write_char(*str);
        str++;
    }
}

static uint16_t compute_uart_baudrate(uint32_t periphalClk, uint32_t baudrate)
{
	return ((periphalClk + (baudrate/2U))/baudrate);
}

static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphalClk, uint32_t baudrate)
{
	USARTx->BRR = compute_uart_baudrate(periphalClk, baudrate);
}
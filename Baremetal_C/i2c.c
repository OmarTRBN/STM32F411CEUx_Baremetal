// i2c.c

#include "i2c.h"

// PB8 : SCL1
// PB9 : SDA1

#define GPIOBEN_O 0b1 << 1
#define I2C1EN_O 0b1 << 21
#define I2C_100KHZ 80
#define SD_MODE_MAX_RISE_TIME 17
#define CR1_PE 0b1 << 0;

#define SR_BUSY_O 0b1 << 1
#define CR1_START_O 0b1 << 8
#define SR1_SB_O 0b1 << 0
#define SR1_ADDR 0b1 << 1
#define SR1_TXE_O 0b1 << 7
#define CR1_ACK 0b1 << 10
#define CR1_STOP_O 0b1 << 9
#define SR1_RXNE 0b1 << 6
#define SR1_BTF 0b1 << 2


void initI2C1(){
    // Enable GPIOB clock
    RCC->AHB1ENR |= GPIOBEN_O;

    // PB8 - SCL1
    // Set alternate function mode
    GPIOB->MODER &= ~(1U << 16);
    GPIOB->MODER |= 1U << 17;
    // Set alternate function type to I2C1_SCL (AF4)
    GPIOB->AFR[1] &= ~(0xF << 0);
    GPIOB->AFR[1] |= 0x4 << 0;
    // Open drain
    GPIOB->OTYPER |= (1U << 8);
    // Pull-up
    GPIOB->PUPDR |= 1U << 16;
    GPIOB->PUPDR &= ~(1U << 17);

    // PB9 - SDA1
    // Set alternate function mode
    GPIOB->MODER &= ~(1U << 18);
    GPIOB->MODER |= 1U << 19;
    // Set alternate function type to I2C1_SDA (AF4)
    GPIOB->AFR[1] &= ~(0xF << 4);
    GPIOB->AFR[1] |= 0x4 << 4;
    // Open drain
    GPIOB->OTYPER |= (1U << 9);
    // Pull-up
    GPIOB->PUPDR |= 1U << 18;
    GPIOB->PUPDR &= ~(1U << 19);

    // Enable I2C1 clock
    RCC->APB1ENR |= I2C1EN_O;

    // I2C1 reset
    I2C1->CR1 |= 0b1 << 15;
    I2C1->CR1 &= ~(0b1 << 15);

    // Set I2C1 clock frequency to 16MHz
    I2C1->CR2 = 0b1 << 4;
    I2C1->CCR = I2C_100KHZ;
    I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

    // Enable I2C1 peripheral
    I2C1->CR1 |= CR1_PE;
}

void I2C1_byteRead(char saddr, char maddr, char *data){
	volatile int tmp;
	
	while (I2C1->SR2 & SR_BUSY_O) {} // Wait until bus is free
		
	I2C1->CR1 |= CR1_START_O; // Generate start
	 
	while (! (I2C1->SR1 & (SR1_SB_O)) ){} // Wait until start flag is set
		
	I2C1->DR = saddr << 1; // Transmit slave address + write
		
	while (! (I2C1->SR1 & (SR1_ADDR)) ){} // Wait until addr flag is set
		
	tmp = I2C1->SR2; // Clear addr flag
	I2C1->DR = maddr; // Send memory address
		
	while (! (I2C1->SR1 & SR1_TXE_O) ) {} // Wait until transmitter is empty
	
	I2C1->CR1 |= CR1_START_O; // Generate restart
	while (! (I2C1->SR1 & (SR1_SB_O)) ){} // Wait until start flag is set
		
	I2C1->DR = saddr << 1 | 1; // Transmit slave address + read
	// We transmitted the slave address, now we have to read the data
	
	while (! (I2C1->SR1 & (SR1_ADDR)) ){}
		
	I2C1->CR1 &= ~(CR1_ACK); // Disable acknowledge
	tmp = I2C1->SR2; // Clear addr flag
	I2C1->CR1 |= CR1_STOP_O | CR1_ACK; // Generate stop and re-enable ACK for next transfer
	
	while (! (I2C1->SR1 & SR1_RXNE) ) {}
	*data++ = I2C1->DR;
}

void I2C_burstRead(char saddr, char maddr, int n, char *data){
	volatile int tmp;

	while (I2C1->SR2 & SR_BUSY_O) {} // Wait until bus is free
	I2C1->CR1 |= CR1_START_O;
		
	while (! (I2C1->SR1 & (SR1_SB_O)) ){} // Wait until start flag is set	
	I2C1->DR = saddr << 1; // Transmit slave address + write
	
	while (!(I2C1->SR1 & (SR1_ADDR))){}
	tmp = I2C1->SR2; // Clear addr flag
		
	while (!(I2C1->SR1 & SR1_TXE_O)) {} // Wait until transmitter is empty
	I2C1->DR = maddr; // Send memory address
		
	while (!(I2C1->SR1 & SR1_TXE_O)) {}
	I2C1->CR1 |= CR1_START_O; // Generate restart
	
	while (! (I2C1->SR1 & (SR1_SB_O)) ){} // Wait until start flag is set
	I2C1->DR = saddr << 1 | 1;
		
	while (! (I2C1->SR1 & (SR1_ADDR)) ){}
	tmp = I2C1->SR2; // Clear addr flag
	I2C1->CR1 |= (CR1_ACK); // Enable acknowledge
		
	while(n > 0U)
	{
		
		if (n==1U)
		{
			I2C1->CR1 &= ~(CR1_ACK);
			I2C1->CR1 |= CR1_STOP_O | CR1_ACK; // Generate stop and re-enable ACK for next transfer
			
			while (!(I2C1->SR1 & SR1_RXNE)){}
			*data++ = I2C1->DR;
					
			break;
		}
		else
		{
			while (!(I2C1->SR1 & SR1_RXNE)){}
			*data++ = I2C1->DR;
			n--;
		}
		
	}
}

void I2C_burstWrite(char saddr, char maddr, int n, char *data){

	volatile int tmp;

	// Start
	while (I2C1->SR2 & SR_BUSY_O) {} // Wait until bus is free
	I2C1->CR1 |= CR1_START_O;	
	while (! (I2C1->SR1 & (SR1_SB_O)) ){} // Wait until start flag is set	
	
	// Address
	I2C1->DR = saddr << 1; // Transmit slave address + write
	while (!(I2C1->SR1 & (SR1_ADDR))){}
	tmp = I2C1->SR2; // Clear addr flag
		
	// Write
	while (!(I2C1->SR1 & SR1_TXE_O)) {} // Wait until data register is empty
	I2C1->DR = maddr; // Send memory address	
	for (int i=0; i<n; i++){	
		while (!(I2C1->SR1 & SR1_TXE_O)) {} // Wait until data register is empty
		I2C1->DR = *data++;
	}
	while (!(I2C1->SR1 & SR1_BTF)) {}
	
	// Stop
	I2C1->CR1 |= CR1_STOP_O;
	tmp = I2C1->SR1;  // Read SR1
	tmp = I2C1->SR2;  // Read SR2 to clear flags
}

void initI2C2()
{
}
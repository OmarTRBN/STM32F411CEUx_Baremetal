#include "gpio.h"

GPIO_TypeDef* getGpioPin(char GPIO_port){
	GPIO_TypeDef* target_port;
	switch(GPIO_port)
	{
		case PORTA: target_port = GPIOA;break;
		case PORTB: target_port = GPIOB;break;
		case PORTC: target_port = GPIOC;break;
		#ifdef GPIOD
		case PORTD: target_port = GPIOD;break;
		#endif
		#ifdef GPIOE
		case PORTE: target_port = GPIOE;break;
		#endif
		#ifdef GPIOF
		case PORTF: target_port = GPIOF;break;
		#endif
		#ifdef GPIOG
		case PORTG: target_port = GPIOG;break;
		#endif
		#ifdef GPIOH
		case PORTH: target_port = GPIOH;break;
		#endif
		#ifdef GPIOI
		case PORTI: target_port = GPIOI;break;
		#endif
		#ifdef GPIOJ
		case PORTJ: target_port = GPIOJ;break;
		#endif
		#ifdef GPIOK
		case PORTK: target_port = GPIOK;break;
		#endif
	}
	return target_port;
}

void pinMode(int portPin, char mode){
	char port = portPin/16;
	char pin = portPin%16;
	GPIO_TypeDef *GPIO = getGpioPin(port);
	
	RCC->AHB1ENR |= (1<<port);
	
	if (mode==INPUT)
	{
		GPIO->MODER &= ~(0b11 << (pin*2)); // Resetting bit values (set as input)
		GPIO->PUPDR &= ~(0b11 << (pin*2)); // Resetting bit values
		GPIO->PUPDR |= 0b10 << (pin*2); // Set as pulldown (10)
	}
	else if (mode==OUTPUT)
	{
		GPIO->MODER &= ~(0b11 << (pin*2)); // Resetting bit values
		GPIO->MODER |= 0b01 << (pin*2); // Setting pin to output (01)
		GPIO->OTYPER &= ~(0b1 << pin); // Setting output push-pull (0)
	}
}

void digitalWrite(int portPin, char state){
	char port = portPin/16;
	char pin = portPin%16;
	GPIO_TypeDef *GPIO = getGpioPin(port);
	
	if (state==1)
	{
		GPIO->ODR |= 0b1 << pin;
	}
	else
	{
		GPIO->ODR &= ~(0b1 << pin);
	}
}

char digitalRead(int portPin){
	char port = portPin/16;
	char pin = portPin%16; 
	GPIO_TypeDef * GPIO = getGpioPin(port);
	
	return (GPIO->IDR & (0b1 << pin));	
}

void togglePin(int portPin){
    char port = portPin / 16;  // Determine the port (0-15 is A, 16-31 is B, etc.)
    char pin = portPin % 16;   // Determine the pin within the port
    GPIO_TypeDef* GPIO = getGpioPin(port);
    
    // Toggle the pin state using XOR operation
    GPIO->ODR ^= (0b1 << pin);
}
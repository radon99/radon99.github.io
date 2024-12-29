#include "GPIO.h"

// GPIO

// 특정 포트의 전체 핀
void Gpio_initPort(volatile uint8_t* DDR, uint8_t dir)	
{
	// DDR
	// DDRD = 0xff;
	// DDRA = 0x00;
	// Mode : Input, Output;
	if(dir == OUTPUT)
		*DDR = 0xff;
	else
		*DDR = 0x00;
}

// 특정 포트의 특정 핀
void Gpio_initPin(volatile uint8_t* DDR, uint8_t dir, uint8_t pinNum)										
{
	// DDR
	// DDRA &= ~(1<<0)
	// DDRD |= (1<<0)
	
	if(dir == OUTPUT)
		*DDR |= 1<<pinNum;
	else
		*DDR &= ~(1<<pinNum);

}

void Gpio_writePort(volatile uint8_t* PORT, uint8_t data)
{
	// PORT
	// PORTD = 0xff;
	// PORTD = data;
	*PORT = data;
}

void Gpio_writePin(volatile uint8_t* PORT, uint8_t pinNum, uint8_t state)
{
	// PORT
	// PORTD |= 1<<0;
	if(state == GPIO_PIN_SET)
	{
		*PORT |= 1<<pinNum;
	}
	else
		*PORT &= ~(1<<pinNum);
	
}

uint8_t Gpio_readPort(volatile uint8_t* PIN)
{
	// Pin
	return *PIN;
	
}

uint8_t Gpio_readPin(volatile uint8_t* PIN, uint8_t pinNum)
{
	// Pin
	// PINA & (1<<0);
	
	return ((*PIN & (1<<pinNum)) != 0);
	// pushed return 0, released return 1
}
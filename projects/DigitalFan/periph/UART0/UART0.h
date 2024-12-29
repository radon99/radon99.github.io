#ifndef UART0_H_
#define UART0_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART0_init();
void UART0_ISR_Process();
void UART0_Transmit( unsigned char data );  // 데이터 시트 참조
unsigned char UART0_Receive( void );     // 데이터 시트 참조
void UART0_SendString(char *str);
uint8_t UART0_Avail();

void UART0_clearRxFlag();
void UART0_setRxFlag();
uint8_t UART0_getRxFlag();
uint8_t* UART0_readRxBuff();


#endif /* UART0_H_ */
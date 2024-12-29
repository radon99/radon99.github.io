#include "UART0.h"

uint8_t uart0Rxbuff[100];
uint8_t uart0RxFlag;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);
 
void UART0_init()
{
	// UART0, TxD, RxD, x2 mode, Baud Rate 9600
	// 8bit Data bit, 1bit Stop bit, Parity bit None -> Default Value
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
	UCSR0A |= (1<<U2X0);
	UCSR0B |= (1<<RXCIE0);  // 1byte Received Interrupt Enable
	UBRR0L = 207;
	DDRD = 0xff;
	stdout = &OUTPUT;
}
 
void UART0_ISR_Process()
{
	static uint8_t uart0RxTail = 0;
	uint8_t rx0Data = UDR0;
	
	if(rx0Data == '\n')
	{
		uart0Rxbuff[uart0RxTail] = rx0Data;
		uart0RxTail++;
		uart0Rxbuff[uart0RxTail] = 0;
		uart0RxTail = 0;
		uart0RxFlag =1;
	}
	else
	{
		uart0Rxbuff[uart0RxTail] = rx0Data;
		uart0RxTail++;
	}
	//uart0Rxbuff[uart0RxTail] = rx0Data;
	//uart0RxTail++;
}


void UART0_Transmit( unsigned char data )  // 데이터 시트 참조
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char UART0_Receive( void )     // 데이터 시트 참조
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void UART0_SendString(char *str)
{
	for(int i=0; str[i]; i++)
	{
		UART0_Transmit(str[i]);
	}
}

uint8_t UART0_Avail()
{
	if(!(UCSR0A & (1<<RXC0)))
	{
		return 0;   //RX 데이터가 없으면 0
	}
	return 1;		// 있으면 1
}

void UART0_clearRxFlag()
{
	uart0RxFlag = 0;
}

void UART0_setRxFlag()
{
	uart0RxFlag = 1;
}

uint8_t UART0_getRxFlag()
{
	return uart0RxFlag;
}

uint8_t* UART0_readRxBuff()
{
	return uart0Rxbuff;
}
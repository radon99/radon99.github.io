#include "FND.h"

uint16_t fndData = 0;
uint8_t fndColonFlag = 0;
uint8_t i = 0;

void FND_init()
{
	FND_DIGIT_DDR |= (1<< FND_DIGIT_4) | (1<< FND_DIGIT_3) | (1<< FND_DIGIT_2) | (1<< FND_DIGIT_1);	// REFRESH
	FND_DATA_DDR = 0xff;
}

void FND_dispNum(uint16_t fndNum)
{
	
	uint8_t fndFont[11] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6F, 0x80 };
						//	 0	    1	 2	   3	  4	    5	  6	   7	  8	    9	 col   //
	
	static uint8_t fndDigitState = 0;
	fndDigitState = (fndDigitState + 1) % 5;
	
	PORTE |= (1<< FND_DIGIT_4) | (1<< FND_DIGIT_3) | (1<< FND_DIGIT_2) | (1<< FND_DIGIT_1);		// PORTE : DIGIT_PORT

	switch (fndDigitState)
	{
		case 0 :
		//PORTF = fndFont[fndNum/1000%10];														// PORTF : DISPLAY_FONT_PORT
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum/1000%10]);
		//PORTE &= ~(1<<FND_DIGIT_1);															// ENABLE ONLY FND_DIGIT_1
		Gpio_writePin(&FND_DIGIT_PORT, FND_DIGIT_1, GPIO_PIN_RESET);
		_delay_ms(1);
		break;
		
		case 1 :
		//PORTF = fndFont[fndNum/100%10];
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum/100%10]);
		//PORTE &= ~(1<<FND_DIGIT_2);
		Gpio_writePin(&FND_DIGIT_PORT, FND_DIGIT_2, GPIO_PIN_RESET);
		_delay_ms(1);
		break;
		
		case 2 :
		//PORTF = fndFont[fndNum/10%10];
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum/10%10]);
		//PORTE &= ~(1<<FND_DIGIT_3);
		Gpio_writePin(&FND_DIGIT_PORT, FND_DIGIT_3, GPIO_PIN_RESET);
		_delay_ms(1);
		break;
		
		case 3 :
		//PORTF = fndFont[fndNum%10];
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum%10]);
		//PORTE &= ~(1<<FND_DIGIT_4);
		Gpio_writePin(&FND_DIGIT_PORT, FND_DIGIT_4, GPIO_PIN_RESET);
		_delay_ms(1);
		break;
		
		case 4 :
		if(fndColonFlag) 
		//PORTF = fndFont[10];
		Gpio_writePort(&FND_DATA_PORT,fndFont[10]);
		else
		//PORTF = 0x00;
		Gpio_writePort(&FND_DATA_PORT,0);
		//PORTE &= ~(1<<FND_DIGIT_2);
		Gpio_writePin(&FND_DIGIT_PORT, FND_DIGIT_2, GPIO_PIN_RESET);
		_delay_ms(1);		
		break;
	}
}

void FND_colonOn()
{
	fndColonFlag = 1;
}

void FND_colonOff()
{
	fndColonFlag = 0;
}

void FND_setFndData(uint16_t data)
{
	fndData = data;
}

void FND_ISR_Process()
{
	FND_dispNum(fndData);
}
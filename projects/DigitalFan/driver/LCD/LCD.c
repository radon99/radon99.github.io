#include "LCD.h"

#define LCD_CONTROL_DDR			DDRB
#define LCD_CONTROL_PORT		PORTB
#define LCD_DATA_DDR			DDRC
#define LCD_DATA_PORT			PORTC

#define LCD_RS					4
#define LCD_RW					6
#define LCD_EN					7

#define LCD_8bit_FUNCTION_SET	0x38
#define LCD_DISPLAY_OFF			0x08
#define LCD_DISPLAY_CLEAR		0x01
#define LCD_ENTRY_MODE_SET		0x06
#define LCD_DISPLAY_ON			0x0C

void Gpio_init()
{
	// LCD_CONTROL_DDR |= (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_EN) ;
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUT, LCD_RS);
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUT, LCD_RW);
	Gpio_initPin(&LCD_CONTROL_DDR, OUTPUT, LCD_EN);
	
	// LCD_DATA_DDR = 0xff;
	Gpio_initPort(&LCD_DATA_DDR, OUTPUT);
}

void LCD_cmdMode()
{
	// RS pin : bit 0 set
	// LCD_CONTROL_PORT &= ~(1<<LCD_RS);
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RS, GPIO_PIN_RESET);
}

void LCD_charMode()
{
	// RS pin : bit 1 set
	// LCD_CONTROL_PORT |= (1<<LCD_RS);
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RS, GPIO_PIN_SET);
	
}

void LCD_writeMode()
{
	// RW pin : bit 0 set
	// LCD_CONTROL_PORT &= ~(1<<LCD_WR);
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_RW, GPIO_PIN_RESET);
}

void LCD_enableHigh()
{
	// E pin : bit 1 set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_EN, GPIO_PIN_SET);
	_delay_ms(1);
}

void LCD_enableLow()
{
	// E pin : bit 0 set
	Gpio_writePin(&LCD_CONTROL_PORT, LCD_EN, GPIO_PIN_RESET);
	_delay_ms(1);
}

void LCD_writeByte(uint8_t data)
{
	// D0~D7 pin : data
	Gpio_writePort(&LCD_DATA_PORT, data);
}

// MCU -> LCD 명령어를 보낼 경우 (write mode)
void LCD_writeCmdData(uint8_t data)		// 8bit data interface
{
	LCD_cmdMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

// MCU -> LCD Data를 보낼 경우 (write mode)
void LCD_writeCharData(uint8_t data)
{
	LCD_charMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

void LCD_init()
{
	Gpio_init();								// DDR INITIAL
	
	_delay_ms(15);								// 15ms wait
	LCD_writeCmdData(LCD_8bit_FUNCTION_SET); 	// LCD_8bit_FUNCTION_SET	0x38
	_delay_ms(5);								// 5ms wait
	LCD_writeCmdData(LCD_8bit_FUNCTION_SET); 	// LCD_8bit_FUNCTION_SET	0x38
	_delay_ms(1);								// 1ms wait(100us)
	LCD_writeCmdData(LCD_8bit_FUNCTION_SET); 	// LCD_8bit_FUNCTION_SET	0x38
	LCD_writeCmdData(LCD_8bit_FUNCTION_SET); 	// LCD_8bit_FUNCTION_SET	0x38
	LCD_writeCmdData(LCD_DISPLAY_OFF); 			// LCD_DISPLAY_OFF			0x08
	LCD_writeCmdData(LCD_DISPLAY_CLEAR); 		// LCD_DISPLAY_CLEAR		0x01
	LCD_writeCmdData(LCD_ENTRY_MODE_SET); 		// LCD_ENTRY_MODE_SET		0x06
	
	LCD_writeCmdData(LCD_DISPLAY_ON); 			// LCD_DISPLAY_ON			0x0C
}

void LCD_writeString(char *str)		// 문자열(배열)은 주소
{
	for(int i = 0; str[i]; i++)
	{
		LCD_writeCharData(str[i]);
	}
}

void LCD_gotoXY(uint8_t row, uint8_t col)
{
	col %= 16; row %= 2;
	uint8_t lcdregisterAddress = (0x40 * row) + col;
	uint8_t command = 0x80 + lcdregisterAddress;
	LCD_writeCmdData(command);
}

void LCD_writeStringXY(uint8_t row, uint8_t col, char* str)
{
	LCD_gotoXY(row, col);
	LCD_writeString(str);
}

void LCD_clearDisplay()
{
	LCD_writeCmdData(LCD_DISPLAY_CLEAR); 		// LCD_DISPLAY_CLEAR
}

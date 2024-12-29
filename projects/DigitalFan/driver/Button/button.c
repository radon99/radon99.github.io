// GPIO connected BUTTON DRIVER VER.

#include "Button.h"		// 해당 파일 기준으로 파일 찾는다. 파일이 바로 옆에 있어서 경로설정할 필요없음.

void Button_init(button_t *btn, volatile uint8_t* ddr, volatile uint8_t* pin, volatile uint8_t* port, uint8_t pinNum)
{
	btn->DDR = ddr;	// -> : 포인터 구조체 변수 내의 멤버 변수 접근
	btn->PIN = pin;
	btn->PORT = port;
	btn->pinNum = pinNum;
	btn->prevState = 1;
	// 특정 비트 0으로 설정하여 입력모드
	Gpio_initPin(btn->DDR, INPUT, btn->pinNum);
	Gpio_initPort(btn->PORT, btn->pinNum);
}
uint8_t Button_GetState(button_t* btn)
{
	uint8_t curState = Gpio_readPin(btn->PIN, btn->pinNum);
	
	if((curState == 0) && (btn->prevState == 1))
	{
		_delay_ms(10);
		btn->prevState = PUSHED;
		return ACT_PUSHED;
	}
	else if ((curState != 0) && (btn->prevState == 0))
	{
		_delay_ms(10);
		btn->prevState = RELEASED;
		return ACT_RELEASED;
	}
	return ACT_NONE;
}

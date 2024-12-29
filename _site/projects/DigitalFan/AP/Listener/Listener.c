#include "Listener.h"

uint8_t fanTimeFlag;
button_t btnStop, btnSpeed, btnMode, btnTimer;

void Listener_init()
{	
	//UART_init
	UART0_init();
	//Button_init
	Button_init(&btnStop, &BUTTON1_DDR, &BUTTON1_PIN, &BUTTON1_PORT, BUTTON1_PINNUM);
	Button_init(&btnSpeed, &BUTTON2_DDR, &BUTTON2_PIN, &BUTTON2_PORT, BUTTON2_PINNUM);
	Button_init(&btnMode, &BUTTON3_DDR, &BUTTON3_PIN, &BUTTON3_PORT, BUTTON3_PINNUM);
	Button_init(&btnTimer, &BUTTON4_DDR, &BUTTON4_PIN, &BUTTON4_PORT, BUTTON4_PINNUM);
}

void UART0_command()
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();
	
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();
	
	if(UART0_getRxFlag())
	{
		UART0_clearRxFlag();
		uint8_t* rxString = UART0_readRxBuff();
		
		// 풍량조절 UART
		if(fanAutoManualState == MANUAL)
		{
			if(!strcmp((char*)rxString,"fan_off\n"))
			{
				fanWindSpeed = OFF;
				Model_setfanWindSpeed(fanWindSpeed);
			}
			else if(!strcmp((char*)rxString,"fan_low\n"))
			{
				fanWindSpeed = LOW;
				Model_setfanWindSpeed(fanWindSpeed);
			}
			else if(!strcmp((char*)rxString,"fan_medium\n"))
			{
				fanWindSpeed = MEDIUM;
				Model_setfanWindSpeed(fanWindSpeed);
			}
			else if(!strcmp((char*)rxString,"fan_high\n"))
			{
				fanWindSpeed = HIGH;
				Model_setfanWindSpeed(fanWindSpeed);
			}
		}
		
		// 타이머 UART
		if(!strcmp((char*)rxString,"time_off\n"))
		{
			fanTimerState = TIME_OFF;
			Model_setfanTimerState(fanTimerState);
			fanTimeFlag = 0;
			Model_setfanTimeFlag(fanTimeFlag);
		}		
		if(!strcmp((char*)rxString,"time3\n"))
		{
			fanTimerState = TIME3;
			Model_setfanTimerState(fanTimerState);
			fanTimeFlag = 0;
			Model_setfanTimeFlag(fanTimeFlag);
		}
		else if(!strcmp((char*)rxString,"time5\n"))
		{
			fanTimerState = TIME5;
			Model_setfanTimerState(fanTimerState);
			fanTimeFlag = 0;
			Model_setfanTimeFlag(fanTimeFlag);
		}
		else if(!strcmp((char*)rxString,"time7\n"))
		{
			fanTimerState = TIME7;
			Model_setfanTimerState(fanTimerState);
			fanTimeFlag = 0;
			Model_setfanTimeFlag(fanTimeFlag);
		}
	}
}

void Listener_eventCheck()	
{	
	Listener_stopEvent();	
	Listener_modeEvent();
	Listener_timerEvent();	
}

void Listener_manualEvent()											
{
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();						
		
	if((Button_GetState(&btnSpeed) == ACT_RELEASED))				
	{
		fanWindSpeed = (fanWindSpeed + 1) % 4;
		Model_setfanWindSpeed(fanWindSpeed);
	}
}

void Listener_modeEvent()
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	switch(fanAutoManualState)
	{
		case MANUAL :
		Listener_manualEvent();
		if((Button_GetState(&btnMode) == ACT_RELEASED))
		{
			fanAutoManualState = AUTO;
			Model_setfanAutoManualState(fanAutoManualState);
		}
		break;
		case AUTO :
		if((Button_GetState(&btnMode) == ACT_RELEASED))
		{
			fanAutoManualState = MANUAL;
			Model_setfanAutoManualState(fanAutoManualState);
		}
		break;
	}
}

void Listener_timerEvent()
{
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();
		
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();
	fanTimeFlag = Model_getfanTimeFlag();
	
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	if((fanWindSpeed != OFF) | (fanAutoManualState == AUTO))			// 오토랑 바람이 켜져있을때만 타이머 설정 가능
	{
		if((Button_GetState(&btnTimer) == ACT_RELEASED))				// 타이머 버튼이 눌리면 다음 타이머 순서로 돌림
		{
			fanTimerState = (fanTimerState + 1) % 4;
			Model_setfanTimerState(fanTimerState);
			fanTimeFlag = 0;
			Model_setfanTimeFlag(fanTimeFlag);								// 타이머 시간 설정 아직 안함.
		}
	}
}

void Listener_stopEvent()
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();				
	
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();						
	
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();
	
	if((Button_GetState(&btnStop) == ACT_RELEASED))				// 무슨 조건이든 항상 끄게
	{
		//MANUAL로 전환
		fanAutoManualState = MANUAL;
		Model_setfanAutoManualState(fanAutoManualState);
		//fan wind speed off
		fanWindSpeed = OFF;
		Model_setfanWindSpeed(fanWindSpeed);					// 바람세기 OFF
		//타이머도 OFF
		fanTimerState = TIME_OFF;								// 타이머도 끄기
		Model_setfanTimerState(fanTimerState);
	}
}


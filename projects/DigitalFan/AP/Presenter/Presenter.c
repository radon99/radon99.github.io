#include "Presenter.h"
// 출력 전문가

void Presenter_init()
{
	FND_init();
	LCD_init();
}

void Presenter_dispFanData(uint8_t min, uint8_t sec)
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();
	
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();
	
	uint16_t timerData;
	
	//FND DISPLAY
	if(fanTimerState != TIME_OFF)
	{	
		timerData = min*100 + sec;
		FND_setFndData(timerData);
	}
	else
	{
		timerData = 0;
		FND_setFndData(timerData);
	}

	//LCD DISPLAY
	static uint8_t prevSec = 0xff;
	static uint8_t i, j;
	char buff[30];
	if(fanTimerState == TIME_OFF)
	{
		sprintf(buff, "  Digital Fan!  ");
		LCD_writeStringXY(0, 0, buff);
		i = 2;
	}
	else if(sec != prevSec)
	{
		prevSec = sec;
		if((i == 0)|(i == 4))
		{
			j ^= 1;
			sprintf(buff, "                ");
			LCD_writeStringXY(0, 0, buff);
		}
		sprintf(buff, "Digital Fan!");
		LCD_writeStringXY(0, i, buff);
		if(j)
		{
			LCD_gotoXY(0, i - 1);
			LCD_writeString(" ");
			i++;
		}
		else
		{
			LCD_gotoXY(0, i + 12);
			LCD_writeString(" ");
			i--;
		}				
	}
	if(fanAutoManualState == MANUAL)
	{
		switch(fanWindSpeed)
		{
			case OFF :
			sprintf(buff, "  STOP   00:00");
			LCD_writeStringXY(1, 0, buff);
			break;
			case LOW :
			sprintf(buff, "  LOW    %02d:%02d", min, sec);
			LCD_writeStringXY(1, 0, buff);
			break;
			case MEDIUM :
			sprintf(buff, "  MEDIUM %02d:%02d", min, sec);
			LCD_writeStringXY(1, 0, buff);
			break;
			case HIGH :
			sprintf(buff, "  HIGH   %02d:%02d", min, sec);
			LCD_writeStringXY(1, 0, buff);
			break;
		}
	}
	else
	{
		sprintf(buff, "  AUTO   %02d:%02d", min, sec);
		LCD_writeStringXY(1, 0, buff);
	}
}

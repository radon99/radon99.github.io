#include "Service_Fan.h"

uint16_t fan_millisec;
uint8_t fan_sec, fan_min;
uint16_t counter;
uint16_t counter2;
uint8_t i;
uint16_t random_time;

void Service_fanInit()
{
	//Time Initialize
	fan_millisec = 0;
	fan_sec = 0;
	fan_min = 0;
	counter = 0;
	random_time = 0;
	
	//Fan Motor
	//PWM Initialize
	TCCR3B |= (0<<CS32) | (1<<CS31) | (1<<CS30); // PreScaler 1/64	// FAST PWM mode 14
	TCCR3B |= (1<<WGM33) | (1<<WGM32);
	TCCR3A |= (1<<WGM31) | (0<<WGM30);	
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0); // non-inverting mode	
	DDRE |= (1<<3);	
	
	//Buzzer
	//PWM Initialize
	TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10); // PreScaler 1/64
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1A |= (1 << COM1A1) | (0 << COM1A0); // non-inverting mode
	DDRB |= (1<<5);	
}

void Service_fanLow()	
{
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);
	FAN_ICR = (250000 / 20000) - 1;	// 20khz frequency , Top value
	FAN_OCR = FAN_ICR / 1.4;		// Duty Cycle 71%
	TCNT3 = 0;
}

void Service_fanMedium()	
{
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);
	FAN_ICR = (250000 / 20000) - 1;	// 20khz frequency , Top value
	FAN_OCR = FAN_ICR / 1.15;		// Duty Cycle 86%
	TCNT3 = 0;
}

void Service_fanHigh()	
{
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);
	FAN_ICR = (250000 / 20000) - 1;	// 20khz frequency , Top value
	FAN_OCR = FAN_ICR / 1;			// Duty Cycle 100%
	TCNT3 = 0;
}

void Service_fanOff()
{
	TCCR3A &= ~((1<<COM3A1) | (1<<COM3A0));
	TCNT3 = 0;
}

void Service_fanAutoSpeed()
{
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);
	FAN_ICR = (250000 / 20000) - 1;							// 20khz frequency , Top value
	FAN_OCR = FAN_ICR / ((double)((rand() % 6) + 10) / 10);			// Duty Cycle 66 ~ 100%
	TCNT3 = 0;
}

/////Interrupt Service/////
void Service_fanDecMillisec()							
{
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();
	
	if(fan_millisec || fan_sec || fan_min)
	{
		if(fanTimerState != TIME_OFF)
		{
			if (fan_millisec > 0) {
				fan_millisec--;
				} else {
				fan_millisec = 999;
				if (fan_sec > 0) {
					fan_sec--;
					} else {
					fan_sec = 59;
					if (fan_min > 0) {
						fan_min--;
						} else {
						fan_min = 59;
					}
				}
			}
		}												
}
}

void Service_fanAutoConfigure()
{
	counter++;
		if (counter >= 2000) {
			uint8_t fanAutoManualState;
			fanAutoManualState = Model_getfanAutoManualState();
			
			if(fanAutoManualState == AUTO)
			{
				Service_fanAutoSpeed();
			}								
			counter = 0;
		}
}

void Service_MusicConfigure()
{
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();
	
	uint16_t frequency[] = { 
		 NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4,
		 NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_D5, NOTE_C5,
		 NOTE_G4, NOTE_G4, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B4, NOTE_A4,
		 NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5 };
	
	playTone(frequency, fanWindSpeed);
	
}

void playTone(uint16_t* frequency, uint8_t speed)
{
	if(speed != OFF)
	{
		TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
		counter2++;
		if (counter2 >= (1000 / speed)) {
			TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
			i++;
			i %= 25;
			if (counter2 >= (1300 / speed))
			{
				counter2 = 0;
				TCNT1 = 0;
			}
		}
		else
		{
			Buzzer_makeHertz(frequency[i]);
		}
		
	}
	else
	{
		TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
	}	
}

void Buzzer_makeHertz(uint16_t hertz)	// 20 20Khz 가청주파수
{
	BUZZER_ICR =  (250000 / hertz) - 1;	// 1khz frequency , Top value
	BUZZER_OCR = BUZZER_ICR / 2;		// Duty Cycle 50%
}
////////////////////////////

void Service_fanRun()
{
	Service_fanTimerConfigure();
	Service_fanTimeOver();
	Service_fanManualConfigure();
	Service_fanAutoConfigure();
	Service_fanDisplay();
}

void Service_fanTimerConfigure()
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();
	
	uint8_t fanTimeFlag;
	fanTimeFlag = Model_getfanTimeFlag();
	
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();	
			
	if((fanWindSpeed == OFF) & (fanAutoManualState == MANUAL))		// stop 버튼 누르면 시간 초기화
	{
		fan_min = 0;
		fan_sec = 0;
		fan_millisec = 0;
	}
	
	if(!fanTimeFlag)												// 타이머 버튼 눌릴때마다 새로 설정되게.
	{
		switch(fanTimerState)
		{
			case TIME_OFF :
			fan_min = 0;
			fan_sec = 0;
			fan_millisec = 0;
			break;
			case TIME3 :
			fan_min = 3;
			fan_sec = 0;
			fan_millisec = 0;
			break;
			case TIME5 :
			fan_min = 5;
			fan_sec = 0;
			fan_millisec = 0;
			break;
			case TIME7 :
			fan_min = 7;
			fan_sec = 0;
			fan_millisec = 0;
			break;
		}
		fanTimeFlag = 1;
		Model_setfanTimeFlag(fanTimeFlag);
	}

}

void Service_fanTimeOver()
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	uint8_t fanTimerState;
	fanTimerState = Model_getfanTimerState();
	
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();	
	
	if(fanTimerState != TIME_OFF)									// 타이머 켜져있을때
	{
		if(!(fan_millisec | fan_sec | fan_min))						// 다 0일때
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
}

void Service_fanManualConfigure()
{
	uint8_t fanAutoManualState;
	fanAutoManualState = Model_getfanAutoManualState();
	
	uint8_t fanWindSpeed;
	fanWindSpeed = Model_getfanWindSpeed();
	
	if(fanAutoManualState == MANUAL)// 수동모드일때
	{
		switch(fanWindSpeed)
		{
			case OFF :
				Service_fanOff();
			break;
			case LOW :
				Service_fanLow();
			break;
			case MEDIUM :
				Service_fanMedium();
			break;
			case HIGH :
				Service_fanHigh();
			break;
		}
	}
}

void Service_fanDisplay()
{
	Presenter_dispFanData(fan_min, fan_sec);
}
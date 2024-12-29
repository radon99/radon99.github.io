#include "apMain.h"

ISR(TIMER0_OVF_vect)
{
	FND_ISR_Process();
	TCNT0 = 130;
}

ISR(TIMER2_COMP_vect)
{
	Service_fanDecMillisec();
	Service_fanAutoConfigure();
	Service_MusicConfigure();
}

ISR(USART0_RX_vect)
{
	UART0_ISR_Process();
}

void apMain_init()
{
	//AP Initialize
	Listener_init();
	Service_fanInit();
	Presenter_init();
	
	//Timer Initialize
	TIM0_init();
	TIM2_init();
	sei();
	
	//Model Default Set
	Model_setfanWindSpeed(OFF);
	Model_setfanTimerState(TIME_OFF);
	Model_setfanAutoManualState(MANUAL);
	Model_setfanTimeFlag(1);
}

void apMain_execute()
{
	UART0_command();
	Listener_eventCheck();
	Service_fanRun();
}
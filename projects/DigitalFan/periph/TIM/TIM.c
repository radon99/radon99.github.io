#include "TIM.h"

void TIM0_init(){	// 1ms overflow interrupt, FND display
	// /128 1m interrupt
	TCCR0 |= ((1<<CS02) | (0<<CS01) | (1<<CS00));	// /128 PreScaler
	TIMSK |= (1<<TOIE0);							// TIMSK Timer/Counter0 overflow interrupt enable 
	// TIMSK 타이머/카운터의 인터럽트를 제어하는 레지스터
	TCNT0 = 130;
}

void TIM2_init(){	// 1ms OUTPUT COMPARE interrupt(CTC MODE) , TIME calculate
	TCCR2 |= ((0<<CS22) | (1<<CS21) | (1<<CS20));	// /64 PreScaler
	TIMSK |= (1<<OCIE2);							// TIMSK Timer/Counter2 OUTPUT COMPARE interrupt enable
	
	TCCR2 |= ((1<<WGM21) | (1<<WGM20));				// CTC MODE
	OCR2 = 250 - 1;									// 0 ~ 249 250사이클, 0부터 카운트, 1카운트마다 4us, 4us * 250 = 1ms, 1ms마다 인터럽트 발생
}



#include "Model_TimerValue.h"		// 선풍기 수동, 자동상태 공용데이터

uint8_t fanTimerState;
uint8_t fanTimeFlag;

uint8_t Model_getfanTimerState()
{
	return fanTimerState;
}

void Model_setfanTimerState(uint8_t state)
{
	fanTimerState = state;
}

uint8_t Model_getfanTimeFlag()
{
	return fanTimeFlag;
}

void Model_setfanTimeFlag(uint8_t flag)
{
	fanTimeFlag = flag;
}



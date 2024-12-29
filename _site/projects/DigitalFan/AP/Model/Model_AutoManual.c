#include "Model_AutoManual.h"		// 선풍기 수동, 자동상태 공용데이터

uint8_t fanAutoManualState;

uint8_t Model_getfanAutoManualState()
{
	return fanAutoManualState;
}

void Model_setfanAutoManualState(uint8_t state)
{
	fanAutoManualState = state;
}




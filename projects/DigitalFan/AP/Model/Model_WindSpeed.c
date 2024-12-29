#include "Model_WindSpeed.h"

uint8_t fanWindSpeed;

uint8_t Model_getfanWindSpeed()
{
	return fanWindSpeed;
}

void Model_setfanWindSpeed(uint8_t state)
{
	fanWindSpeed = state;
}




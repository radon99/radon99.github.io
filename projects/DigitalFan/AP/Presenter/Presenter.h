#ifndef PRESENTER_H_
#define PRESENTER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "../../driver/FND/FND.h"
#include "../../driver/LCD/LCD.h"
#include "../Model/Model_TimerValue.h"
#include "../Model/Model_WindSpeed.h"
#include "../Model/Model_AutoManual.h"

void Presenter_init();
void Presenter_dispFanData(uint8_t min, uint8_t sec);

#endif /* PRESENTER_H_ */
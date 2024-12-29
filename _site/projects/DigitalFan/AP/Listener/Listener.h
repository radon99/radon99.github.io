#ifndef LISTENER_H_
#define LISTENER_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#include "../../periph/UART0/UART0.h"
#include "../../driver/Button/button.h"
#include "../Model/Model_AutoManual.h"
#include "../Model/Model_TimerValue.h"
#include "../Model/Model_WindSpeed.h"

void Listener_init();
void Listener_eventCheck();
void Listener_manualEvent();
void Listener_modeEvent();
void Listener_timerEvent();
void Listener_stopEvent();
void UART0_command();

#endif /* LISTENER_H_ */
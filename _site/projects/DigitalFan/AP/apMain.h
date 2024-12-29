﻿#ifndef APMAIN_H_
#define APMAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Listener/Listener.h"
#include "Service/Service_Fan.h"
#include "Presenter/Presenter.h"
#include "../periph/TIM/TIM.h"

void apMain_init();
void apMain_execute();

#endif /* APMAIN_H_ */
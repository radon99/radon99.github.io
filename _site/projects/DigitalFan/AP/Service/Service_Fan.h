#ifndef SERVICE_FAN_H_
#define SERVICE_FAN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "../Model/Model_TimerValue.h"
#include "../Model/Model_AutoManual.h"
#include "../Model/Model_WindSpeed.h"
#include "../Presenter/Presenter.h"

#define FAN_ICR			ICR3
#define FAN_OCR			OCR3A
#define BUZZER_ICR		ICR1
#define BUZZER_OCR		OCR1A

#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  783

void Service_fanInit();
void Service_fanDecMillisec();
void Service_fanRun();

void Service_fanOff();
void Service_fanLow();
void Service_fanMedium();	
void Service_fanHigh();
void Service_fanAutoSpeed();

void Service_fanTimerConfigure();
void Service_fanTimeOver();
void Service_fanManualConfigure();
void Service_fanAutoConfigure();
void Service_fanDisplay();
void Service_MusicConfigure();
void playTone(uint16_t *frequency, uint8_t speed);
void Buzzer_makeHertz(uint16_t hertz);

#endif /* SERVICE_FAN_H_ */
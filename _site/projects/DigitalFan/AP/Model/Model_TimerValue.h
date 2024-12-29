#ifndef MODEL_TIMERVALUE_H_
#define MODEL_TIMERVALUE_H_
#include <avr/io.h>

enum { TIME_OFF, TIME3, TIME5, TIME7 };

uint8_t Model_getfanTimerState();
void Model_setfanTimerState(uint8_t state);
uint8_t Model_getfanTimeFlag();
void Model_setfanTimeFlag(uint8_t flag);

#endif /* MODEL_TIMERVALUE_H_ */
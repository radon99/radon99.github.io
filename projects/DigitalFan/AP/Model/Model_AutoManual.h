#ifndef MODEL_AUTOMANUAL_H_
#define MODEL_AUTOMANUAL_H_
#include <avr/io.h>

enum { MANUAL, AUTO };

uint8_t Model_getfanAutoManualState();
void Model_setfanAutoManualState(uint8_t state);

#endif /* MODEL_AUTOMANUAL_H_ */
#ifndef MODEL_WINDSPEED_H_
#define MODEL_WINDSPEED_H_
#include <avr/io.h>

enum { OFF, LOW, MEDIUM, HIGH };

uint8_t Model_getfanWindSpeed();
void Model_setfanWindSpeed(uint8_t state);

#endif /* MODEL_WINDSPEED_H_ */
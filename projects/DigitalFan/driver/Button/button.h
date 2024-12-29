#define BUTTON_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../periph/GPIO/GPIO.h"

#define BUTTON1_DDR			DDRA
#define BUTTON1_PIN			PINA
#define BUTTON1_PORT		PORTA
#define BUTTON1_PINNUM		0

#define BUTTON2_DDR			DDRA
#define BUTTON2_PIN			PINA
#define BUTTON2_PORT		PORTA
#define BUTTON2_PINNUM		1

#define BUTTON3_DDR			DDRA
#define BUTTON3_PIN			PINA
#define BUTTON3_PORT		PORTA
#define BUTTON3_PINNUM		2

#define BUTTON4_DDR			DDRA
#define BUTTON4_PIN			PINA
#define BUTTON4_PORT		PORTA
#define BUTTON4_PINNUM		3

enum {PUSHED, RELEASED};
enum {ACT_PUSHED, ACT_RELEASED, ACT_NONE};

typedef struct _button				// 구조체는 헤더파일에 넣는다.
{
	volatile uint8_t* DDR;
	volatile uint8_t* PIN;
	volatile uint8_t* PORT;
	uint8_t pinNum;
	uint8_t prevState;
	
	// port : PA, PB, PC...
	// pin number
	// static prevState
	
}button_t;	// 자료형 선언

void Button_init(button_t *btn, volatile uint8_t* ddr, volatile uint8_t* pin, volatile uint8_t* port, uint8_t pinNum);
uint8_t Button_GetState(button_t* btn);


#ifndef F407_FN_H
#define F407_FN_H
#include <f407.h>

//pin data direction types
#define INPUT 0b00
#define OUTPUT 0b01
#define ALTFN 0b10
#define ANALOG 0b11
//pin output types
#define PUSH_PULL 0b0
#define OPEN_DRAIN 0b1
//pin input types
#define NOPULL 0b00
#define PULLUP 0b01
#define PULLDOWN 0b10

void GPIO_pinConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinDir, uint8_t pupd);
void GPIO_pinSet(GPIO_Typedef* gpio, uint8_t pin);
void GPIO_pinReset(GPIO_Typedef* gpio, uint8_t pin);
uint8_t GPIO_pinRead(GPIO_Typedef* gpio, uint8_t pin);
void testFunc();
#endif
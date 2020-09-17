#ifdef BOARD_F103
#ifndef F1_GPIO_H
#define F1_GPIO_H
#include <stdint.h>
#include <boards.h>

#define INPUT 0x0
#define OUTPUT 0x1
#define OUTPUT_LOW_SPEED 0x2
#define OUTPUT_HIGH_SPEED 0x3

#define ANALOG 0x0
#define INPUT_FLOATING 0x1
#define INPUT_PUPD 0x2

#define GPO_PP 0x0
#define GPO_OD 0x1
#define AFO_PP 0x2
#define AFO_OD 0x3

#define GPIO_MODE_MASK(n)		(0x3 << ((n)*4))
#define GPIO_CNF_MASK(n)		(0x3 << (((n)*4) + 2))
#define GPIO_MODE(n, mode)	(mode << ((n)*4))	
#define GPIO_CNF(n, mode)	(mode << (((n)*4) + 2))

void pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t mode);
void pinConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t config);
void writeHigh(GPIO_Typedef* gpio, uint8_t pin);
void writeLow(GPIO_Typedef* gpio, uint8_t pin);
void toggle(GPIO_Typedef* gpio, uint8_t pin);

#endif
#endif
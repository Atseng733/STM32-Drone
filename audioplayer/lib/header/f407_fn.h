#ifndef F407_FN_H
#define F407_FN_H
#include <boards.h>
//pin data direction types
#define INPUT (0x00)
#define OUTPUT (0x01)
#define ALTFN (0x02)
#define ANALOG (0x03)
//pin output types
#define PUSH_PULL (0x00)
#define OPEN_DRAIN (0x01)
//pin speeds
#define LOW_SPEED (0x00)
#define MED_SPEED (0x01)
#define HI_SPEED (0x02)
#define VHI_SPEED (0x03)
//pin pull-up/pull-down types
#define FLOATING (0x00)
#define PULLUP (0x01)
#define PULLDOWN (0x02)
//alternate functions
#define I2C_AFN (0x04)
#define SPI_AFN (0x05)
#define USART_AFN (0x07)
#define SDIO_AFN (0x0C)

#define GPIO_MODE(n, mode)		((mode) << (2 * (n)))
#define GPIO_PUPD(n, pupd)		((pupd) << (2 * (n)))
#define GPIO_OTYPE(n, otype) (otype << n)
#define GPIO_SPEED(n, speed) (speed << (2 * n))
#define GPIO_WORD_MASK(n)		(0x3 << (2 * (n)))
#define GPIO_HWORD_MASK(n)		(0x1 << (n))

void pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinMode);
void pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinMode, uint8_t pupd);
void pinOutputConfig(GPIO_Typedef* gpio,uint8_t pin, uint8_t mode, uint8_t speed, uint8_t pupd);
void pinAFNConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t AFx, uint8_t otype, uint8_t speed, uint8_t pupd);
void writeLow(GPIO_Typedef* gpio, uint8_t pin);
void writeHigh(GPIO_Typedef* gpio, uint8_t pin);
void toggle(GPIO_Typedef* gpio, uint8_t pin);
uint8_t pinRead(GPIO_Typedef* gpio, uint8_t pin);

#endif
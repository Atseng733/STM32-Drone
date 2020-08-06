#ifndef F407_FN_H
#define F407_FN_H
#include <f407.h>

//pin data direction types
#define INPUT ((uint32_t) 0x00)
#define OUTPUT ((uint32_t) 0x01)
#define ALTFN ((uint32_t) 0x02)
#define ANALOG ((uint32_t) 0x03)
//pin output types
#define PUSH_PULL ((uint32_t) 0x00)
#define OPEN_DRAIN ((uint32_t) 0x01)
//pin speeds
#define LOW_SPEED ((uint32_t) 0x00)
#define MED_SPEED ((uint32_t) 0x01)
#define HI_SPEED ((uint32_t) 0x02)
#define VHI_SPEED ((uint32_t 0x03))
//pin pull-up/pull-down types
#define FLOATING ((uint32_t) 0x00)
#define PULLUP ((uint32_t) 0x01)
#define PULLDOWN ((uint32_t) 0x02)
//alternate functions
#define I2C_AFN ((uint32_t) 0x04)
#define USART_AFN ((uint32_t) 0x07)

#define GPIO_CLK_ENABLE(port) port##_Enable
#define GPIOA_Enable RCC->AHB1ENR |= 0x01;
#define GPIOB_Enable RCC->AHB1ENR |= 0x02;
#define GPIOC_Enable RCC->AHB1ENR |= 0x04;
#define GPIOD_Enable RCC->AHB1ENR |= 0x08;
#define GPIOD_Enable RCC->AHB1ENR |= 0x08;
#define GPIOE_Enable RCC->AHB1ENR |= 0x10;

#define GPIO_MODE(n, mode)		((mode) << (2 * (n)))
#define GPIO_PUPD(n, pupd)		((pupd) << (2 * (n)))
#define GPIO_OTYPE(n, otype) (otype << n)
#define GPIO_SPEED(n, speed) (speed << (2 * n))
#define GPIO_WORD_MASK(n)		(0x3 << (2 * (n)))
#define GPIO_HWORD_MASK(n)		(0x1 << (n))

void GPIO_pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinMode);
void GPIO_pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinMode, uint8_t pupd);
void GPIO_pinOutputConfig(GPIO_Typedef* gpio,uint8_t pin, uint8_t mode, uint8_t speed, uint8_t pupd);
void GPIO_pinAFNConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t AFx, uint8_t otype, uint8_t speed, uint8_t pupd);
void GPIO_writeLow(GPIO_Typedef* gpio, uint8_t pin);
void GPIO_writeHigh(GPIO_Typedef* gpio, uint8_t pin);
void GPIO_toggle(GPIO_Typedef* gpio, uint8_t pin);
uint8_t GPIO_pinRead(GPIO_Typedef* gpio, uint8_t pin);
void testFunc();

#endif
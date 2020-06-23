#ifndef GPIO_H_
#define GPIO_H_

#include <iostream>
#include <stdint.h>
#define SET_SFR(OFFSET) (*(volatile uint32_t)(GPIO_BASE + OFFSET*4))

#define GPIO_BASE 0x60000300
#define GPO (*(volatile uint32_t*)(0x60000300))
#define GPO_SET (*(volatile uint32_t*)(0x60000304))
//#define GPO_CLR ()
#define GPEN_SET (*(volatile uint32_t*)(0x60000310))

#define HIGH 1
#define LOW 0

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t mode);

#endif
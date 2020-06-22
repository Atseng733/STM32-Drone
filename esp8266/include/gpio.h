#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#define SET_SFR(OFFSET) (*(volatile uint32_t)(GPIO_BASE + OFFSET*4))

#define GPIO_BASE 0x60000300
#define GPIO_OUT (*(volatile uint32_t*)(GPIO_BASE + 0x0000))
#define GPIO_OUT_SET (*(volatile uinit32_t*)(GPIO_BASE + 0x0001))

#endif
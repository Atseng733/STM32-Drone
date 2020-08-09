#ifndef RCC_H
#define RCC_H
#include <boards.h>

#define PLLRDY (1 << 25)
#define PLLON (1 << 24)
#define HSERDY (1 << 17)
#define HSEON (1 << 16)
#define HSIRDY (1 << 1)
#define HSION (1 << 0)

void rcc_hse_enable();
void rcc_hsi_disable();
void rcc_pll_enable();
void rcc_io_enable(uint16_t port);

#endif
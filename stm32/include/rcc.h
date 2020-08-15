#ifndef RCC_H
#define RCC_H
#include <boards.h>

#if PLL_CLK_SRC == 1 //determine pll clock base frequency
	#define PLL_CLK (F_HSE/2)
#else
	#define PLL_CLK (F_HSI/2)
#endif

#if F_CPU/4000000UL > 2 //calculate pll clock multiplier
	#define PLL_EN 1
	#define PLL_MUL (F_CPU/PLL_CLK)
#elif F_CPU/4000000UL == 2
	#define PLL_EN 0
	#define PLL_MUL 0
#endif

#if F_CPU > 36000000UL
	#define APB1_PSC 1
	#define APB1_CLK (F_CPU/2)
#else
	#define APB1_PSC 0
	#define APB1_CLK F_CPU
#endif

#define PLLRDY (1 << 25)
#define PLLON (1 << 24)
#define HSERDY (1 << 17)
#define HSEON (1 << 16)
#define HSIRDY (1 << 1)
#define HSION (1 << 0)

void rcc_hse_enable();
void rcc_hsi_disable();
void rcc_pll_enable();
void rcc_sys_clk_setup();
void rcc_io_enable(uint16_t port);
void rcc_i2c1_enable();
void rcc_usart1_enable();

#endif
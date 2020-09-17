#ifndef RCC_H
#define RCC_H
#include <boards.h>

#if PLL_CLK_SRC == 1 //determine pll multiplier ratio
	#define PLL_RATIO (F_CPU / (F_HSE / 2))
#else
	#define PLL_RATIO (F_CPU / (F_HSI /2))
#endif

#define FLASH_WAIT_STATES ((F_CPU - 1000000) / 30000000)

#if(F_CPU > 42000000 && F_CPU <= 84000000) //calculate apb1 domain prescaler
	#define APB1PSC 2
#elif (F_CPU > 84000000)
	#define APB1PSC 4
#endif

#if(F_CPU > 84000000)
	#define APB2PSC 2
#endif

#define APB1_CLK (F_CPU / APB1PSC)
#define APB2_CLK (F_CPU / APB2PSC)
#define PLLQ ((((2 * F_CPU) - 1000000) / 48000000) + 1)

void rcc_hse_enable();
void rcc_hsi_disable();
void rcc_pll_enable();
void rcc_sys_clk_setup();
void enableMCO(uint32_t mcox, uint8_t clk_out);
void rcc_io_enable(uint16_t port);
void rcc_i2c1_enable();
void rcc_usart1_enable();

#endif
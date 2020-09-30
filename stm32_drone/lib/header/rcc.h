#ifndef RCC_H
#define RCC_H
#include <boards.h>

#if PLL_CLK_SRC == 1 //determine pll clock base frequency
	#define PLL_CLK (F_HSE/2)
#else
	#define PLL_CLK (F_HSI/2)
#endif

#if(F_CPU <=  24000000)
	#define FLASH_WAIT_STATES 0
#elif(F_CPU <= 48000000)
	#define FLASH_WAIT_STATES 1
#elif(F_CPU <= 72000000)
	#define FLASH_WAIT_STATES 2
#endif

#if(F_CPU/4000000UL > 2) //calculate pll clock multiplier
	#define PLL_EN 1
	#define PLL_MUL (F_CPU/PLL_CLK)
#elif(F_CPU/4000000UL) == 2
	#define PLL_EN 0
	#define PLL_MUL 0
#endif

#if(F_CPU <= APB1_MAX_FREQ)
	#define APB1_PSC 1
#elif(F_CPU > APB1_MAX_FREQ && F_CPU <= (2*APB1_MAX_FREQ)) //calculate apb1 domain prescaler
	#define APB1_PSC 2
#elif (F_CPU > (2*APB1_MAX_FREQ))
	#define APB1_PSC 4
#endif

#if(F_CPU <= APB2_MAX_FREQ)
	#define APB2_PSC 1
#elif(F_CPU > APB2_MAX_FREQ)
	#define APB2_PSC 2
#endif

#define APB1_CLK (F_CPU / APB1_PSC)
#define APB2_CLK (F_CPU / APB2_PSC)

#define RCC_MCO_SYSCLK 0x4
#define RCC_MCO_HSI 0x5
#define RCC_MCO_HSE 0x6
#define RCC_MCO_PLL_DIV_2 0x7

void rcc_hse_enable();
void rcc_hsi_disable();
void rcc_pll_enable();
void rcc_sys_clk_setup();
void enableMCO(uint8_t clk);
void rcc_io_enable(uint16_t port);
void rcc_i2c1_enable();
void rcc_usart1_enable();

#endif
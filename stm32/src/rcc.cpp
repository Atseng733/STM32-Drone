#include <rcc.h>

#if F_CPU/8000000 > 1 //calculate pll clock multiplier
	#define PLL_MUL F_CPU/PLL_CLK
#else
	#define PLL_MUL 0
#endif


#if PLL_CLK_SRC //determine pll clock base frequency
	#define PLL_CLK F_HSE
#else
	#define PLL_CLK F_HSI/2
#endif


void rcc_hse_enable() {
	RCC->CR |= HSEON; //set HSEON bit
	while(!(RCC->CR & HSERDY)); //wait for stable clock
	RCC->CFGR &= ~0x3;
	RCC->CFGR |= 0x1; //select hse as system clock
}

void rcc_hsi_disable() {
	RCC->CR &= ~HSION;
	while(RCC->CR & HSIRDY);
}

void rcc_pll_enable() {
	if(PLL_CLK_SRC) {
		rcc_hse_enable();
	}
	RCC->CFGR |= (PLL_CLK_SRC << 16); //select pll clock source
	RCC->CFGR |= ((PLL_MUL - 2) << 18); //select pll multiplier
	RCC->CR |= PLLON; //enable pll
	while(RCC->CR & PLLRDY); //wait until pll clock is ready
	RCC->CFGR &= ~0x3;
	RCC->CFGR |= 0x2; //select pll as system clock
}


void rcc_io_enable(uint16_t port) {
	RCC_GPIOEN_REGISTER |= port;
}
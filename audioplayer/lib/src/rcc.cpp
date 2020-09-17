#include <rcc.h>

void rcc_hse_enable() {
	RCC->CR |= RCC_CR_HSEON; //set HSEON bit
	while(!(RCC->CR & RCC_CR_HSERDY)); //wait for stable clock
}

void rcc_hsi_disable() {
	RCC->CR &= ~RCC_CR_HSION;
	while(RCC->CR & RCC_CR_HSIRDY);
}

void rcc_pll_enable() {
	uint8_t pll_factor = 2;
	while(PLL_RATIO*pll_factor < 50) {
		pll_factor++;
	}

	RCC->PLLCFGR &= ~(0x7FC << 6);
	RCC->PLLCFGR |= ((PLL_RATIO * pll_factor) << RCC_PLLCFGR_PLLN);
	RCC->PLLCFGR &= ~(0x3F);
	RCC->PLLCFGR |= (pll_factor << RCC_PLLCFGR_PLLM);
	
	//set APB1 domain clock to 42MHz and below
	if(APB1PSC == 2) {
		RCC->CFGR |= (0x4 << 10); //divide apb1 clock by 2
	}
	else if(APB1PSC == 4) {
		RCC->CFGR |= (0x5 << 10); //divide by 4
	}

	//set APB2 domain clock to 84MHz and below
	if(APB2PSC == 2) {
		RCC->CFGR |= (0x4 << 13); //divide apb2 clock by 2
	}

	//set clock speed for usb, rng, and sdio to 48MHz and below
	if(F_CPU > 48000000) { 
		RCC->PLLCFGR &= ~(0xF << 24);
		RCC->PLLCFGR |= (PLLQ << 24);
	}
	else {
		RCC->PLLCFGR &= ~(0xF << 24);
		RCC->PLLCFGR |= (0x2 << 24);
	}

	if(PLL_CLK_SRC) {
		rcc_hse_enable();
		RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC);
	}
	else if(!PLL_CLK_SRC) {
		RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC);
	}

	//set flash wait states
	FLASH->ACR |= FLASH_WAIT_STATES;

	RCC->CR |= RCC_CR_PLLON; //enable pll
	while(!(RCC->CR & RCC_CR_PLLRDY)); //wait until pll clock is ready
	RCC->CFGR &= ~0x3;
	RCC->CFGR |= 0x2; //select pll as system clock
	while(!((RCC->CFGR & 0x0000000F) == 0xA));
}

void rcc_sys_clk_setup() {
	if(F_CPU == 8000000) {
		rcc_hse_enable();
		RCC->CFGR &= ~0x3;
		RCC->CFGR |= 0x1; //select hse as system clock
	}
	else if(F_CPU > 8000000) {
		rcc_pll_enable();
	}
}

void enableMCO(uint32_t mcox, uint8_t clk_out) {
	
}

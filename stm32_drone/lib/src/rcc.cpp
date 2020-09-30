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
	if(PLL_CLK_SRC) {
		rcc_hse_enable();
	}

	RCC->CFGR |= RCC_CFGR_PLLXTPRE; //divide HSE pll entry by 2
	if(PLL_CLK_SRC) { //select pll clock source
		RCC->CFGR |= RCC_CFGR_PLLSRC;
	}

	if(PLL_MUL <= 16) {
		RCC->CFGR |= ((PLL_MUL - 2) << RCC_CFGR_PLLMUL); //select pll multiplier
	}
	
	//set APB1 domain clock to below the max
	if(APB1_PSC == 2) {
		RCC->CFGR |= (0x4 << RCC_CFGR_PPRE1); //divide apb1 clock by 2
	}
	else if(APB1_PSC == 4) {
		RCC->CFGR |= (0x5 << RCC_CFGR_PPRE1); //divide by 4
	}

	//set APB2 domain clock to below the max
	if(APB2_PSC == 2) {
		RCC->CFGR |= (0x4 << RCC_CFGR_PPRE2); //divide apb2 clock by 2
	}

	FLASH->ACR |= FLASH_WAIT_STATES; //set flash wait states

	RCC->CR |= RCC_CR_PLLON; //enable pll
	while(!(RCC->CR & RCC_CR_PLLRDY)); //wait until pll clock is ready
	RCC->CFGR &= ~0x3;
	RCC->CFGR |= 0x2; //select pll as system clock
	while(!((RCC->CFGR & 0x0000000F) == 0xA));
}

void rcc_sys_clk_setup() {
	if(PLL_EN) {
		rcc_pll_enable();
	}
	else if(!PLL_EN) {
		rcc_hse_enable();
	}
}

void enableMCO(uint8_t clk) {
	pinMode(GPIOA, 8, OUTPUT_HIGH_SPEED);
	pinConfig(GPIOA, 8, AFO_PP);
	RCC->CFGR &= ~(7 << 24);
	RCC->CFGR |= (clk << 24);
}


void rcc_io_enable(uint16_t port) {
	RCC_GPIOEN_REGISTER |= port;
	RCC_GPIOEN_REGISTER;
}

void rcc_i2c1_enable() {
	RCC_APB1ENR |= RCC_APB1ENR_I2C1EN;
	RCC_APB1ENR;
}

void rcc_usart1_enable() {
	RCC_APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC_APB2ENR;
}
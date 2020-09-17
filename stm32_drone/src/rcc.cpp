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
	RCC->CFGR |= (1 << 17); //divide HSE pll entry by 2
	RCC->CFGR |= (PLL_CLK_SRC << 16); //select pll clock source
	RCC->CFGR |= ((PLL_MUL - 2) << 18); //select pll multiplier
	if(APB1_PSC) { //set apb1 peripheral prescaler to 2 if F_CPU exceeds 36MHz
		RCC->CFGR |= (0x4 << 8);
	}
	RCC->CR |= RCC_CR_PLLON; //enable pll
	while(!(RCC->CR & RCC_CR_PLLRDY)); //wait until pll clock is ready
	RCC->CFGR &= ~0x3;
	RCC->CFGR |= 0x2; //select pll as system clock
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
#include <main.h>

usart USART;

int main(void) {
	USART.println("program start");
	GPIO_pinMode(GPIOA, 6, OUTPUT);
	GPIO_pinMode(GPIOD, 2, OUTPUT);
	GPIO_writeLow(GPIOA, 6);

	while(true) {
		delay_ms(1);
		GPIO_toggle(GPIOD, 2);
	}

	return 0;
}

void Reset_Handler() {
	//RCC->APB1RSTR |= (1 << 4);
	//RCC->APB1RSTR &= ~(1 << 4);
	//RCC->AHB1RSTR = 0xFFFFFFFF;
	//RCC->APB1RSTR = 0xFFFFFFFF;
	//RCC->AHB1RSTR = 0x00000000;
	//RCC->APB1RSTR = 0x00000000;
	
	RCC->CR |= 1 << 16; //enable external high-speed clock
	GPIO_CLK_ENABLE(GPIOA)
	GPIO_CLK_ENABLE(GPIOB)
	GPIO_CLK_ENABLE(GPIOC)
	GPIO_CLK_ENABLE(GPIOD)
	USART.init();
	TIM6_init();
	main();
	while(1);
}
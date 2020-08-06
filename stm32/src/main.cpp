#include <main.h>

usart2 USART2;
static uint32_t r = 0;
long count = 1;

int main(void) {
	USART2.putln("hello");
	USART2.putln("world");
	USART2.transmit();
	GPIO_pinMode(GPIOA, 6, OUTPUT);
	GPIO_pinMode(GPIOD, 2, OUTPUT);
	GPIO_writeLow(GPIOA, 6);
	while(true) {
		//ticks = count;
		delay_ms(1000);
		//count++;
		//delay_ms(1000);
		GPIO_toggle(GPIOD, 2);
	}

	return 0;
}

void Reset_Handler() {
	RCC->CR |= 1 << 16; //enable external high-speed clock
	GPIO_CLK_ENABLE(GPIOA)
	GPIO_CLK_ENABLE(GPIOB)
	GPIO_CLK_ENABLE(GPIOC)
	GPIO_CLK_ENABLE(GPIOD)
	USART2.init();
	TIM6_init();
	main();
}
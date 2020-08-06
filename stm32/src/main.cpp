#include <main.h>

usart USART;
static uint32_t r = 0;
long count = 1;

int main(void) {
	USART.println("Program start");
	GPIO_pinMode(GPIOA, 6, OUTPUT);
	GPIO_pinMode(GPIOD, 2, OUTPUT);
	GPIO_writeLow(GPIOA, 6);
	USART.print("NVIC_ISER1: "); USART.println(NVIC_ISER->ISER1, 16);
	USART.print("CR1 Register: "); USART.println(TIM6->CR1, 16);
	while(true) {
		//ticks = count;
		delay_ms(1000);
		USART.print("NVIC_ISER1: "); USART.println(NVIC_ISER->ISER1, 16);
		USART.print("CR1 Register: "); USART.println(TIM6->CR1, 16);
		USART.print("Static register: "); USART.println(r, 16);
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
	USART.init();
	TIM6_init();
	main();
}
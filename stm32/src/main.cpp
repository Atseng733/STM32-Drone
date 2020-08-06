#include <main.h>

char str[32];

uint8_t a = 0x3C;

int main(void) {
	ssd1306 display(0x3C);

	USART.println("Starting Program");
	GPIO_pinMode(GPIOA, 6, OUTPUT);
	GPIO_pinMode(GPIOD, 2, OUTPUT);
	GPIO_writeLow(GPIOA, 6);
	USART.println(display.get_addr(), 16);
	display.begin();
	display.print("test");
	display.display();


	while(true) {
		//I2C.write(0x3C, 0x00, 0xAF);
		delay_ms(1000);
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
	I2C.init();
	main();
}
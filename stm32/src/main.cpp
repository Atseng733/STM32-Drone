#include <main.h>

int main(void) {
	pinMode(GPIOC, 13, OUTPUT);
	writeHigh(GPIOC, 13);

	USART.putln("Program Start");
	USART.putln("Program test");
	USART.transmit();


	
	while(true) {
		toggle(GPIOC, 13);
		for(int i = 0; i < 500000; i++) {
			asm("nop");
		}
		USART.putln("test");
		USART.transmit();
	}

	return 0;
}

void Reset_Handler() {
	rcc_pll_enable();
	rcc_io_enable(RCC_GPIOA);
	rcc_io_enable(RCC_GPIOB);
	rcc_io_enable(RCC_GPIOC);
	USART.init();
	main();
}
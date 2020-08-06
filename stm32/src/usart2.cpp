#include <usart2.h>

usart2 USART;
char usart_buffer[256];
char usart2_str[32];
char* tx_index;
char* buffer_index;

void usart2::init() {
	tx_index = usart_buffer;
	buffer_index = usart_buffer;

	RCC->APB2ENR |= 0x0010; //enable usart1 clock
	USART1->CR1 |= 0x2000; //enable usart
	USART1->BRR = BRR_VALUE; //set baud rate to (16MHz / (8 * 2 * BRR )) 	BRR = 52.0625 = (34h + 1h/16d)

	GPIO_pinMode(GPIOB, 6, ALTFN);
	GPIO_pinAFNConfig(GPIOB, 6, USART_AFN, PUSH_PULL, LOW_SPEED, FLOATING); //set PB6 to usart tx alternate function

	USART1->CR1 |= 0x0008; //enable the transmitter

	println("USART2 Initialized");
}

void usart2::putc(char c) {
	*buffer_index = c;

	if((buffer_index + 1) == (usart_buffer + 256)) {
		buffer_index = usart_buffer;
	}
	else {
		buffer_index++;
	}
}

void usart2::put(char* str) {
	while(*str != 0) {
		putc(*str);
		str++;
	}
}

void usart2::putln(char* str) {
	while(*str != 0) {
		putc(*str);
		str++;
	}

	putc('\n');
}

void usart2::transmit() {
	while(tx_index != buffer_index) {
		USART1->DR = *tx_index;

		if((tx_index + 1) == (usart_buffer + 256)) {
			tx_index = usart_buffer;
		}
		else {
			tx_index++;
		}

		for(int i = 0; i < 500; i++) {
			asm("nop");
		}
	}
}

void usart2::printc(char c) {
	putc(c);
	transmit();
}

void usart2::print(char* str) {
	put(str);
	transmit();
}

void usart2::println(char* str) {
	putln(str);
	transmit();
}

void usart2::print(int64_t i, uint8_t base) {
	put(itoa(usart2_str, i, base));
	transmit();
}

void usart2::println(int64_t i, uint8_t base) {
	putln(itoa(usart2_str, i, base));
	transmit();
}
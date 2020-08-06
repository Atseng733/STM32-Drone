#include <usart2.h>

char buffer[256];
char* tx_index;
char* buffer_index;

void usart2::init() {
	tx_index = buffer;
	buffer_index = buffer;

	RCC->APB2ENR |= 0x0010; //enable usart1 clock
	USART1->CR1 |= 0x2000; //enable usart
	USART1->BRR = 0x0341; //set baud rate to (16MHz / (8 * 2 * BRR )) 	BRR = 52.0625 = (34h + 1h/16d)

	GPIO_pinMode(GPIOB, 6, ALTFN);
	GPIO_pinAFNConfig(GPIOB, 6, USART_AFN, PUSH_PULL, LOW_SPEED, FLOATING); //set PB6 to usart tx alternate function

	USART1->CR1 |= 0x0008; //enable the transmitter
}

void usart2::putc(char c) {
	*buffer_index = c;

	if((buffer_index + 1) == (buffer + 256)) {
		buffer_index = buffer;
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

		if((tx_index + 1) == (buffer + 256)) {
			tx_index = buffer;
		}
		else {
			tx_index++;
		}
		
		for(int i = 0; i < 5000; i++) {
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
#include <usart.h>

usart USART;
char usart_buffer[256];
char usart_str[32];
char* tx_index;
char* buffer_index;

void usart::init() {
	tx_index = usart_buffer;
	buffer_index = usart_buffer;

	RCC_USART1EN_REGISTER |= RCC_USART1EN; //enable usart1 clock
	USART1->CR1 |= 0x2000; //enable usart
	USART1->BRR = ((uint16_t)BRR_MANTISSA(USART_BAUD) << 4) | BRR_FRACTION(USART_BAUD); //set baud rate to (16MHz / (8 * 2 * BRR )) 	BRR = 52.0625 = (34h + 1h/16d)
	//USART1->BRR = 0x0045; //set baud rate to (16MHz / (8 * 2 * BRR )) 	BRR = 52.0625 = (34h + 1h/16d)

	pinMode(GPIOA, 9, OUTPUT);
	pinConfig(GPIOA, 9, AFO_PP); //set PB6 to usart tx alternate function

	USART1->CR1 |= 0x0008; //enable the transmitter

	println("USART Initialized");
}

void usart::putc(char c) {
	*buffer_index = c;

	if((buffer_index + 1) == (usart_buffer + 256)) {
		buffer_index = usart_buffer;
	}
	else {
		buffer_index++;
	}
}

void usart::put(char* str) {
	while(*str != 0) {
		putc(*str);
		str++;
	}
}

void usart::putln(char* str) {
	while(*str != 0) {
		putc(*str);
		str++;
	}

	putc('\n');
}

void usart::transmit() {

	while(tx_index != buffer_index) {
		USART1->DR = *tx_index;

		if((tx_index + 1) == (usart_buffer + 256)) {
			tx_index = usart_buffer;
		}
		else {
			tx_index++;
		}

		while(!(USART1->SR & USART_TXE));
	}
}

void usart::printc(char c) {
	putc(c);
	transmit();
}

void usart::print(char* str) {
	put(str);
	transmit();
}

void usart::println(char* str) {
	putln(str);
	transmit();
}

void usart::print(int64_t i, uint8_t base) {
	put(itoa(usart_str, i, base));
	transmit();
}

void usart::println(int64_t i, uint8_t base) {
	putln(itoa(usart_str, i, base));
	transmit();
}
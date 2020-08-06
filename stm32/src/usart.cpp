#include <usart.h>

usart serial;
char* index;
char usart_str[32];
bool newline = false;
volatile bool txc = false;

void usart::init() {
	RCC->APB2ENR |= 0x0010; //enable usart1 clock
	USART1->CR1 |= 0x2000; //enable usart
	USART1->BRR = 0x0341; //set baud rate to (16MHz / (8 * 2 * BRR )) BRR = 52.0625 = (34h + 1/16)
	USART1->CR1 |= 0x0080; //enable txe interrupt

	GPIO_pinMode(GPIOB, 6, ALTFN);
	GPIO_pinAFNConfig(GPIOB, 6, USART_AFN, PUSH_PULL, LOW_SPEED, FLOATING); //set PB6 to usart tx alternate function

	USART1->CR1 |= 0x0008; //enable the transmitter
	serial.println("usart enabled");
}

void usart::printc(char c) {
	USART1->DR = c;
}

void usart::print(char* str) {
	index = str;
	txc = false;
	enableInterrupt(37); //begin transmission by enabling interrupt
	while(!txc); //wait for tx complete
}

void usart::print(uint64_t w) {
	itoa(usart_str, w, 10);
	index = usart_str;
	txc = false;
	enableInterrupt(37); //begin transmission by enabling interrupt
	while(!txc); //wait for tx complete
}

void usart::print(uint64_t w, uint8_t base) {
	itoa(usart_str, w, base);
	index = usart_str;
	txc = false;
	enableInterrupt(37); //begin transmission by enabling interrupt
	while(!txc); //wait for tx complete
}

void usart::println(char* str) {
	newline = true;
	print(str);
}

void usart::println(uint64_t w) {
	newline = true;
	print(w);
}

void usart::println(uint64_t w, uint8_t base) {
	newline = true;
	print(w, base);
}

void USART1_Handler() {
	if(*index == 0) {
		if(newline) {
			USART1->DR = '\n';
		}
		disableInterrupt(37);
		newline = false;
		txc = true; //transmit complete
	}
	else {
		USART1->DR = *index;
		index++;
	}
}
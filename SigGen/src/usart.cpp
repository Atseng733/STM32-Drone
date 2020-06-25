#include <usart.h>
#include <debug.h>

void usart_init() {
	cli();
	UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
	UBRR0L = (uint8_t)(UBRR_VALUE);
	UCSR0A = 0x00;
	UCSR0B = 0x48;
	UCSR0C |= 0x06;
	sei();
}

void usart_test() {
	printc('A');
}

void printc(uint8_t c) {
	#ifdef USART_INIT
	#else
	usart_init();
	#define USART_INIT 1
	#endif
	//wait until previous transmit is complete
	while(!(UCSR0A&(1<<5)));
	//send data
	UDR0 = c;
}
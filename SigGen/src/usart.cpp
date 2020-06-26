#include <usart.h>
#include <debug.h>

char* index;
bool transmitting = false;

ISR(USART_UDRE_vect) {
	if(*index != 0) {
		UDR0 = *index;
		index++;
	}
	else {
		transmitting = false;
	}
}

void usart_init() {
	cli();
	UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
	UBRR0L = (uint8_t)(UBRR_VALUE);
	UCSR0A = 0x00;
	UCSR0B = 0x68;
	UCSR0C |= 0x06;
	sei();
}

void usart_test() {
	print("Testing USART communication");
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

void printcint(uint8_t c) {
	#ifdef USART_INIT
	#else
	usart_init();
	#define USART_INIT 1
	#endif

	while(transmitting);

	UDR0 = c;
}

void print(char str[]) {
	#ifdef USART_INIT
	#else
	usart_init();
	#define USART_INIT 1
	#endif
	if(transmitting == false) {
		index = str;
		printc(str[0]);
		transmitting = true;
	}
}
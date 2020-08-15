#include <usart.h>

usart USART;
char usart_tx_buffer[256];
char* tx_buffer_index;
char* tx_index;

uint8_t USART_RxBuffer[256];
uint32_t USART_RxBufferCount;
uint32_t USART_RxCount;

char usart_str[32];

uint8_t* TxBufferIT;
uint8_t TxState;
uint32_t TxLen;

uint8_t* RxBuffer;
volatile uint8_t RxState;
volatile uint32_t RxLen;

void usart::init(USART_Typedef* usartx, uint32_t baud) {
	tx_index = usart_tx_buffer;
	tx_buffer_index = usart_tx_buffer;

	RxState = 0;

	rcc_usart1_enable(); //enable usart1 clock
	usartx->CR1 |= USART_CR1_UE; //enable usart
	usartx->BRR = ((uint16_t)BRR_MANTISSA(baud) << 4) | BRR_FRACTION(baud); //set baud rate

	pinMode(GPIOA, 9, OUTPUT);
	pinConfig(GPIOA, 9, AFO_PP); //set PA9 to usart tx alternate function
	pinMode(GPIOA, 10, INPUT);
	pinConfig(GPIOA, 10, INPUT_PUPD); //set PA10 to usart tx alternate function
	writeHigh(GPIOA, 10);

	usartx->CR1 |= USART_CR1_TE; //enable the transmitter
	usartx->CR1 |= USART_CR1_RE; //enable the receiver

	println("USART Initialized");
}



void usart::putc(char c) {
	*tx_buffer_index = c;

	if((tx_buffer_index + 1) == (usart_tx_buffer + 255)) {
		tx_buffer_index = usart_tx_buffer;
	}
	else {
		tx_buffer_index++;
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
	while(tx_index != tx_buffer_index) {
		USART1->DR = *tx_index;

		if((tx_index + 1) == (usart_tx_buffer + 256)) {
			tx_index = usart_tx_buffer;
		}
		else {
			tx_index++;
		}

		while(!(USART1->SR & USART_SR_TXE));
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

void usart::println(double d) {
	putln(dtoa(usart_str, d));
	transmit();
}

uint8_t usart::receiveIT(uint8_t* dest,  uint32_t len) {
	while(RxState != 0);
	uint8_t rxstate = RxState;
	uint8_t temp;

	if(rxstate != USART_BUSY_RX) {
		RxState = USART_BUSY_RX;
		RxBuffer = dest;
		RxLen = len;

		enableInterrupt(37);
		temp = USART1->DR;
		USART1->CR1 |= USART_CR1_RXNEIE;
	}

	while(RxState != 0);
	return rxstate;
}

uint8_t usart::read(uint8_t* dest, uint32_t len) {
	uint8_t temp = USART1->DR;
	while(len > 0) {
		while(!(USART1->SR & USART_SR_RXNE));
		*dest = USART1->DR;
		dest++;
		len--;
		if(USART1->SR & USART_SR_ORE) {
			USART.println("ORE");
		}
		if(USART1->SR & USART_SR_NE) {
			USART.println("NE");
		}
		if(USART1->SR & USART_SR_FE) {
			USART.println("FE");
		}
		if(USART1->SR & USART_SR_PE) {
			USART.println("PE");
		}
	}
	return 1;
}

uint8_t usart::read() {
	uint8_t temp;

	while(!(USART1->SR & USART_SR_RXNE));
	temp = USART1->DR;
	
	return temp;
}

void USART1_Handler() {
	uint8_t temp;

	if(USART1->SR & USART_SR_RXNE) {
		if(RxLen > 0) {
			*(RxBuffer++) = USART1->DR;
			RxLen--;
		}
		if(RxLen == 0) {
			disableInterrupt(37);
			USART1->CR1 &= ~USART_CR1_RXNEIE;
			RxState = USART_READY;
		}
	}

	if(USART1->SR & USART_SR_ORE) {
		temp = USART1->DR; 
		disableInterrupt(37);
		USART1->CR1 &= ~USART_CR1_RXNEIE;
		RxState = USART_READY;
	}
}
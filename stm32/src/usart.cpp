#include <usart.h>

usart USART;
char USART_TxBuffer[128];
char USART_TxBuffer_w;
char USART_TxBuffer_r;

uint8_t USART_RxBuffer[128];
uint8_t USART_Rx_rIndex;
uint8_t USART_Rx_wIndex;

char usart_str[32];


uint8_t USART_RxBufferIT[256];
uint8_t USART_RxBufferIT_r;
uint8_t USART_RxBufferIT_w;

volatile bool RxState;
uint16_t RxLen;
uint8_t* RxData;

void usart::init(USART_Typedef* usartx, uint32_t baud) {
	USART_TxBuffer_r = 0;
	USART_TxBuffer_w = 0;
	USART_Rx_rIndex = 0;
	USART_Rx_wIndex = 0;
	USART_RxBufferIT_r = 0;
	USART_RxBufferIT_w = 0;
	RxState = false;


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
	USART_TxBuffer[USART_TxBuffer_w++] = c;

	USART_TxBuffer_w &= 0xFF;
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

void usart::putln(int64_t i, uint8_t base) {
	putln(itoa(usart_str, i, base));
}

void usart::transmit() {
	while(USART_TxBuffer_r != USART_TxBuffer_w) {
		USART1->DR = USART_TxBuffer[USART_TxBuffer_r++];

		USART_TxBuffer_r &= 0xFF;

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
	//while(RxState);
	//if(USART1->SR & USART_SR_IDLE) {
		RxState = true;
		RxData = dest;
		RxLen = len;
		USART1->CR1 |= USART_CR1_RXNEIE;
		enableInterrupt(37);
	//}
	//else {
	//	return 0;
	//}

	return 1;
}


uint8_t usart::readSync(uint8_t* dest,  uint32_t len, uint8_t start) {
	uint8_t temp;
	uint8_t sync = 0;
	uint8_t w_index = 0;
	
	while(w_index < len)
	{
		if(USART1->SR & USART_SR_RXNE) 
		{
			USART_RxBuffer[USART_Rx_wIndex++] = USART1->DR;
			USART_Rx_wIndex &= 0xFF;
		}

	 	if (USART_Rx_wIndex != USART_Rx_rIndex)
	 	{
	 		temp = USART_RxBuffer[USART_Rx_rIndex++];
	 		USART_Rx_rIndex &= 0xFF;

	 		if (temp == start)
	 		{
	 			sync = 1;
	 			w_index = 0;
	 			dest[w_index++] = temp;
	 		}
	 		else if(sync == 1)
	 		{
				dest[w_index++] = temp;
	 		}
	 	}
	}

	return 1;
}


uint8_t usart::read(uint8_t* dest, uint32_t len, uint8_t start) {
	uint8_t temp;
	uint8_t i = 0;
	bool sync = false;

	while(i < len)
	{
	 	temp = USART_RxBufferIT[USART_RxBufferIT_r++];
	 	USART_RxBufferIT_r &= 0xFF;

	 	if(USART_RxBufferIT_r != USART_RxBufferIT_w) {
		 	if(temp == start) {
		 		sync = true;
		 		dest[i++] = temp;
		 	}
		 	else if(sync) {
		 		dest[i++] = temp;
		 	}
		 	//dest[i++] = USART_RxBufferIT[USART_RxBufferIT_r++];
		 	//USART_RxBufferIT_r &= 0xFF;
	 	}
	}
	

	
	return 1;
}

uint8_t usart::read() {
	uint8_t temp;

	while(USART_RxBufferIT_w != USART_RxBufferIT_r)
	{
	 	temp = USART_RxBufferIT[USART_RxBufferIT_r++];
	 	USART_RxBufferIT_r &= 0xFF;
	}

	return 1;
}

void USART1_Handler() {
	if(USART1->SR & USART_SR_RXNE) 
	{
		USART_RxBufferIT[USART_RxBufferIT_w++] = USART1->DR;
		//USART_RxBufferIT_w &= 0xFF;
		if(USART_RxBufferIT_w == 255) {
			USART1->CR1 &= ~USART_CR1_RXNEIE;
			RxState = false;
		}
		toggle(GPIOB, 9);
		/*if(RxLen == 0) {
			USART1->CR1 &= ~USART_CR1_RXNEIE;
			RxState = false;
		}*/
	}
}
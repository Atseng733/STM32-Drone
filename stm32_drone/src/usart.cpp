#include <usart.h>
usart Serial1;
usart Serial2;

void usart::Init(USART_Typedef* usartx, uint32_t baud, uint8_t mode) {
	USARTx = usartx;

	if(USARTx == USART1) {
		USART1_CLK_EN;
		pinMode(GPIOA, 9, OUTPUT);
		pinConfig(GPIOA, 9, AFO_PP); //set PA9 to usart tx alternate function
		pinMode(GPIOA, 10, INPUT);
		pinConfig(GPIOA, 10, INPUT_PUPD); //set PA10 to usart tx alternate function
		writeHigh(GPIOA, 10);

		USARTx->BRR = (BRR_MANTISSA(USARTDIV(baud, F_CPU)) << 4) | BRR_FRACTION(USARTDIV(baud, F_CPU));
	}
	else if(USARTx == USART2) {
		USART2_CLK_EN;
		pinMode(GPIOA, 2, OUTPUT);
		pinConfig(GPIOA, 2, AFO_PP); //set PA2 to usart tx alternate function
		pinMode(GPIOA, 3, INPUT);
		pinConfig(GPIOA, 3, INPUT_PUPD); //set PA3 to usart rx input
		writeHigh(GPIOA, 3);

		USARTx->BRR = (BRR_MANTISSA(USARTDIV(baud, APB1_CLK)) << 4) | BRR_FRACTION(USARTDIV(baud, APB1_CLK));
	}
	USARTx->CR1 |= USART_CR1_UE; //enable usart

	//set baudrate register
	
	//(*usart_config).USARTx->BRR = 0x00D0;

	switch(mode) {
		case USART_MODE_TX:
			USARTx->CR1 |= USART_CR1_TE; //enable the transmitter
			break;
		case USART_MODE_RX:
			USARTx->CR1 |= USART_CR1_RE; //enable the receiver
			break;
		case USART_MODE_TXRX:
			USARTx->CR1 |= USART_CR1_TE; //enable both
			USARTx->CR1 |= USART_CR1_RE; 
			break;
	}
}

void usart::USART_InterruptEnable() {
	if(USARTx == USART1) {
		enableInterrupt(37);
	}
	else if(USARTx == USART2) {
		enableInterrupt(38);
	}
}

uint8_t usart::GetFlagStatus(uint32_t reg, uint32_t flag) {
	return (reg & flag);
}

void usart::printc(char c) {
	while(!GetFlagStatus(USARTx->SR, USART_SR_TXE));
	USARTx->DR = c;
}

void usart::print(char* str) {
	while(*str != 0) {
		while(!GetFlagStatus(USARTx->SR, USART_SR_TXE)); //wait until data register empty
		USARTx->DR = *(str++); //send data
	}

	while(!GetFlagStatus(USARTx->SR, USART_SR_TC));
}

void usart::println(char* str) {
	while(*str != 0) {
		while(!GetFlagStatus(USARTx->SR, USART_SR_TXE)); //wait until data register empty
		USARTx->DR = *(str++); //send data
	}

	while(!GetFlagStatus(USARTx->SR, USART_SR_TXE));
	USARTx->DR = '\n';

	while(!GetFlagStatus(USARTx->SR, USART_SR_TC));
}

void usart::println(int64_t num, uint8_t base) {
	println(itoa(stdlib_str, num, base));
}

void usart::sendIT(char* str) {
	USART_InterruptEnable();
	USARTx->CR1 |= USART_CR1_TXEIE;
}

void usart::receiveIT(uint16_t len) {
	//RxLen = len;

	USART_InterruptEnable();
	USARTx->CR1 |= USART_CR1_RXNEIE;
}

void usart::read(uint8_t* data, uint16_t len) {
	uint16_t i = 0;
	uint8_t temp;
	/*while(RxBuffer_w != RxBuffer_r) {
		*(data++) = RxBuffer[RxBuffer_r++];
		RxBuffer_r &= RX_BUFFER_SIZE;
	}*/
	while(i < len) {
		temp = RxBuffer[RxBuffer_r++];
		RxBuffer_r &= RX_BUFFER_SIZE;
		data[i++] = temp;
	}
}

void usart::readSync(uint8_t* data, uint16_t len, uint8_t syncByte) {
	uint16_t i = 0;
	uint8_t temp;
	bool sync = false;

	while(i < len) {
		temp = RxBuffer[RxBuffer_r++];
		RxBuffer_r &= RX_BUFFER_SIZE;

	 	if (temp == syncByte)
	 	{
	 		sync = true;
	 		data[i++] = temp;
	 	}
	 	else if(sync)
	 	{
			data[i++] = temp;
	 	}
	}
}

void usart::USART_ISR() {
	uint8_t temp;

	if(GetFlagStatus(USARTx->CR1, USART_CR1_TXEIE)) {
		if(GetFlagStatus(USARTx->SR, USART_SR_TXE)) {
			USARTx->DR = 'c';
		}
	}
	
	if(GetFlagStatus(USARTx->CR1, USART_CR1_RXNEIE)) {
		if(GetFlagStatus(USARTx->SR, USART_SR_RXNE)) {
			//if(RxLen > 0) {
				RxBuffer[RxBuffer_w++] = USARTx->DR;
				RxBuffer_w &= RX_BUFFER_SIZE;
			//	RxLen--;
			//}
			
			/*if(RxLen == 0) {
				USARTx->CR1 &= ~(USART_CR1_RXNEIE);
			}*/
		}
	}


}

void USART1_Handler() {
	Serial1.USART_ISR();
}

void USART2_Handler() {
	Serial2.USART_ISR();
}
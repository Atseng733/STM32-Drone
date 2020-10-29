#include <usart.h>
usart Serial1;
usart Serial2;
usart Serial3;

volatile bool dataReady = false;

void usart::Init(USART_Struct* pusart_struct, uint32_t baud, uint8_t mode) {
	pUSART_Struct = pusart_struct;
	dataReady = false;

	if(pUSART_Struct->USARTx == USART1) {
		USART1_CLK_EN;
		pUSART_Struct->USARTx->BRR = (BRR_MANTISSA(USARTDIV(baud, APB2_CLK)) << 4) | BRR_FRACTION(USARTDIV(baud, APB2_CLK));
	}
	else if(pUSART_Struct->USARTx == USART2) {
		USART2_CLK_EN;
		pUSART_Struct->USARTx->BRR = (BRR_MANTISSA(USARTDIV(baud, APB1_CLK)) << 4) | BRR_FRACTION(USARTDIV(baud, APB1_CLK));
	}
	else if(pUSART_Struct->USARTx == USART3) {
		USART3_CLK_EN;
		pUSART_Struct->USARTx->BRR = (BRR_MANTISSA(USARTDIV(baud, APB1_CLK)) << 4) | BRR_FRACTION(USARTDIV(baud, APB1_CLK));
	}

	pUSART_Struct->USARTx->CR1 |= USART_CR1_UE; //enable usart

	switch(mode) {
		case USART_MODE_TX:
			pUSART_Struct->USARTx->CR1 |= USART_CR1_TE; //enable the transmitter
			break;
		case USART_MODE_RX:
			pUSART_Struct->USARTx->CR1 |= USART_CR1_RE; //enable the receiver
			break;
		case USART_MODE_TXRX:
			pUSART_Struct->USARTx->CR1 |= USART_CR1_TE; //enable both
			pUSART_Struct->USARTx->CR1 |= USART_CR1_RE; 
			break;
	}
}

void usart::USART_InterruptEnable() {
	if(pUSART_Struct->USARTx == USART1) {
		enableInterrupt(37);
	}
	else if(pUSART_Struct->USARTx == USART2) {
		enableInterrupt(38);
	}
	else if(pUSART_Struct->USARTx == USART3) {
		enableInterrupt(39);
	}
}

uint8_t usart::GetFlagStatus(uint32_t reg, uint32_t flag) {
	return (reg & flag);
}

void usart::printc(char c) {
	while(!GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TXE));
	pUSART_Struct->USARTx->DR = c;
}

void usart::print(char* str) {
	while(*str != 0) {
		while(!GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TXE)); //wait until data register empty
		pUSART_Struct->USARTx->DR = *(str++); //send data
	}

	while(!GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TC));
}

void usart::println(char* str) {
	while(*str != 0) {
		while(!GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TXE)); //wait until data register empty
		pUSART_Struct->USARTx->DR = *(str++); //send data
	}

	while(!GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TXE));
	pUSART_Struct->USARTx->DR = '\n';

	while(!GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TC));
}

void usart::println(int32_t num, uint8_t base) {
	char str[32];
	println(itoa(str, num, base));
}

void usart::printd(double d, uint8_t prec) {
	char str[32];
	println(dtoa(str, d, prec));
}

void usart::sendIT(char* str) {
	USART_InterruptEnable();
	pUSART_Struct->USARTx->CR1 |= USART_CR1_TXEIE;
}

void usart::receiveIT() {
	USART_InterruptEnable();
	pUSART_Struct->USARTx->CR1 |= USART_CR1_RXNEIE;
}

void usart::read(uint8_t* data, uint16_t len) {
	uint16_t i = 0;
	uint8_t temp;

	while(i < len) {
		temp = pUSART_Struct->RxBuffer[pUSART_Struct->RxBuffer_r++];
		pUSART_Struct->RxBuffer_r &= RX_BUFFER_SIZE;
		data[i++] = temp;
	}
}

uint8_t usart::readSync(uint8_t* data, uint16_t len, uint8_t syncByte) {
	uint16_t i = 0;
	uint8_t temp;
	bool sync = false;

	if(!dataReady) {
		return 0;
	}

	while(i < len) {
		temp = pUSART_Struct->RxBuffer[pUSART_Struct->RxBuffer_r++];
		pUSART_Struct->RxBuffer_r &= RX_BUFFER_SIZE;

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

	dataReady = false;
	return 1;
}

void usart::USART_ISR() {
	uint8_t temp;

	if(GetFlagStatus(pUSART_Struct->USARTx->CR1, USART_CR1_TXEIE)) {
		if(GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_TXE)) {
		}
	}
	
	if(GetFlagStatus(pUSART_Struct->USARTx->CR1, USART_CR1_RXNEIE)) {
		if(GetFlagStatus(pUSART_Struct->USARTx->SR, USART_SR_RXNE)) {
			pUSART_Struct->RxBuffer[pUSART_Struct->RxBuffer_w++] = pUSART_Struct->USARTx->DR;
			pUSART_Struct->RxBuffer_w &= RX_BUFFER_SIZE;
			dataReady = true;
		}
	}


}

void USART1_Handler() {
	Serial1.USART_ISR();
}

void USART2_Handler() {
	Serial2.USART_ISR();
}

void USART3_Handler() {
	Serial3.USART_ISR();
}
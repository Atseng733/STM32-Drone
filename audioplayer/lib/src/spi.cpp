#include <spi.h>

void SPI_Init(SPI_Struct* pSPI_Struct) {
	SPI2_CLK_EN;

	//pSPI_Struct->SPIx->CR2 |= SPI_CR2_SSOE;
	// pSPI_Struct->SPIx->CR1 |= pSPI_Struct->CR1;
	// pSPI_Struct->SPIx->CR2 |= pSPI_Struct->CR2;
	pSPI_Struct->SPIx->CR1 |= (0b111 << SPI_CR1_BR);
	pSPI_Struct->SPIx->CR1 |= SPI_CR1_SSM;
	pSPI_Struct->SPIx->CR1 |= SPI_CR1_SSI;
	pSPI_Struct->SPIx->CR1 |= SPI_CR1_MSTR;
	pSPI_Struct->SPIx->CR1 |= SPI_CR1_SPE;
	pSPI_Struct->InitState = 1;
}

uint8_t SPI_Tx(SPI_Struct* pSPI_Struct, uint16_t data) {
	if(pSPI_Struct->InitState != 1) {
		return 0;
	}

	pSPI_Struct->SPIx->DR = data;
	while(!(pSPI_Struct->SPIx->SR & SPI_SR_TXE));
	while((pSPI_Struct->SPIx->SR & SPI_SR_BSY));

	return 1;
}

uint8_t SPI_Tx(SPI_Struct* pSPI_Struct, uint16_t* data, uint8_t count) {
	if(pSPI_Struct->InitState != 1) {
		return 0;
	}
	pSPI_Struct->SPIx->DR = 0xFF;
	while(!(pSPI_Struct->SPIx->SR & SPI_SR_TXE));

	for(int i = 0; i < count; i++) {
		pSPI_Struct->SPIx->DR = data[i];
		while(!(pSPI_Struct->SPIx->SR & SPI_SR_TXE));
	}
	while((pSPI_Struct->SPIx->SR & SPI_SR_BSY));

	return 1;
}

uint16_t SPI_Rx(SPI_Struct* pSPI_Struct) {
	SPI_Tx(pSPI_Struct, 0xFF);
	while(!(pSPI_Struct->SPIx->SR & SPI_SR_RXNE));
	return pSPI_Struct->SPIx->DR;
}

uint16_t* SPI_Rx(SPI_Struct* pSPI_Struct, uint16_t* dest, uint8_t count) {
	uint16_t temp;

	temp = SPI_Rx(pSPI_Struct);
	while(temp == 0xFF) {
		temp = SPI_Rx(pSPI_Struct);
	}

	for(int i = 0; i < count; i++) {
		dest[i] = temp;
		temp = SPI_Rx(pSPI_Struct);
	}

	return dest;
}
#include <spi.h>

void SPI_Init(SPI_Struct *pSPI_Struct) {
    //Master mode
    //GPIO
    if(pSPI_Struct->SPIx == SPI1) {
        //SCK PA5
        pinMode(GPIOA, 5, OUTPUT);
        pinConfig(GPIOA, 5, AFO_PP);

        //MISO PA6
        pinMode(GPIOB, 4, INPUT);
        pinConfig(GPIOB, 4, INPUT_PUPD);
        writeHigh(GPIOB, 4);

        //MOSI PA7
        pinMode(GPIOB, 5, OUTPUT);
        pinConfig(GPIOB, 5, AFO_PP);
    }

    /*
    1.Select the BR[2:0] bits to define the serial clock baud rate (see SPI_CR1 register).
    2.Select the CPOL and CPHA bits to define one of the four relationships between the data transfer and the serial clock (see Figure 240). 
    3.Set the DFF bit to define 8- or 16-bit data frame format
    4.Configure the LSBFIRST bit in the SPI_CR1 register to define the frame format. 
    5.If the NSS pin is required in input mode, in hardware mode, connect the NSS pin to a high-level signal during the complete byte transmit sequence. In NSS software mode, set the SSM and SSI bits in the SPI_CR1 register. If the NSS pin is required in output mode, the SSOE bit only should be set. 
    6.The MSTR and SPE bits must be set (they remain set only if the NSS pin is connected to a high-level signal).
    */

    if(pSPI_Struct->SPIx == SPI1) {
        SPI1_CLK_EN;
    }

    //Set baudrate first by masking bits
    pSPI_Struct->SPIx->CR1 |= (pSPI_Struct->CR1 & 0x0038);
    
    //Clock phase and polarity
    pSPI_Struct->SPIx->CR1 |= (pSPI_Struct->CR1 & 0x0003);

    //Set 8 or 16 bit frame format
    pSPI_Struct->SPIx->CR1 |= (pSPI_Struct->CR1 & 0x0800);

    //LSB or MSB transmitted first
    pSPI_Struct->SPIx->CR1 |= (pSPI_Struct->CR1 & 0x0080);

    //configure NSS pin
    //if Software slave management enabled
    if(pSPI_Struct->SPIx->CR1 & SPI_CR1_SSM) {
        pSPI_Struct->SPIx->CR1 |= (pSPI_Struct->CR1 & 0x0200);
    }
    else {
        if(pSPI_Struct->SPIx == SPI1) {
            pinMode(GPIOA, 4, INPUT);
            pinConfig(GPIOA, 4, INPUT_PUPD);
            writeHigh(GPIOA, 4);
        }
    }

    //set MSTR and SPE bits
    pSPI_Struct->SPIx->CR1 |= SPI_CR1_MSTR | SPI_CR1_SPE;

    pSPI_Struct->InitState = 1;
}

uint8_t SPI_Tx(SPI_Struct* pSPI_Struct, uint16_t data) {
	if(pSPI_Struct->InitState != 1) {
		return 0;
	}

	pSPI_Struct->SPIx->DR = data;
    Serial2.printc('c');
	while(!(pSPI_Struct->SPIx->SR & SPI_SR_TXE));
    while(!(pSPI_Struct->SPIx->SR & SPI_SR_RXNE));
    uint16_t temp = pSPI_Struct->SPIx->DR;

	return 1;
}

uint8_t SPI_Tx(SPI_Struct* pSPI_Struct, uint16_t* data, uint8_t count) {
	if(pSPI_Struct->InitState != 1) {
		return 0;
	}

	for(int i = 0; i < count; i++) {
		pSPI_Struct->SPIx->DR = data[i];
		while(!(pSPI_Struct->SPIx->SR & SPI_SR_TXE));
	}
	while(pSPI_Struct->SPIx->SR & SPI_SR_BSY);

	return 1;
}

uint16_t SPI_Rx(SPI_Struct* pSPI_Struct) {
	if(pSPI_Struct->SPIx->SR & SPI_SR_RXNE) {
        Serial2.printc('i');
		return pSPI_Struct->SPIx->DR;
	}
	else {
        Serial2.printc('e');
		SPI_Tx(pSPI_Struct, 0xFF);
		while(!(pSPI_Struct->SPIx->SR & SPI_SR_RXNE));
		return pSPI_Struct->SPIx->DR;
	}
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
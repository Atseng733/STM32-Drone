#ifndef SPI_H
#define SPI_H

#include <boards.h>
#include <usart.h>
#include <timer.h>

typedef struct {
	uint8_t InitState;
	SPI_Typedef* SPIx;
	GPIO_Typedef* NSS_PORT;
	uint8_t NSS_PIN;
	uint16_t CR1;
	uint8_t CR2;
} SPI_Struct;


void SPI_Init(SPI_Struct* pSPI_Struct);
uint8_t SPI_Tx(SPI_Struct* pSPI_Struct, uint16_t data);
uint8_t SPI_Tx(SPI_Struct* pSPI_Struct, uint16_t* data, uint8_t count);
uint16_t SPI_Rx(SPI_Struct* pSPI_Struct);
uint16_t* SPI_Rx(SPI_Struct* pSPI_Struct, uint16_t* dest, uint8_t count);

#endif
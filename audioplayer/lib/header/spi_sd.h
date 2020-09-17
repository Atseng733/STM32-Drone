#ifndef SPI_SD_H
#define SPI_SD_H

#include <boards.h>
#include <spi.h>

class spi_sd {
private:
	SPI_Struct* pSPI_Struct;
public:
	void Init(SPI_Struct* pSPI_Struct);
	void SPI_SD_Read(SPI_Struct* pSPI_Struct);
	void SPI_SD_SetBlockLength(uint32_t length);
	void Send_CMD0(SPI_Struct* pSPI_Struct);
	void Send_CMD8(SPI_Struct* pSPI_Struct);
	void Send_CMD16(SPI_Struct* pSPI_Struct, uint32_t arg);
	void Send_CMD41(SPI_Struct* pSPI_Struct);
	void Send_CMD55(SPI_Struct* pSPI_Struct);
	void Send_CMD58(SPI_Struct* pSPI_Struct);
	uint16_t GetResponse8(SPI_Struct* pSPI_Struct);
	void GetResponse40(SPI_Struct* pSPI_Struct, uint16_t* dest);
	void clockCycle(SPI_Struct* pSPI_Struct, uint8_t n);
};

#endif
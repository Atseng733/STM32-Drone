#include <spi_sd.h>

void spi_sd::Init(SPI_Struct* spi_struct) {
	pSPI_Struct = spi_struct;

	Serial1.println("\nInitializing...");
	uint16_t response[5];
	uint8_t i = 0;

	/*place sd card in SPI mode by setting mosi and cs high and toggling clk for 74 cycles*/
	writeHigh(pSPI_Struct->NSS_PORT, pSPI_Struct->NSS_PIN);
	for(int i = 0; i < 10; i++) {
		SPI_Tx(pSPI_Struct, 0xFF);
	}

	/*then set cs low and send CMD0 0x4000'0000'0095*/
	writeLow(pSPI_Struct->NSS_PORT, pSPI_Struct->NSS_PIN);
	Send_CMD0(pSPI_Struct);

	/*get cmd0 response which should be 0x01*/
	Serial1.println("\nSending Command 0...");
	if(GetResponse8(pSPI_Struct) != 0x01) {
		Serial1.println("Command 0 error");
	}

	/*send cmd8*/
	Serial1.println("\nSending Command 8...");
	Send_CMD8(pSPI_Struct);

	/*get cmd8 response*/
	GetResponse40(pSPI_Struct, response);
	if(response[4] != 0xAA) {
		Serial1.println("Command 8 error");
	}

	/*send cmd58*/
	Serial1.println("\nSending Command 58...");
	Send_CMD58(pSPI_Struct);
	GetResponse40(pSPI_Struct, response);

	/*send cmd55 and acmd 41 until out of idle state*/
	Serial1.println("\nSending ACMD41...");
	uint16_t attempts = 0;
	while(attempts < 100) {
		Send_CMD55(pSPI_Struct);
		GetResponse8(pSPI_Struct);

		Send_CMD41(pSPI_Struct);
		if(GetResponse8(pSPI_Struct) == 0x01) {
			attempts++;
			delay_ms(10);
		}
		else {
			Serial1.println("SD Initialized");
			break;
		}
	}

	/*send cmd58*/
	Serial1.println("\nSending Command 58...");
	Send_CMD58(pSPI_Struct);
	GetResponse40(pSPI_Struct, response);
}

void spi_sd::Send_CMD0(SPI_Struct* pSPI_Struct) {
	uint16_t CMD0[6] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_Tx(pSPI_Struct, CMD0, 6);
}

void spi_sd::Send_CMD8(SPI_Struct* pSPI_Struct) {
	uint16_t CMD8[6] = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
	SPI_Tx(pSPI_Struct, CMD8, 6);
}

void spi_sd::Send_CMD16(SPI_Struct* pSPI_Struct, uint32_t arg) {
	uint16_t CMD16[6];
	CMD16[0] = 0x50;
	CMD16[1] = (arg & 0x000000FF);
	CMD16[2] = (arg >> 8) & 0x000000FF;
	CMD16[3] = (arg >> 16) & 0x000000FF;
	CMD16[4] = (arg >> 24) & 0x000000FF;
	CMD16[5] = 0xFF;
	SPI_Tx(pSPI_Struct, CMD16, 6);
}

void spi_sd::Send_CMD41(SPI_Struct* pSPI_Struct) {
	uint16_t CMD41[6] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x01};
	SPI_Tx(pSPI_Struct, CMD41, 6);
}

void spi_sd::Send_CMD55(SPI_Struct* pSPI_Struct) {
	uint16_t CMD55[6] = {0x77, 0x00, 0x00, 0x00, 0x00, 0x01};
	SPI_Tx(pSPI_Struct, CMD55, 6);
}

void spi_sd::Send_CMD58(SPI_Struct* pSPI_Struct) {
	uint16_t CMD58[6] = {0x7A, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_Tx(pSPI_Struct, CMD58, 6);
}

uint16_t spi_sd::GetResponse8(SPI_Struct* pSPI_Struct) {
	int i = 0;
	uint16_t response;

	while(i < 8) {
		response = SPI_Rx(pSPI_Struct);
		if(response == 0xFF) {
			i++;
		}
		else {
			break;
		}
	}

	return response;
}

void spi_sd::GetResponse40(SPI_Struct* pSPI_Struct, uint16_t* dest) {
	SPI_Rx(pSPI_Struct, dest, 5);
}

void spi_sd::SPI_SD_Read(SPI_Struct* pSPI_Struct) {

}

void spi_sd::clockCycle(SPI_Struct* pSPI_Struct, uint8_t n) {
	SPI_Tx(pSPI_Struct, 0xFF);
	SPI_Rx(pSPI_Struct);
}
#include <spi_sd.h>

void spi_sd::Init(SPI_Struct* spi_struct) {
	pSPI_Struct = spi_struct;

	Serial1.println("\nInitializing...");
	uint16_t response[5];

	/*place sd card in SPI mode by setting mosi and cs high and toggling clk for 74 cycles*/
	writeHigh(pSPI_Struct->NSS_PORT, pSPI_Struct->NSS_PIN);
	for(int i = 0; i < 10; i++) {
		SPI_Tx(pSPI_Struct, 0xFF);
	}

	/*then set cs low and send CMD0 0x4000'0000'0095*/
	writeLow(pSPI_Struct->NSS_PORT, pSPI_Struct->NSS_PIN);
	Serial1.println("\nSending Command 0...");
	Send_CMD0();

	/*get cmd0 response which should be 0x01*/
	response[0] = GetResponse8();
	Serial1.println(response[0], 16);

	/*send cmd8*/
	Serial1.println("\nSending Command 8...");
	Send_CMD8();

	/*get cmd8 response*/
	GetResponse40(response);
	if(response[4] != 0xAA) {
		Serial1.println("Command 8 error");
	}

	for(uint16_t i: response) {
		Serial1.println(i, 16);
	}

	/*send cmd58*/
	Serial1.println("\nSending Command 58...");
	Send_CMD58();
	GetResponse40(response);
	for(uint16_t i: response) {
		Serial1.println(i, 16);
	}

	/*send cmd55 and acmd 41 until out of idle state*/
	Serial1.println("\nSending ACMD41...");
	uint16_t attempts = 0;
	while(attempts < 100) {
		Send_CMD55();
		GetResponse8();

		Send_CMD41();
		if(GetResponse8() == 0x01) {
			attempts++;
			delay_ms(10);
		}
		else {
			Serial1.println("SD initialized in ");
			break;
		}
	}

	/*send cmd58*/
	Serial1.println("\nSending Command 58...");
	Send_CMD58();
	GetResponse40(response);
	for(uint16_t i: response) {
		Serial1.println(i, 16);
	}
	if(response[1] & (1 << 7)) {
		Serial1.println("SDHC");
	}
}

void spi_sd::ReadBlock(uint32_t sector, uint8_t* dest) {
	uint16_t response;
	bool receiveData = false;
	Send_CMD17(sector);
	response = GetResponse8();

	while(1) {
		response = SPI_Rx(pSPI_Struct);
		//Serial1.println(response, 16);
		if(response == 0xFE) {
			receiveData = true;
			break;
		}
	}

	if(receiveData) {
		for(int i = 0; i < 512; i++) {
			dest[i] = SPI_Rx(pSPI_Struct);
		}

		SPI_Rx(pSPI_Struct);
		SPI_Rx(pSPI_Struct);
	}

}

void spi_sd::Send_CMD0() {
	uint16_t CMD0[6] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_Tx(pSPI_Struct, CMD0, 6);
}

void spi_sd::Send_CMD8() {
	uint16_t CMD8[6] = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
	SPI_Tx(pSPI_Struct, CMD8, 6);
}

void spi_sd::Send_CMD16(uint32_t arg) {
	uint16_t CMD16[6];
	CMD16[0] = 0x50;
	CMD16[1] = (arg >> 24) & 0x000000FF;
	CMD16[2] = (arg >> 16) & 0x000000FF;
	CMD16[3] = (arg >> 8) & 0x000000FF;
	CMD16[4] = (arg & 0x000000FF);
	CMD16[5] = 0xFF;
	SPI_Tx(pSPI_Struct, CMD16, 6);
}

void spi_sd::Send_CMD17(uint32_t arg) {
	uint16_t CMD17[6];
	CMD17[0] = 0x51;
	CMD17[1] = (arg >> 24) & 0xFF;
	CMD17[2] = (arg >> 16) & 0xFF;
	CMD17[3] = (arg >> 8) & 0xFF;
	CMD17[4] = (arg & 0xFF);
	CMD17[5] = 0x01;
	SPI_Tx(pSPI_Struct, CMD17, 6);
}

void spi_sd::Send_CMD41() {
	uint16_t CMD41[6] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x01};
	SPI_Tx(pSPI_Struct, CMD41, 6);
}

void spi_sd::Send_CMD55() {
	uint16_t CMD55[6] = {0x77, 0x00, 0x00, 0x00, 0x00, 0x01};
	SPI_Tx(pSPI_Struct, CMD55, 6);
}

void spi_sd::Send_CMD58() {
	uint16_t CMD58[6] = {0x7A, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_Tx(pSPI_Struct, CMD58, 6);
}

uint16_t spi_sd::GetResponse8() {
	int i = 0;
	uint16_t response;

	while(i < 16) {
		response = SPI_Rx(pSPI_Struct);
		if((response >> 7) & 1) {
			i++;
		}
		else {
			break;
		}
	}

	return response;
}

void spi_sd::GetResponse40(uint16_t* dest) {
	dest[0] = GetResponse8();
	for(int i = 1; i < 5; i++) {
		dest[i] = SPI_Rx(pSPI_Struct);
	}
}


void spi_sd::clockCycle(uint8_t n) {
	for(int i = 0; i < n; i++) {
		SPI_Tx(pSPI_Struct, 0xFF);
	}
}

void spi_sd::GetPartitionData() {
	ReadBlock(0, buf);

	if(((buf[MBR_Sig + 1] << 8) | buf[MBR_Sig]) == 0xAA55) {
		for(int i = 0; i < 512; i++) {
			Serial1.println(buf[i], 16);
		}
	}

	PT1_StartSector = buf[446];
}
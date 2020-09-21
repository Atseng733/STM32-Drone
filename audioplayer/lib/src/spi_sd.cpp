#include <spi_sd.h>

void spi_sd::Init(SPI_SD_Struct* pspi_sd_struct) {
	pSPI_SD_Struct = pspi_sd_struct;
	pSPI_SD_Struct->dirDepth = 0;

	Serial1.println("\nInitializing...");
	uint16_t response[5];

	/*place sd card in SPI mode by setting mosi and cs high and toggling clk for 74 cycles*/
	writeHigh(pSPI_SD_Struct->pSPI_Struct->NSS_PORT, pSPI_SD_Struct->pSPI_Struct->NSS_PIN);
	for(int i = 0; i < 10; i++) {
		SPI_Tx(pSPI_SD_Struct->pSPI_Struct, 0xFF);
	}

	/*then set cs low and send CMD0 0x4000'0000'0095*/
	writeLow(pSPI_SD_Struct->pSPI_Struct->NSS_PORT, pSPI_SD_Struct->pSPI_Struct->NSS_PIN);
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
		response = SPI_Rx(pSPI_SD_Struct->pSPI_Struct);
		//Serial1.println(response, 16);
		if(response == 0xFE) {
			receiveData = true;
			break;
		}
	}

	if(receiveData) {
		for(int i = 0; i < 512; i++) {
			dest[i] = SPI_Rx(pSPI_SD_Struct->pSPI_Struct);
		}

		SPI_Rx(pSPI_SD_Struct->pSPI_Struct);
		SPI_Rx(pSPI_SD_Struct->pSPI_Struct);
	}

}

void spi_sd::Send_CMD0() {
	uint16_t CMD0[6] = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD0, 6);
}

void spi_sd::Send_CMD8() {
	uint16_t CMD8[6] = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD8, 6);
}

void spi_sd::Send_CMD16(uint32_t arg) {
	uint16_t CMD16[6];
	CMD16[0] = 0x50;
	CMD16[1] = (arg >> 24) & 0x000000FF;
	CMD16[2] = (arg >> 16) & 0x000000FF;
	CMD16[3] = (arg >> 8) & 0x000000FF;
	CMD16[4] = (arg & 0x000000FF);
	CMD16[5] = 0xFF;
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD16, 6);
}

void spi_sd::Send_CMD17(uint32_t arg) {
	uint16_t CMD17[6];
	CMD17[0] = 0x51;
	CMD17[1] = (arg >> 24) & 0xFF;
	CMD17[2] = (arg >> 16) & 0xFF;
	CMD17[3] = (arg >> 8) & 0xFF;
	CMD17[4] = (arg & 0xFF);
	CMD17[5] = 0x01;
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD17, 6);
}

void spi_sd::Send_CMD41() {
	uint16_t CMD41[6] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x01};
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD41, 6);
}

void spi_sd::Send_CMD55() {
	uint16_t CMD55[6] = {0x77, 0x00, 0x00, 0x00, 0x00, 0x01};
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD55, 6);
}

void spi_sd::Send_CMD58() {
	uint16_t CMD58[6] = {0x7A, 0x00, 0x00, 0x00, 0x00, 0x95};
	SPI_Tx(pSPI_SD_Struct->pSPI_Struct, CMD58, 6);
}

uint16_t spi_sd::GetResponse8() {
	int i = 0;
	uint16_t response;

	while(i < 16) {
		response = SPI_Rx(pSPI_SD_Struct->pSPI_Struct);
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
		dest[i] = SPI_Rx(pSPI_SD_Struct->pSPI_Struct);
	}
}


void spi_sd::clockCycle(uint8_t n) {
	for(int i = 0; i < n; i++) {
		SPI_Tx(pSPI_SD_Struct->pSPI_Struct, 0xFF);
	}
}

uint8_t spi_sd::GetPartitionData() {
	ReadBlock(0, pSPI_SD_Struct->dataBuf);
	pSPI_SD_Struct->PT1_StartSector = 0;

	if(CheckBootSign()) {
		for(uint8_t i = 0; i < 4; i++) {
			GetValue(&(pSPI_SD_Struct->PT1_StartSector), MBR_Partition1 + PT_LbaOfs, 4);
		}

		Serial1.println(pSPI_SD_Struct->PT1_StartSector, 10);
	}
	else {
		Serial1.println("MBR error");
		return 0;
	}

	ReadBlock(pSPI_SD_Struct->PT1_StartSector, pSPI_SD_Struct->dataBuf);
	dumpBuf();
	if(CheckBootSign()) {
		uint32_t FATSz32;
		GetValue(&FATSz32, BPB_FATSz32, 4);
		uint8_t NumFATs;
		GetValue(&NumFATs, BPB_NumFATs, 1);
		uint16_t RsvdSecCnt;
		GetValue(&RsvdSecCnt, BPB_RsvdSecCnt, 2);
		uint32_t HiddSec;
		GetValue(&HiddSec, BPB_HiddSec, 4);
		pSPI_SD_Struct->DataStartSector = (FATSz32 * NumFATs) + RsvdSecCnt + HiddSec;

		//GetValue(&(pSPI_SD_Struct->SecPerClus), 12, 1);
		pSPI_SD_Struct->SecPerClus = pSPI_SD_Struct->dataBuf[13];
	}
	else {
		Serial1.println("Boot Sector error");
		return 0;
	}

	return 1;
}

uint8_t spi_sd::CheckBootSign() {
	return (((pSPI_SD_Struct->dataBuf[MBR_Sig + 1] << 8) | pSPI_SD_Struct->dataBuf[MBR_Sig]) == 0xAA55);
}

template <typename T> T spi_sd::GetValue(T* type, uint16_t offset, uint8_t n) {
	for(uint8_t i = 0; i < n; i++) {
		*type |= pSPI_SD_Struct->dataBuf[offset + i] << (i * 8);
	}

	return *type;
}

void spi_sd::ScanDir(uint32_t sector) {
	int i = 0;
	ReadBlock(sector, pSPI_SD_Struct->dataBuf);

	while(pSPI_SD_Struct->dataBuf[i % 512] != 0x00) {
		if(pSPI_SD_Struct->dataBuf[i % 512] != 0xE5 && pSPI_SD_Struct->dataBuf[i % 512] != 0x2E) {
			if(pSPI_SD_Struct->dataBuf[(i % 512) + DIR_Attr] == 0x0F && (pSPI_SD_Struct->dataBuf[i % 512] & (1 << 6))) {
				uint8_t LFN_Entries = pSPI_SD_Struct->dataBuf[i % 512] - 0x40;
				uint32_t LFN_End = (LFN_Entries - 1) * 32 + i;

				for(int j = 0; j < pSPI_SD_Struct->dirDepth; j++) {
					Serial1.print("\t");
				}
				Serial1.print("-");

				for(int k = LFN_End; k > (LFN_End - (32*LFN_Entries)); k -= 32) {
					ReadBlock(sector + (k / 512), pSPI_SD_Struct->dataBuf);

					for(int j = 0; j < 5; j++) {
						if(pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name1 + (j * 2)] != 0x00 && pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name1 + (j * 2)] != 0xFF) {
							Serial1.printc(pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name1 + (j * 2)]);
						}
					}
					for(int j = 0; j < 6; j++) {
						if(pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name2 + (j * 2)] != 0x00 && pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name2 + (j * 2)] != 0xFF) {
							Serial1.printc(pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name2 + (j * 2)]);
						}
					}
					for(int j = 0; j < 2; j++) {
						if(pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name3 + (j * 2)] != 0x00 && pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name3 + (j * 2)] != 0xFF) {
							Serial1.printc(pSPI_SD_Struct->dataBuf[(k % 512) + LDIR_Name3 + (j * 2)]);
						}
					}
				}
				Serial1.println("");

				ReadBlock(sector + ((LFN_End + 32) / 512), pSPI_SD_Struct->dataBuf);
				if(pSPI_SD_Struct->dataBuf[((LFN_End + 32) % 512) + DIR_Attr] == 0x10) {
					uint32_t startSector;
					GetValue(&startSector, ((LFN_End + 32) % 512) + DIR_FstClusHI, 2);
					startSector = startSector << 16;
					GetValue(&startSector, ((LFN_End + 32) % 512) + DIR_FstClusLO, 2);
					startSector -= 2;
					startSector *= pSPI_SD_Struct->SecPerClus;
					startSector += pSPI_SD_Struct->DataStartSector;
					Serial1.println(startSector, 10);
					pSPI_SD_Struct->dirDepth++;
					ScanDir(startSector);
					pSPI_SD_Struct->dirDepth--;
				}
			}
			/*if(pSPI_SD_Struct->dataBuf[(i % 512) + DIR_Attr] == 0x10) {
				for(int j = 0; j < pSPI_SD_Struct->dirDepth; j++) {
					Serial1.print("\t");
				}
				Serial1.print("-");
				
				for(int k = 0; k < 8; k++) {
					Serial1.printc(pSPI_SD_Struct->dataBuf[(i % 512) + k]);
				}
				Serial1.println("");

				uint32_t startSector;
				GetValue(&startSector, (i % 512) + DIR_FstClusHI, 2);
				startSector = startSector << 16;
				GetValue(&startSector, (i % 512) + DIR_FstClusLO, 2);

				startSector -= 2;
				startSector *= pSPI_SD_Struct->SecPerClus;
				startSector += pSPI_SD_Struct->DataStartSector;

				pSPI_SD_Struct->dirDepth++;
				ScanDir(startSector);
				pSPI_SD_Struct->dirDepth--;

				ReadBlock(sector + (i / 512), pSPI_SD_Struct->dataBuf);
			}
			else if(pSPI_SD_Struct->dataBuf[(i % 512) + DIR_Attr] == 0x20) {
				for(int j = 0; j < pSPI_SD_Struct->dirDepth; j++) {
					Serial1.print("\t");
				}
				Serial1.print("-");
				
				int k = 0;
				while(pSPI_SD_Struct->dataBuf)
				if(pSPI_SD_Struct->dataBuf[(i % 512) - 32] )
				Serial1.println("");
			}*/
		}

		i += 32;
		ReadBlock(sector + (i / 512), pSPI_SD_Struct->dataBuf);
	}
}

void spi_sd::dumpBuf() {
	for(uint8_t i: pSPI_SD_Struct->dataBuf) {
		Serial1.println(i, 16);
	}
}
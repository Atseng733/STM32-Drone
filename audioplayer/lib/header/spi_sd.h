#ifndef SPI_SD_H
#define SPI_SD_H

#include <boards.h>
#include <spi.h>

//MBR and partition table
#define MBR_bootcode 0
#define MBR_Partition1 446
#define MBR_Partition2 462
#define MBR_Partition3 478
#define MBR_Partition4 494
#define MBR_Sig 510

#define PT_BootID 0
#define PT_StartHd 1
#define PT_StartCySc 2
#define PT_System 4
#define PT_EndHd 5
#define PT_EndCySc 6
#define PT_LbaOfs 8
#define PT_LbaSize 12

class spi_sd {
private:
	SPI_Struct* pSPI_Struct;
	uint8_t buf[512];
	uint32_t PT1_StartSector;
public:
	void Init(SPI_Struct* pSPI_Struct);
	void ReadBlock(uint32_t sector, uint8_t* dest);
	void WriteBlock(uint32_t sector);
	void Send_CMD0();
	void Send_CMD8();
	void Send_CMD16(uint32_t arg);
	void Send_CMD17(uint32_t arg);
	void Send_CMD24(uint32_t arg);
	void Send_CMD41();
	void Send_CMD55();
	void Send_CMD58();
	uint16_t GetResponse8();
	void GetResponse40(uint16_t* dest);
	void clockCycle(uint8_t n);
	void GetPartitionData();
};

#endif
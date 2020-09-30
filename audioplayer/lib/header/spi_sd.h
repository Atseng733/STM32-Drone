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

//BPB and Boot sector
#define BS_JmpBoot 0
#define BS_OEMName 3
#define BPB_BytsPerSec 11
#define BPB_SecPerClus 13
#define BPB_RsvdSecCnt 14
#define BPB_NumFATs 16
#define BPB_RootEntCnt 17
#define BPB_TotSec16 19
#define BPB_Media 21
#define BPB_FATSz16 22
#define BPB_SecPerTrk 24
#define BPB_NumHeads 26
#define BPB_HiddSec 28
#define BPB_TotSec32 32
#define BPB_FATSz32 36
#define BPB_ExtFlags 40
#define BPB_FSVer 42
#define BPB_RootClus 44
#define BPB_FSInfo 48
#define BPB_BkBootSec 50
#define BPB_Reserved 52
#define BPB_DrvNum 64
#define BPB_Reserved1 65
#define BPB_BootSig 66
#define BPB_VolID 67
#define BS_VolLab 71
#define BS_FilSysType 82
#define BS_BootCode32 90
#define BS_BootSign 510

//Directory entries
#define DIR_Name 0
#define DIR_Attr 11
#define DIR_NTRes 12
#define DIR_CrtTimeTenth 13
#define DIR_CrtTime 14
#define DIR_CrtData 16
#define DIR_LstAccDate 18
#define DIR_FstClusHI 20
#define DIR_WrtTime 22
#define DIR_WrtData 24
#define DIR_FstClusLO 26
#define DIR_FileSize 28

#define LDIR_Ord 0
#define LDIR_Name1 1
#define LDIR_Attr 11
#define LDIR_Type 12
#define LDIR_Chksum 13
#define LDIR_Name2 14
#define LDIR_FstClusLO 26
#define LDIR_Name3 28

typedef struct {
	SPI_Struct* pSPI_Struct;
	uint8_t dataBuf[512];
	uint32_t PT1_StartSector;
	uint8_t SecPerClus;
	uint32_t DataStartSector;
	uint8_t dirDepth;
} SPI_SD_Struct;

class spi_sd {
private:
	SPI_SD_Struct* pSPI_SD_Struct;
public:
	void Init(SPI_SD_Struct* pspi_sd_struct);
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
	uint8_t GetPartitionData();
	uint8_t CheckBootSign();
	template <typename T> T GetValue(T* type, uint16_t offset, uint8_t n);
	void ScanDir(uint32_t sector);
	void dumpBuf();
	uint32_t SearchFile(char search_str[], uint32_t sector);
};

#endif
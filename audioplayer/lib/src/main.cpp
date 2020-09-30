#include <main.h>
spi_sd SD1;
SPI_Struct SPI2_Struct;
USART_Struct USART1_Struct;
SPI_SD_Struct SPI_SD1_Struct;
Adv_Timer_Struct TIM4_Struct;
DAC_Struct DAC_Init_Struct;

int main(void) {
	rcc_sys_clk_setup();
	GPIOA_CLK_EN;
	GPIOB_CLK_EN;
	GPIOC_CLK_EN;
	GPIOD_CLK_EN;

	pinMode(GPIOA, 6, OUTPUT, PULLDOWN); //onboard LEDs
	pinMode(GPIOA, 7, OUTPUT, PULLDOWN);

	timer_init();

	pinMode(GPIOA, 9, ALTFN);
	pinAFNConfig(GPIOA, 9, USART_AFN, PUSH_PULL, LOW_SPEED, PULLUP);

	USART1_Struct.USARTx = USART1;
	Serial1.Init(&USART1_Struct, 230400, USART_MODE_TX);

	//configure spi2 pins
	pinMode(GPIOB, 13, ALTFN); //sck
	pinAFNConfig(GPIOB, 13, SPI_AFN, PUSH_PULL, MED_SPEED, FLOATING);
	pinMode(GPIOB, 9, OUTPUT); //nss
	pinMode(GPIOB, 15, ALTFN); //mosi
	pinAFNConfig(GPIOB, 15, SPI_AFN, PUSH_PULL, MED_SPEED, FLOATING);
	pinMode(GPIOB, 14, ALTFN); //miso
	pinAFNConfig(GPIOB, 14, SPI_AFN, PUSH_PULL, MED_SPEED, FLOATING);

	SPI2_Struct.SPIx = SPI2;
	SPI2_Struct.NSS_PORT = GPIOB;
	SPI2_Struct.NSS_PIN = 9;
	SPI2_Struct.CR1 = (0x6 << SPI_CR1_BR) | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE; //set baud rate, master mode, and slave management mode
	SPI2_Struct.CR2 = 0;

	delay_ms(100);
	

	SPI_Init(&SPI2_Struct);

	SPI2_Struct.CR1 &= ~(0x7 << SPI_CR1_BR);
	SPI2_Struct.CR1 |= (0x0 << SPI_CR1_BR);

	SPI_SD1_Struct.pSPI_Struct = &SPI2_Struct;
	SD1.Init(&SPI_SD1_Struct);
	SetClockPSC(&SPI2_Struct, 0b1);
	//for(int i = 0; i < 6000; i++) {
	//	Serial1.print("Sector "); Serial1.println(i, 10);
	//	SD1.ReadBlock(i);
	//}

	//SD1.ReadBlock(148154);
	//SD1.ReadBlock(2047);
	SD1.GetPartitionData();
	//SD1.ScanDir(SPI_SD1_Struct.DataStartSector);
	enableInterrupt(30);

	TIM4_Struct.TIMx = TIM4;
	TIM4_Struct.CR2 = (MMS_UPDATE << GEN_TIM_CR2_MMS);
	TIM4_Struct.DIER = (GEN_TIM_DIER_UIE);
	Serial1.println(APB1_CLK, 10);
	TIM4_Struct.PSC = APB1_CLK / 20000 - 1; //one timer count is 100us
	TIM4_Struct.ARR = 42000; //overflow ever second
	adv_timer DAC_TIMER;
	DAC_TIMER.Init(&TIM4_Struct);

	DAC_Init_Struct.CR = (DAC_TSEL_TIM4 << DAC_CR_TSEL1) | DAC_CR_TEN1 | DAC_CR_EN1;
	Serial1.println(DAC_Init_Struct.CR, 16);
	DAC_Init(&DAC_Init_Struct);

	Serial1.println(SPI_SD1_Struct.DataStartSector, 10);
	Serial1.println("Searching File");
	uint32_t fileSector = SD1.SearchFile("Paramore", SPI_SD1_Struct.DataStartSector);
	Serial1.println(fileSector, 10);
	SD1.ReadBlock(fileSector, SPI_SD1_Struct.dataBuf);
	GetWavContent(SPI_SD1_Struct.dataBuf);

	while(1) {
		toggle(GPIOA, 6);

		delay_ms(1000);
	}
	return 0;
}

void TIM4_Handler() {
	TIM4_Struct.TIMx->SR &= ~(GEN_TIM_SR_UIF);
	/*if(DAC->DOR1 = 0x00) {
		DAC->DHR8R1 = 0xFF;
	}
	else {
		DAC->DHR8R1 = 0x00;
	}*/
	Serial1.println("test");
}


void Reset_Handler() {
	main();
}

void HardFault_Handler() {
	Serial1.println("HardFault");
}

void MemManage_Handler() {
	Serial1.println("MemFault");
}

void BusFault_Handler() {
	Serial1.println("BusFault");
}
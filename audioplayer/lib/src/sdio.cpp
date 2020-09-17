#include <sdio.h>
uint32_t temp_cmd;
uint32_t response;

void SDIO_CMD(uint32_t cmd, uint32_t arg) {
	SDIO->CMD &= 0;
	for(int i = 0; i < 10; i++) {
		asm("nop");
	}
	SDIO->ARG = arg;
	SDIO->CMD |= cmd;
	for(int i = 0; i < 10; i++) {
		asm("nop");
	}
	if(cmd & (1 << SDIO_CMD_WAITRESP)) { //if waiting for response
		while(!(SDIO->STA & SDIO_STA_CMDREND));
		SDIO->ICR |= SDIO_ICR_CMDRENDC;
	}
	else if(!(cmd & (1 << SDIO_CMD_WAITRESP))) { //if no response required
		while(!(SDIO->STA & SDIO_STA_CMDSENT));
		SDIO->ICR |= SDIO_ICR_CMDSENTC;
	}
	for(int i = 0; i < 10; i++) {
		asm("nop");
	}

	if(SDIO->STA != 0) {
		Serial1.println("Error");
	}

	Serial1.println(SDIO->RESP1, 16);
	Serial1.println(SDIO->RESP2, 16);
	Serial1.println(SDIO->RESP3, 16);
	Serial1.println(SDIO->RESP4, 16);
}

void SDIO_Init() {
	SDIO_CLK_EN;
	//SDIO->CLKCR |= (0x1 << 11); //4 bit data bus, default is 1
	SDIO->CLKCR |= (((F_CPU * 2 / PLLQ) / 400000) + 1); //SDIO_CK < 400kHz when in identification mode
	//SDIO->CLKCR |= (1 << 9); //enable power saving mode
	SDIO->POWER |= 0x3; //power on - card clock is enabled
	//enable sdio clock
	SDIO->CLKCR |= SDIO_CLKCR_CLKEN;

	delay_ms(10);

	temp_cmd = 8 | SDIO_CMD_CPSMEN;
	SDIO_CMD(temp_cmd, 0);

	//send APP_CMD (CMD55)
	//set command index and enable CPSM
	temp_cmd = 55 | (0x01 << SDIO_CMD_WAITRESP) | SDIO_CMD_CPSMEN;
	SDIO_CMD(temp_cmd, 0);

	//set cmd index to 41
	temp_cmd = 41 | (0x1 << SDIO_CMD_WAITRESP) | SDIO_CMD_CPSMEN; 
	SDIO_CMD(temp_cmd, 0);

	//send CMD2 ALL_SEND_CID
	temp_cmd = 2 | (0x3 << SDIO_CMD_WAITRESP) | SDIO_CMD_CPSMEN;
	SDIO_CMD(temp_cmd, 0);

	//send CMD3 SEND_RELATIVE_ADDR
	temp_cmd |= 3 | (0x1 << SDIO_CMD_WAITRESP);
	SDIO_CMD(temp_cmd, 0);

	Serial1.println(SDIO->RESP1, 16);
	Serial1.println(SDIO->RESP2, 16);
	Serial1.println(SDIO->RESP3, 16);
	Serial1.println(SDIO->RESP4, 16);
}
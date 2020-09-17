#include <main.h>
spi_sd SD1;

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
	Serial1.Init(USART1, 230400, USART_MODE_TX);

	//configure spi2 pins
	pinMode(GPIOB, 13, ALTFN); //sck
	pinAFNConfig(GPIOB, 13, SPI_AFN, PUSH_PULL, MED_SPEED, FLOATING);
	pinMode(GPIOB, 9, OUTPUT); //nss
	pinMode(GPIOB, 15, ALTFN); //mosi
	pinAFNConfig(GPIOB, 15, SPI_AFN, PUSH_PULL, MED_SPEED, FLOATING);
	pinMode(GPIOB, 14, ALTFN); //miso
	pinAFNConfig(GPIOB, 14, SPI_AFN, PUSH_PULL, MED_SPEED, FLOATING);
	SPI_Struct SPI2_Struct;
	SPI2_Struct.SPIx = SPI2;
	SPI2_Struct.NSS_PORT = GPIOB;
	SPI2_Struct.NSS_PIN = 9;
	SPI2_Struct.CR1 = (0x6 << SPI_CR1_BR) | SPI_CR1_MSTR; //set baud rate, master mode, and slave management mode
	SPI2_Struct.CR2 = 0;

	SPI_Init(&SPI2_Struct);
	SD1.Init(&SPI2_Struct);

	while(1) {
		toggle(GPIOA, 6);

		delay_ms(1000);
	}
	return 0;
}


void Reset_Handler() {
	main();
}

void HardFault_Handler() {
	while(1) {
		for(int i = 0; i < 3; i++) {
			toggle(GPIOB, 12);
			delay_ms(250);
		}
		delay_ms(1000);
	}
}

void MemManage_Handler() {
	while(1) {
		for(int i = 0; i < 3; i++) {
			toggle(GPIOB, 12);
			delay_ms(250);
		}
		delay_ms(1000);
	}
}

void BusFault_Handler() {
	while(1) {
		for(int i = 0; i < 3; i++) {
			toggle(GPIOB, 12);
			delay_ms(250);
		}
		delay_ms(1000);
	}
}
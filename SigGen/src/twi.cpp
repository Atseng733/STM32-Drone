#include "twi.h"
#include <usart.h>
#include <stdlib.h>
#include <usart.h>
char str[16];
void TWI_Init() {
	//print("TWI init");
	TWSR = 0x00;
	TWBR = TWI_BAUD;
	TWCR = (1<<TWEN);
}

void TWI_Start() {
	TWI_Init();
	//print("start ");
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void TWI_Send(uint8_t data) {
	//print("send "); print(utoa((unsigned int)(data), str, 16));
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void TWI_Write(uint8_t sAddr, uint8_t addr, uint8_t data) {
	//print("write ");
	//print("start, ");
	TWI_Start();
	//print("send sAddr, ");
	TWI_Send(sAddr<<1);
	//print("send register, ");
	TWI_Send(addr);
	//print("send data "); print(utoa((unsigned int)(data), str, 16));
	TWI_Send(data);
	//print("stop\n");
	TWI_Stop();
}

char TWI_Read(uint8_t sAddr, uint8_t addr) {
	char register_value = 0;
		
	TWI_Start();
	TWI_Send(sAddr<<1);
	TWI_Send(addr);
	TWI_Start();
	TWI_Send(sAddr<<1 | 1);
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1<<TWINT)));
	register_value = TWDR;
	TWI_Stop();
	return register_value;
}

void TWI_Read(uint8_t sAddr, uint8_t begin_addr, uint8_t count, uint8_t* dest) {
	uint8_t i;
	
	TWI_Start();
	TWI_Send(sAddr<<1);
	TWI_Send(begin_addr);
	TWI_Start();
	TWI_Send(sAddr<<1 | 1);
	for(i = 0; i < count - 1; i++) {
		TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWEA);
		while (!(TWCR & (1<<TWINT)));
		dest[i] = TWDR;
	}
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	dest[i] = TWDR;
	TWI_Stop();
}

void TWI_Stop() {
	//print("stop\n");
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

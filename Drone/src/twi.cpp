#include <twi.h>
#include <usart.h>
#include <stdlib.h>
#include <usart.h>
char str[16];
uint8_t twst;

void TWI_Init() {
	//print("TWI init");
	TWSR = 0x00;
	TWBR = TWI_BAUD;
	TWCR = (1<<TWEN);
}

unsigned char TWI_Start() {
	TWI_Init();
	//print("start ");
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));

	twst = TWI_Status() & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) {
		print("TWI start error ");
		return 1;
	}
	return 0;
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

unsigned char TWI_ReadAck() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;
}

unsigned char TWI_ReadNak()
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;

}

char TWI_Read(uint8_t sAddr, uint8_t addr) {
	char register_value = 0;

	TWI_Start();
	TWI_Send(sAddr<<1);
	TWI_Send(addr);
	TWI_Start();
	TWI_Send(sAddr<<1 | 1);
	register_value = TWI_ReadNak();
	TWI_Stop();
	//print("read "); print(itoa(register_value, str, 16));
	//delay(10);
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
		//print(utoa(i, str, 10));
	}
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	dest[i] = TWDR;
	TWI_Stop();
}

void TWI_Stop() {
	//print("stop\n");
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while(TWCR & (1<<TWSTO));
}

uint8_t TWI_Status() {
	return TWSR;
}
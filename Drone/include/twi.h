#ifndef TWI_H
#define TWI_H
#include <m328io.h>
#include <stdint.h>
#include <util/twi.h>

#define F_SCL 100000UL //100kHz
#define TWI_BAUD ((F_CPU/F_SCL - 16)/2) //value TWBR will be set to

void TWI_Init();
unsigned char TWI_Start();
void TWI_Send(uint8_t data);
void TWI_Write(uint8_t sAddr, uint8_t addr, uint8_t data);
unsigned char TWI_ReadAck();
unsigned char TWI_ReadNak();
char TWI_Read(uint8_t sAddr, uint8_t addr);
void TWI_Read(uint8_t sAddr, uint8_t begin_addr, uint8_t count, uint8_t* dest);
void TWI_Stop();
uint8_t TWI_Status();

#endif
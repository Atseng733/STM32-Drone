#ifndef TWI_H
#define TWI_H
#include <m328io.h>
#include <stdint.h>

#define F_SCL 100000UL //100kHz
#define TWI_BAUD ((F_CPU/F_SCL - 16)/2) //value TWBR will be set to

void TWI_Init();
void TWI_Start();
void TWI_Send(uint8_t data);
void TWI_Write(uint8_t sAddr, uint8_t addr, uint8_t data);
char TWI_Read(uint8_t sAddr, uint8_t addr);
void TWI_Read(uint8_t sAddr, uint8_t begin_addr, uint8_t count, uint8_t* dest);
void TWI_Stop();

#endif
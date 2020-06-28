#ifndef TWI_H
#define TWI_H
#include <m328io.h>

#define F_SCL 100000UL //100kHz
#define TWI_BAUD ((F_CPU/F_SCL - 16)/2) //value TWBR will be set to

void TWI_Init();
void TWI_Start();
void TWI_Send(unsigned char data);
void TWI_Write(unsigned char sAddr, unsigned char addr, unsigned char data);
char TWI_Read(unsigned char sAddr, unsigned char addr);
void TWI_Read(unsigned char sAddr, unsigned char begin_addr, unsigned char count, uint8_t* dest);
void TWI_Stop();

#endif
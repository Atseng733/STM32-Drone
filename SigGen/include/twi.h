#ifndef TWI_H
#define TWI_H
#include <m328io.h>

#define F_SCL 100000UL //100kHz
#define TWI_BAUD ((F_CPU/F_SCL - 16)/2) //value TWBR will be set to

void twi_init();
//void twi_start();
//void twi_sla_w(uint8_t sAddr);
//void twi_sla_r(uint8_t sAddr);
//void twi_send_data(uint8_t data);
//void twi_stop();

#endif
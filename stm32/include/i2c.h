#ifndef I2C_H
#define I2C_H

#include <f407.h>
#include <interrupt.h>
#include <f407_fn.h>
#include <usart.h>

class i2c {
	public:
		i2c() {}
		void init();
		void start();
		uint8_t send(uint8_t data);
		uint8_t sla_w(uint8_t sla_addr);
		uint8_t sla_r(uint8_t sla_addr);
		void stop();
		uint8_t write(uint8_t sla_addr, uint8_t addr, uint8_t data);
};

#endif
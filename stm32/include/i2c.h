#ifndef I2C_H
#define I2C_H

#include <boards.h>
#include <interrupt.h>
#include <f1_gpio.h>
#include <usart.h>
#include <timer.h>

class i2c {
	public:
		i2c() {}
		void init();
		void start();
		uint8_t send(uint8_t data);
		uint8_t sla_w(uint8_t sla_addr);
		uint8_t sla_r(uint8_t sla_addr);
		void stop();
		void write(uint8_t sla_addr, uint8_t addr, uint8_t data);
		void iwrite(uint8_t sla_addr, uint8_t addr, uint8_t data);
		uint8_t read(uint8_t sla_addr, uint8_t addr);
		void read(uint8_t sla_addr, uint8_t begin_addr, uint8_t count, uint8_t* dest);
		uint8_t iread(uint8_t sla_addr, uint8_t addr, uint8_t count, uint8_t* dest);
};

extern i2c I2C;

#endif
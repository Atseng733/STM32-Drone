#ifndef I2C_H
#define I2C_H

#include <boards.h>
#include <interrupt.h>
#include <usart.h>
#include <timer.h>
#include <rcc.h>

#define I2C_CCR_VALUE ((uint32_t)((1/(double)I2C_FREQ)/(3/(double)APB1_CLK)))
#define I2C_TRISE_VALUE ((uint32_t)((.0000003)/(1/(double)APB1_CLK)))
#define I2C_READY 0
#define I2C_BUSY_TX 1
#define I2C_BUSY_RX 2

class i2c {
	private:
		void I2C_RXNE_Handler();
	public:
		i2c() {}
		void init();
		void write(uint8_t sla_addr, uint8_t addr, uint8_t data);
		void write(uint8_t sla_addr, uint8_t addr, uint8_t* data, uint16_t len);
		void iwrite(uint8_t sla_addr, uint8_t addr, uint8_t* data, uint32_t len);
		uint8_t read(uint8_t sla_addr, uint8_t addr);
		void read(uint8_t sla_addr, uint8_t begin_addr, uint8_t* dest, uint8_t count);
		void iread(uint8_t sla_addr, uint8_t addr, uint8_t* dest, uint8_t count);
		void I2C_CloseTx();
		void I2C_CloseRx();
		void I2C_EV_ISR();
};

extern i2c I2C;

#endif
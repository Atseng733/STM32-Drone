#ifndef I2C_H
#define I2C_H

#include <boards.h>
#include <interrupt.h>
#include <usart.h>
#include <timer.h>
#include <rcc.h>

#define I2C_CCR_VALUE(freq) ((uint32_t)((1/(double)freq)/(3/(double)APB1_CLK)))
#define I2C_TRISE_VALUE ((uint32_t)((.0000003)/(1/(double)APB1_CLK)))

#define I2C_READY 0
#define I2C_BUSY_TX 1
#define I2C_BUSY_RX 2

class i2c {
	private:
		I2C_Typedef* I2Cx;

		void I2C_ISR();
		void Start();
		void SendAddrW(uint8_t addr);
		void SendAddrR(uint8_t addr);
		void AckEnable();
		void AckDisable();
		void ClearAddrFlag();
		void Stop();
	public:
		i2c() {}
		void Init(I2C_Typedef* i2cx, uint32_t i2c_speed);
		uint8_t GetFlagStatus(uint32_t reg, uint32_t flag);
		void write(uint8_t slaAddr, uint8_t regAddr, uint8_t data);
		void write(uint8_t slaAddr, uint8_t regAddr, uint8_t* data, uint16_t len);
		uint8_t read(uint8_t slaAddr, uint8_t regAddr);
		void read(uint8_t slaAddr, uint8_t regAddr, uint8_t* dest, uint16_t len);
};

extern i2c I2C;

#endif
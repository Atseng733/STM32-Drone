#include <i2c.h>
usart i2c_serial;
void i2c::init() {
	RCC->APB1ENR |= (0x01 << 21);
	I2C1->CR1 = 0x0000;
	I2C1->CR2 = 0x0000;

	I2C1->CR2 = 0x0010; //set peripheral clock (in MHz)
	I2C1->CCR |= 0x0050;	  //adjust bus speed
	I2C1->TRISE |= 0x0011;	  //set max rise time
	I2C1->CR1 |= 0x0400;  //enable acknowledge

	GPIO_pinMode(GPIOB, 8, ALTFN);
	GPIO_pinAFNConfig(GPIOB, 8, I2C_AFN, OPEN_DRAIN, LOW_SPEED, PULLUP);
	GPIO_pinMode(GPIOB, 9, ALTFN);
	GPIO_pinAFNConfig(GPIOB, 9, I2C_AFN, OPEN_DRAIN, LOW_SPEED, PULLUP);

	I2C1->CR1 |= 0x0001; //enable i2c

	//i2c_serial.print("I2C initialized\t");
}

void i2c::start() {
	I2C1->CR1 |= 0x0100; //set start bit
}

uint8_t i2c::send(uint8_t data) {
		I2C1->DR = data;
}

uint8_t i2c::sla_w(uint8_t sla_addr) {
	if(I2C1->SR1 & 0x0001) {
		I2C1->DR = (sla_addr << 1);
	}

	if((I2C1->SR1 & 0x0002) && (I2C1->SR2 & 0x0001)) {
		return 0;
	}

	return 1;
}

uint8_t i2c::sla_r(uint8_t sla_addr) {
	if(I2C1->SR1 & 0x0001) {
		I2C1->DR = ((sla_addr << 1) + 1);
	}

	if((I2C1->SR1 & 0x0002) && (I2C1->SR2 & 0x0001)) {
		return 0;
	}

	return 1;
	
}

void i2c::stop() {
	I2C1->CR1 |= 0x0200;
}

uint8_t i2c::write(uint8_t sla_addr, uint8_t addr, uint8_t data) {
	i2c_serial.print("Beginning write operation\t");
	uint32_t temp;

	I2C1->CR1 |= 0x0100;
	while(!(I2C1->SR1 & 0x0001));

	//i2c_serial.print("Start\t");

	I2C1->DR = (sla_addr << 1);
	while(!(I2C1->SR1 & 0x0002));
	temp = I2C1->SR2;

	I2C1->DR = addr;
	for(int i = 0; i < 10; i++) {
		asm("nop");
	}

	//while(!(I2C1->SR1 & 0x0010));

	I2C1->DR = data;
	//while(!(I2C1->SR1 & 0x0010));
	for(int i = 0; i < 10; i++) {
			asm("nop");
	}

	I2C1->CR1 |= 0x0200;
}
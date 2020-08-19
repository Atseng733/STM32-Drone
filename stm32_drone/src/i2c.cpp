#include <i2c.h>

i2c I2C;

void i2c::Start() {
	I2Cx->CR1 |= I2C_CR1_START;
}

void i2c::SendAddrW(uint8_t addr) {
	I2Cx->DR = (addr << 1);
}

void i2c::SendAddrR(uint8_t addr) {
	I2Cx->DR = ((addr << 1) + 1);
}

void i2c::AckEnable() {
	I2Cx->CR1 |= I2C_CR1_ACK;
}

void i2c::AckDisable() {
	I2Cx->CR1 &= ~I2C_CR1_ACK;
}

void i2c::ClearAddrFlag() {
	uint32_t temp;
	temp = I2Cx->SR2;
}

void i2c::Stop() {
	I2Cx->CR1 |= I2C_CR1_STOP;
}

void i2c::Init(I2C_Typedef* i2cx, uint32_t i2c_speed) {
	I2Cx = i2cx;

	if(I2Cx == I2C1) { //assuming pin remaps are all default
		I2C1_CLK_EN;
		pinMode(GPIOB, 6, OUTPUT);
		pinConfig(GPIOB, 6, AFO_OD);
		pinMode(GPIOB, 7, OUTPUT);
		pinConfig(GPIOB, 7, AFO_OD);
	}
	else if(I2Cx == I2C2) {
		I2C2_CLK_EN;
		pinMode(GPIOB, 10, OUTPUT); //not sure about these, pins weren't in the datasheet
		pinConfig(GPIOB, 10, AFO_OD);
		pinMode(GPIOB, 11, OUTPUT);
		pinConfig(GPIOB, 11, AFO_OD);
	}

	I2Cx->CR2 = (APB1_CLK/1000000); 	  //set peripheral clock (in MHz)
	I2Cx->CCR |= I2C_CCR_F_S;		//fast mode
	I2Cx->CCR |= I2C_CCR_VALUE(i2c_speed);	  //set bus speed
	I2Cx->TRISE |= I2C_TRISE_VALUE; //set max rise time
	I2Cx->CR1 |= I2C_CR1_ACK;   //enable acknowledge
	I2Cx->CR1 |= 0x0001; //enable i2c
}

uint8_t i2c::GetFlagStatus(uint32_t reg, uint32_t flag) {
	return (reg & flag);
}

void i2c::Write(uint8_t slaAddr, uint8_t regAddr, uint8_t data) {
	uint32_t temp;

	Start();
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_SB));

	SendAddrW(slaAddr);
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_ADDR));
	ClearAddrFlag();

	I2Cx->DR = regAddr;
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_TXE));

	I2Cx->DR = data;
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_BTF));

	Stop();
}

void i2c::Write(uint8_t slaAddr, uint8_t regAddr, uint8_t *data, uint16_t len) {
	uint32_t temp;

	Start();
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_SB));

	SendAddrW(slaAddr);
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_ADDR));
	ClearAddrFlag();

	I2Cx->DR = regAddr;

	while(len > 0) {
		while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_TXE));
		I2Cx->DR = *(data++);
		len--;
	}

	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_BTF));

	Stop();
}
uint8_t i2c::Read(uint8_t slaAddr, uint8_t regAddr) {
	uint8_t data;
	uint32_t temp;

	AckEnable();   //enable acknowledge

	Start();   //start condition
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_SB));

	SendAddrW(slaAddr);
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_ADDR));
	ClearAddrFlag();

	I2Cx->DR = regAddr;					//register address to read from
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_TXE));

	Start();   //repeat start
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_SB));

	SendAddrR(slaAddr); //ad + r
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_ADDR));
	AckDisable(); //disable acknowledge
	ClearAddrFlag();
	Stop(); //stop condition

	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_RXNE));
	data = I2Cx->DR; //read register
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_BTF));

	return data;
}
void i2c::Read(uint8_t slaAddr, uint8_t regAddr, uint8_t* dest, uint16_t len) {
	uint32_t temp;
	uint16_t RxLen = len;

	AckEnable();   //enable acknowledge

	Start();   //start condition
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_SB));

	SendAddrW(slaAddr);
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_ADDR));
	ClearAddrFlag();

	I2Cx->DR = regAddr;					//register address to read from
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_TXE));

	Start();   //repeat start
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_SB));

	SendAddrR(slaAddr); //ad + r
	while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_ADDR));
	ClearAddrFlag();

	if(len == 2) { //if reading 2 bytes
		AckDisable();
		while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_BTF));
		Stop();
		*(dest++) = I2Cx->DR;
		*(dest++) = I2Cx->DR;
	}
	else if(len > 2) { //if reading 3+ bytes
		while(RxLen > 3) { //read until 3 bytes are left
			while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_RXNE));
			*(dest++) = I2Cx->DR;
			RxLen--;
		}

		while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_BTF));
		AckDisable();
		*(dest++) = I2Cx->DR;
		Stop();
		*(dest++) = I2Cx->DR;
		while(!GetFlagStatus(I2Cx->SR1, I2C_SR1_RXNE));
	}
}

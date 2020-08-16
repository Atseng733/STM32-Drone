#include <i2c.h>

i2c I2C;
uint8_t* txBuffer;
uint8_t* rxBuffer;
volatile uint8_t TxRxState;
uint32_t txLen;
uint32_t rxLen;
uint32_t rxSize;
uint8_t devAddr;
uint8_t regAddr;
bool regAddrSent;

static void I2C_GenerateStart() {
	I2C1->CR1 |= I2C_CR1_START;
}

static void I2C_GenerateStop() {
	I2C1->CR1 |= I2C_CR1_STOP;
}

static void I2C_SendAddressW(uint8_t addr) {
	I2C1->DR = (addr << 1);
}

static void I2C_SendAddressR(uint8_t addr) {
	I2C1->DR = ((addr << 1) | 1);
}

static void I2C_AckEnable() {
	I2C1->CR1 |= I2C_CR1_ACK;
}

static void I2C_AckDisable() {
	I2C1->CR1 &= ~I2C_CR1_ACK;
}

static void I2C_ClearAddrFlag() {
	uint32_t temp;

	if(I2C1->SR1 & I2C_SR2_MSL) {
		if(TxRxState == I2C_BUSY_TX) {
			temp = I2C1->SR1;
			temp = I2C1->SR2;
			(void)temp;
		}
		else if(TxRxState == I2C_BUSY_RX) {
			if(rxSize == 1) {
				I2C_AckDisable();
				temp = I2C1->SR1;
				temp = I2C1->SR2;
				(void)temp;
			}
		}
	}
	else {
		temp = I2C1->SR1;
		temp = I2C1->SR2;
		(void)temp;
	}
}

static void I2C_SendRegAddr(uint8_t sla_addr, uint8_t rAddr) {
	uint32_t temp;

	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C_SendAddressW(sla_addr);
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C_ClearAddrFlag();

	I2C1->DR = rAddr;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C_GenerateStop();
}

void i2c::I2C_RXNE_Handler() {
	if(rxSize == 1) {
		*rxBuffer = I2C1->DR;
		rxLen--;
	}

	if(rxSize > 1) {
		if(rxLen == 2) {
			I2C_AckDisable();
		}

		*rxBuffer = I2C1->DR;
		rxBuffer++;
		rxLen--;
	}

	if(rxLen == 0) {
		I2C_GenerateStop();

		I2C_CloseRx();
	}	
}

void i2c::init() {
	I2C1_CLK_EN;

	I2C1->CR2 = (APB1_CLK/1000000); 	  //set peripheral clock (in MHz)
	I2C1->CCR |= I2C_CCR_F_S;		//fast mode
	I2C1->CCR |= I2C_CCR_VALUE;	  //adjust bus speed
	I2C1->TRISE |= I2C_TRISE_VALUE; //set max rise time
	I2C1->CR1 |= I2C_CR1_ACK;   //enable acknowledge

	pinMode(GPIOB, 6, OUTPUT);
	pinConfig(GPIOB, 6, AFO_OD);
	pinMode(GPIOB, 7, OUTPUT);
	pinConfig(GPIOB, 7, AFO_OD);

	I2C1->CR1 |= 0x0001; //enable i2c

	TxRxState = I2C_READY;

	USART.println("I2C initialized");
}

void i2c::write(uint8_t sla_addr, uint8_t addr, uint8_t data) {
	uint32_t temp;

	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C_SendAddressW(sla_addr);
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C_ClearAddrFlag();

	I2C1->DR = addr;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->DR = data;
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |= I2C_CR1_STOP;
	while(I2C1->SR1 & I2C_SR1_TXE || I2C1->SR1 & I2C_SR1_RXNE || I2C1->SR1 & I2C_SR1_BTF);
}

void i2c::write(uint8_t sla_addr, uint8_t addr, uint8_t* data, uint16_t len) {
	uint32_t temp;

	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C_SendAddressW(sla_addr);
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C_ClearAddrFlag();

	I2C1->DR = addr;

	while(len > 0) {
		while(!(I2C1->SR1 & I2C_SR1_TXE));
		I2C1->DR = *data;
		data++;
		len--;
	}

	while(!(I2C1->SR1 & I2C_SR1_TXE));
	while(!(I2C1->SR1 & I2C_SR1_BTF));

	I2C1->CR1 |= I2C_CR1_STOP;
}

void i2c::iwrite(uint8_t sla_addr, uint8_t addr, uint8_t* data, uint32_t len) {
	while(TxRxState  != 0);

	txBuffer = data;
	txLen = len;
	TxRxState = I2C_BUSY_TX;
	devAddr = sla_addr;
	regAddrSent = false;

	enableInterrupt(31);				//enable interrupts
	I2C1->CR2 |= I2C_CR2_ITBUFEN;
	I2C1->CR2 |= I2C_CR2_ITEVTEN;
	I2C1->CR2 |= I2C_CR2_ITERREN;

	I2C_GenerateStart();				//generate start to begin ISR

	while(TxRxState != 0);			//wait until ISR is complete
}

uint8_t i2c::read(uint8_t sla_addr, uint8_t addr) {
	uint8_t data;
	uint32_t temp;

	I2C1->CR1 |= I2C_CR1_ACK;   //enable acknowledge

	I2C1->CR1 |= I2C_CR1_START;   //start condition
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C_SendAddressW(sla_addr);
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C_ClearAddrFlag();

	I2C1->DR = addr;					//register address to read from
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |= I2C_CR1_START;   //repeat start
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C_SendAddressR(sla_addr); //ad + r
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C1->CR1 &= ~I2C_CR1_ACK; //disable acknowledge
	I2C_ClearAddrFlag();

	I2C1->CR1 |= I2C_CR1_STOP; //stop condition

	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	data = I2C1->DR; //read register

	return data;
}

void i2c::read(uint8_t sla_addr, uint8_t addr, uint8_t* dest, uint8_t count) {
	uint32_t temp;
	I2C1->CR1 |= I2C_CR1_ACK;   //enable acknowledge

	I2C1->CR1 |= I2C_CR1_START;   //start condition
	while(!(I2C1->SR1 & I2C_SR1_SB));

	I2C_SendAddressW(sla_addr);
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	I2C_ClearAddrFlag();

	I2C1->DR = addr;			//register address to read from
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	I2C1->CR1 |= I2C_CR1_START;   //repeat start
	while(!(I2C1->SR1 & I2C_SR1_SB));
	I2C_SendAddressR(sla_addr); //ad + r

	while(!(I2C1->SR1 & I2C_SR1_ADDR)); //clear addr flag
	I2C_ClearAddrFlag();

	for(uint8_t i = 0; i < count; i++) {
		if(i == (count - 1)) {
			I2C1->CR1 &= ~I2C_CR1_ACK; //disable acknowledge
			I2C1->CR1 |= I2C_CR1_STOP; //stop condition
		}
		while(!(I2C1->SR1 & I2C_SR1_RXNE));
		dest[i] = I2C1->DR; //read register
	}
}

void i2c::iread(uint8_t sla_addr, uint8_t addr, uint8_t* dest, uint8_t count) {
	while(1)
	uint8_t busystate = TxRxState;
	
	
}

void i2c::I2C_CloseTx() {
	disableInterrupt(31);
	I2C1->CR2 &= ~I2C_CR2_ITBUFEN;
	I2C1->CR2 &= ~I2C_CR2_ITEVTEN;

	TxRxState = I2C_READY;
	txBuffer = NULL;
	txLen = 0;
}

void i2c::I2C_CloseRx() {
	disableInterrupt(31);
	I2C1->CR2 &= ~I2C_CR2_ITBUFEN;
	I2C1->CR2 &= ~I2C_CR2_ITEVTEN;

	rxBuffer = NULL;
	rxLen = 0;
	rxSize = 0;

	TxRxState = I2C_READY;
}

void i2c::I2C_EV_ISR() {
	//Interrupt handling for both master and slave mode of a device
	uint32_t temp1, temp2, temp3;
	temp1 = (I2C1->CR2 & I2C_CR2_ITEVTEN);
	temp2 = (I2C1->CR2 & I2C_CR2_ITBUFEN);

	temp3 = (I2C1->SR1 & I2C_SR1_SB);
	//1. Handle For interrupt generated by SB event
	//	Note : SB flag is only applicable in Master mode
	if(temp1 && temp3) {
		//SB flag set, send address next
		if(TxRxState == I2C_BUSY_TX) {
			I2C_SendAddressW(devAddr);
		}
		else if(TxRxState == I2C_BUSY_RX) {
			I2C_SendAddressR(devAddr);
		}
	}

	temp3 = (I2C1->SR1 & I2C_SR1_ADDR);
	//2. Handle For interrupt generated by ADDR event 
	//Note : When master mode : Address is sent 
	//		 When Slave mode   : Address matched with own address 
	if(temp1 && temp3) {
		I2C_ClearAddrFlag();
	}

	temp3 = (I2C1->SR1 & I2C_SR1_BTF);
	//3. Handle For interrupt generated by BTF(Byte Transfer Finished) event  
	if(temp1 && temp3) {
		if((TxRxState == I2C_BUSY_TX) && (txLen == 0)) {
			if(I2C1->SR1 & I2C_SR1_TXE) {
				I2C_GenerateStop();
				I2C_CloseTx();
			}
		}
		else if(TxRxState == I2C_BUSY_RX) {

		}
	}


	temp3 = (I2C1->SR1 & I2C_SR1_STOPF);
	//4. Handle For interrupt generated by STOPF event 
	// Note : Stop detection flag is applicable only slave mode . For master this flag will never be set
	if(temp1 && temp3) {
		I2C1->CR1 |= 0x0000;
	}

	temp3 = (I2C1->SR1 & I2C_SR1_TXE);
	//5. Handle For interrupt generated by TXE event 
	if(temp1 && temp2 && temp3) {
		if(I2C1->SR2 & I2C_SR2_MSL) {
			if((TxRxState == I2C_BUSY_TX) && (txLen > 0)) {
				if(regAddrSent) {
					I2C1->DR = *txBuffer;
					txBuffer++;
					txLen--;
				}
				else {
					I2C1->DR = regAddr;
					regAddrSent = true;
				}
				
			}
		}
		
	}

	temp3 = (I2C1->SR1 & I2C_SR1_RXNE);
	//6. Handle For interrupt generated by RXNE event 
	if(temp1 && temp2 && temp3) {
		if(I2C1->SR2 & I2C_SR2_MSL) {
			if(TxRxState == I2C_BUSY_RX) {
				I2C_RXNE_Handler();
			}
		}
	}
}

void I2C1_EV_Handler() {
	I2C.I2C_EV_ISR();
}

void I2C1_ER_Handler() {

}
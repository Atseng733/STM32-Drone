#include <i2c.h>

i2c I2C;
static volatile uint8_t isr_sla_addr; //7 bit slave address
volatile uint8_t isr_addr;
volatile uint8_t isr_data;

volatile bool data_ready;
volatile bool isr_complete;
volatile bool txrx; //tx = 0 rx = 1
volatile bool txrx_complete;
volatile bool repeat_start;

void i2c::init() {
	RCC->APB1ENR |= (0x01 << 21);
	I2C1->CR1 = 0x0000;
	I2C1->CR2 = 0x0000;

	I2C1->CR2 = 0x0010; 	  //set peripheral clock (in MHz)
	I2C1->CCR |= 0x8014;	  //adjust bus speed
	I2C1->TRISE |= 0x0005; //set max rise time
	I2C1->CR1 |= 0x0400;   //enable acknowledge

	pinMode(GPIOB, 6, OUTPUT);
	pinConfig(GPIOB, 6, AFO_OD);
	pinMode(GPIOB, 7, OUTPUT);
	pinConfig(GPIOB, 7, AFO_OD);

	I2C1->CR1 |= 0x0001; //enable i2c

	USART.println("I2C initialized");
}

void i2c::start() {
	I2C1->CR1 |= 0x0100; //set start bit
	while(!(I2C1->SR1 & 0x0001)); //wait
}

uint8_t i2c::send(uint8_t data) {
	I2C1->DR = data;
	while(!(I2C1->SR1 & 0x0080));
}

uint8_t i2c::sla_w(uint8_t sla_addr) {
	uint32_t temp;

	I2C1->DR = (sla_addr << 1);
	while(!(I2C1->SR1 & 0x0002));
	temp = I2C1->SR2;

	return 1;
}

uint8_t i2c::sla_r(uint8_t sla_addr) {
	uint32_t temp;

	I2C1->DR = ((sla_addr << 1) + 1);
	while(!(I2C1->SR1 & 0x0002));
	temp = I2C1->SR2;

	return 1;
}

void i2c::stop() {
	I2C1->CR1 |= 0x0200;
	while(I2C1->SR1 & 0x0004);
}

void i2c::write(uint8_t sla_addr, uint8_t addr, uint8_t data) {
	uint32_t temp;

	I2C1->CR1 |= 0x0100;
	while(!(I2C1->SR1 & 0x0001));

	I2C1->DR = (sla_addr << 1);
	while(!(I2C1->SR1 & 0x0002));
	temp = I2C1->SR2;

	I2C1->DR = addr;
	while(!(I2C1->SR1 & 0x0080));

	I2C1->DR = data;
	while(!(I2C1->SR1 & 0x0080));

	I2C1->CR1 |= 0x0200;
	while(I2C1->SR1 & 0x0080 || I2C1->SR1 & 0x0040 || I2C1->SR1 & 0x0004);
}

void i2c::iwrite(uint8_t sla_addr, uint8_t addr, uint8_t data) {
	isr_sla_addr = sla_addr;
	isr_addr = addr;
	isr_data = data;
	//isr_count = count;
	data_ready = false;
	isr_complete = false;
	txrx = false;
	txrx_complete = false;
	repeat_start = false;

	I2C1->CR2 |= 0x0600; //enable itbuf and itev interrupts
	enableInterrupt(31);

	I2C1->CR1 |= 0x0100; //start

	while(!txrx_complete);
}

uint8_t i2c::read(uint8_t sla_addr, uint8_t addr) {
	uint8_t data;
	uint32_t temp;
	I2C1->CR1 |= 0x0400;   //enable acknowledge

	I2C1->CR1 |= 0x0100;   //start condition
	while(!(I2C1->SR1 & 0x0001));

	I2C1->DR = (sla_addr << 1); //ad + w
	while(!(I2C1->SR1 & 0x0002));
	temp = I2C1->SR2;

	I2C1->DR = addr;					//register address to read from
	while(!(I2C1->SR1 & 0x0080));

	I2C1->CR1 |= 0x0100;   //repeat start
	while(!(I2C1->SR1 & 0x0001));

	I2C1->DR = ((sla_addr << 1) + 1); //ad + r
	while(!(I2C1->SR1 & 0x0002));
	I2C1->CR1 &= ~0x0400; //disable acknowledge
	temp = I2C1->SR2;

	I2C1->CR1 |= 0x0200; //stop condition

	while(!(I2C1->SR1 & 0x0040));
	data = I2C1->DR; //read register

	return data;
}

void i2c::read(uint8_t sla_addr, uint8_t addr, uint8_t count, uint8_t* dest) {
	uint32_t temp;
	I2C1->CR1 |= 0x0400;   //enable acknowledge

	I2C1->CR1 |= 0x0100;   //start condition
	while(!(I2C1->SR1 & 0x0001));

	I2C1->DR = (sla_addr << 1); //ad + w
	while(!(I2C1->SR1 & 0x0002));
	temp = I2C1->SR2;

	I2C1->DR = addr;			//register address to read from
	while(!(I2C1->SR1 & 0x0080));

	I2C1->CR1 |= 0x0100;   //repeat start
	while(!(I2C1->SR1 & 0x0001));
	I2C1->DR = ((sla_addr << 1) + 1); //ad + r

	while(!(I2C1->SR1 & 0x0002)); //clear addr flag
	temp = I2C1->SR2;

	for(uint8_t i = 0; i < count; i++) {
		if(i == (count - 1)) {
			I2C1->CR1 &= ~0x0400; //disable acknowledge
			I2C1->CR1 |= 0x0200; //stop condition
		}
		while(!(I2C1->SR1 & 0x0040));
		dest[i] = I2C1->DR; //read register
	}
}

/*uint8_t i2c::iread(uint8_t sla_addr, uint8_t addr, uint8_t count, uint8_t* dest) {
	isr_sla_addr = sla_addr;
	isr_addr = addr;

	data_ready = false;
	isr_complete = false;
	txrx = true;
	txrx_complete = false;
	repeat_start = false;

	I2C1->CR1 |= 0x0400;   //enable acknowledge
	I2C1->CR2 |= 0x0600; //enable itbuf and itev interrupts
	enableInterrupt(31);

	I2C1->CR1 |= 0x0100;   //start condition
	
	while(!txrx_complete);
	USART.println("ahhhhhhhhhhhhhhhHH");
	return isr_data;
}*/

/*void I2C1_EV_Handler() {
	uint32_t temp;
	
	if(isr_complete) {
		disableInterrupt(31);
		I2C1->CR1 |= 0x0200; //stop
		txrx_complete = true;
		data_ready = false;
	}

	if(data_ready) {
		I2C1->DR = isr_data;
		data_ready = false;
		isr_complete = true;
	}

	if(I2C1->SR1 & 0x0001) {
		I2C1->DR = isr_sla_addr;
	}
	else if(I2C1->SR1 & 0x0002) {
		temp = I2C1->SR2;
		I2C1->DR = isr_addr;
		data_ready = true;
	}
}*/

void I2C1_EV_Handler() {
	uint32_t temp; //temp variable for reading status register 2 (needed to clear addr bit)

	if(isr_complete && txrx) {
		disableInterrupt(31);
		txrx_complete = true;
	}
	else if(isr_complete && !txrx) {
		disableInterrupt(31);
		I2C1->CR1 |= 0x0200; //stop
		txrx_complete = true;
	}

	if(data_ready && !repeat_start) {
		I2C1->DR = isr_data;
		isr_complete = true;
	}
	else if(!data_ready && repeat_start) {
		I2C1->CR1 |= 0x0100;   //repeat start
	}


	if((I2C1->SR1 & 0x0002) && txrx && !repeat_start) { //if addr flag set and repeat start
		temp = I2C1->SR2;		 //clear flag
		I2C1->DR = isr_addr;  //send address to write to
		repeat_start = true;
		data_ready = false;
	}
	else if (txrx && repeat_start && (I2C1->SR1 & 0x0002)) {
		I2C1->CR1 &= ~0x0400; //disable acknowledge
		temp = I2C1->SR2;
		isr_data = I2C1->DR; //read data
		I2C1->CR1 |= 0x0200;  //stop condition
		disableInterrupt(31);
		txrx_complete = true;
	}
	else if ((I2C1->SR1 & 0x0002) && !txrx) {
		temp = I2C1->SR2;
		I2C1->DR = isr_addr; //send register address
		repeat_start = false;
		data_ready = true;
	}
 

	if((I2C1->SR1 & 0x0001) && !repeat_start) { //restart condition -> begin read operation
		I2C1->DR = (isr_sla_addr << 1); //send slave address + w
	}
	else if((I2C1->SR1 & 0x0001) && repeat_start) {
		I2C1->DR = (isr_sla_addr << 1) | 1; //send slave address + r
	}
}
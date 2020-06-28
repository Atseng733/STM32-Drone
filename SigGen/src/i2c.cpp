#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

#define F_CPU 16000000UL
#define SDA 4
#define SCL 5 

void I2CStart(unsigned char adr)
{
	DDRC |= 0x30; //set SDA and SCL pins to outputs
	PORTC &= ~(1<<PORTC4);	//SDA
	PORTC &= ~(1<<PORTC5);  //SCL
	
	char i;
	char rc;


	for (i=0;i<7;i++)
	{
		rc = adr & 0x40;
		if (rc == 0x00)
			PORTC &= ~(1<<SDA);	//data pin
		else
			PORTC |= (1<<SDA);	//data pin
		PORTC |= (1<<SCL);	//clk pin
		PORTC &= ~(1<<SCL);	//clk pin
		adr <<=1;
	}
	
	PORTC &= ~(1<<SDA);
	PORTC |= (1<<SCL);	//clk pin
	PORTC &= ~(1<<SCL);	//clk pin

	//ACK	
	PORTC |= (1<<SCL);	//clk pin
	PORTC &= ~(1<<SCL);	//clk pin
}

void I2CStop(void)
{
	PORTC |= (1<<SCL);  //SCL
	PORTC |= (1<<SDA);	//SDA
}


void write8(unsigned char adr,unsigned char reg, unsigned char value) 
{
	I2CStart(adr);
	I2CSend( reg );
	I2CSend( value );
	I2CStop();
}


void I2CSend(unsigned char data)
{
	char i;
	char rc;

	for (i=0;i<8;i++)
	{
		rc = data & 0x80;
		if (rc == 0x00)
			PORTC &= ~(1<<SDA);	//data pin
		else
			PORTC |= (1<<SDA);	//data pin
		
		PORTC |= (1<<SCL);	//clk pin
		PORTC &= ~(1<<SCL);	//clk pin
		data <<= 1;
	}
	
	PORTC |= (1<<SCL);	//clk pin
	PORTC &= ~(1<<SCL);	//clk pin
}











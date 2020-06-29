/*
 * spi.cpp
 *
 * Created: 6/12/2020 5:04:18 PM
 *  Author: Anthony
 */ 
#include "spi.h"
#include <usart.h>

spi::spi() {
//	print("Initializing SPI object ");
}
void spi::begin() {
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	
	DDRB = (1<<DDB3) | (1<<DDB2) | (1<<DDB5);
	//DDRB |= (1<<DDB3) | (1<<DDB5);
	//print("SPI begin ");
}

void spi::transfer8(char data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	//print("SPI transfer8" );
}

void spi::transfer16(int data) {
	SPDR = data>>8;
	while(!(SPSR & (1<<SPIF))); //msb first
	SPDR = data &= 0x00FF;
	while(!(SPSR & (1<<SPIF))); //lsb second
	//print("SPI transfer16 ");
}

void spi::setMode(unsigned char mode) {
	switch(mode) {
		case 0:
		SPCR &= 0xF3;
		break;
		case 1:
		SPCR &= 0xF7;
		SPCR |= 0x04;
		break;
		case 2:
		SPCR &= 0xFB;
		SPCR |= 0x08;
		break;
		case 3:
		SPCR |= 0x0C;
		break;
	}
}
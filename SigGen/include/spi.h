/*
 * spi.h
 *
 * Created: 6/12/2020 5:00:28 PM
 *  Author: Anthony
 */ 
#include <avr/io.h>
#include <m328io.h>

#ifndef SPI_H_
#define SPI_H_

class spi {
public:
	spi();
	void begin();
	void transfer8(char data);
	void transfer16(int data);
	void setMode(unsigned char mode);
};

#endif /* SPI_H_ */
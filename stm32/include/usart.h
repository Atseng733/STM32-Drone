#ifndef USART_H
#define USART_H

#include <boards.h>
#include <f1_gpio.h>
#include <stm32_stdlib.h>

#define USART_BAUD 115200 //change this to set the baudrate

#define BRR_MANTISSA(baud) ((double)F_CPU / (16 * baud))
#define BRR_FRACTION(baud) (uint16_t)(BRR_MANTISSA(baud) - (uint16_t)(BRR_MANTISSA(baud))) * 16

class usart {
public:
	usart() {};
	void init();
	void putc(char c);
	void put(char* str);
	void putln(char* str);
	void transmit();
	void printc(char c);
	void print(char* str);
	void println(char* str);
	void print(int64_t i, uint8_t base = 10);
	void println(int64_t i, uint8_t base = 10);
};

extern usart USART;

#endif
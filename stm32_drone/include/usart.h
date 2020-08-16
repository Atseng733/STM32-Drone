#ifndef USART_H
#define USART_H

#include <boards.h>
#include <stm32_stdlib.h>
#include <rcc.h>
#include <interrupt.h>

#ifndef USART_BAUD
#define USART_BAUD 115200 //change this to set the baudrate
#endif

#define BRR_MANTISSA(baud) ((double)F_CPU / (16 * baud))
#define BRR_FRACTION(baud) (uint16_t)((BRR_MANTISSA(baud) - (uint16_t)(BRR_MANTISSA(baud))) * 16)

#define USART_READY 0
#define USART_BUSY_TX 1
#define USART_BUSY_RX 2


class usart {
public:
	usart() {};
	void init(USART_Typedef* usartx, uint32_t baudrate);
	void putc(char c);
	void put(char* str);
	void putln(char* str);
	void putln(int64_t i, uint8_t base);
	void transmit();
	void printc(char c);
	void print(char* str);
	void println(char* str);
	void print(int64_t i, uint8_t base);
	void println(int64_t i, uint8_t base);
	void println(double d);
	uint8_t receiveIT(uint8_t* dest,  uint32_t len);
	uint8_t read(uint8_t* dest, uint32_t len, uint8_t start);
	uint8_t read();
	uint8_t readSync(uint8_t* dest,  uint32_t len, uint8_t start);
	
};

extern usart USART;

#endif
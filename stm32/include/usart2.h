#ifndef USART2_H
#define USART2_H

#include <f407.h>
#include <f407_fn.h>
#include <stm32_stdlib.h>

#define BRR_VALUE BRR_115200 //change this to set the baudrate
#define BRR_9600 0x0688
#define BRR_19200 0x0341
#define BRR_115200 0x008B

class usart2 {
public:
	usart2() {};
	void init();
	void putc(char c);
	void put(char* str);
	void putln(char* str);
	void transmit();
	void printc(char c);
	void print(char* str);
	void println(char* str);
	void print(int64_t i, uint8_t base);
	void println(int64_t i, uint8_t base);
};

extern usart2 USART;

#endif
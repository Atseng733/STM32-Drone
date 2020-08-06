#ifndef USART_H
#define USART_H

#include <f407.h>
#include <f407_fn.h>
#include <interrupt.h>
#include <stm32_stdlib.h>

class usart {
public:
	usart() {};
	void init();
	void printc(char c);
	void print(char* str);
	void print(uint64_t w);
	void print(uint64_t w, uint8_t base);
	void println(char* str);
	void println(uint64_t w);
	void println(uint64_t w, uint8_t base);
};

#endif
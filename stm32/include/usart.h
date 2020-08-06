#ifndef USART_H
#define USART_H

#include <f407.h>
#include <f407_fn.h>
#include <interrupt.h>
#include <stdlib.h>

class usart {
public:
	usart() {};
	void init();
	void printc(char c);
	void print(char str[]);
	void print(long w);
	void print(long w, uint8_t base);
	void println(char str[]);
	void println(long w);
	void println(long w, uint8_t base);
};

#endif
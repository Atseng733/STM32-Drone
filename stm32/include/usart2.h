#ifndef USART2_H
#define USART2_H

#include <f407.h>
#include <f407_fn.h>

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
};



#endif
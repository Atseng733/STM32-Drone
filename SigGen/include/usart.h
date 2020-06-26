#ifndef USART_H
#define USART_H
#include <m328io.h>
#include <avr/interrupt.h>
#include <stdint.h>
//default baudrate
#ifndef USART_BAUD 
#define USART_BAUD 9600
#endif
//ubrr register value
#define UBRR_VALUE ((F_CPU / (USART_BAUD * 16UL)) - 1)

void usart_init();
void usart_test();
void printc(uint8_t c);
void printcint(uint8_t c);
void print(char str[]);


#endif
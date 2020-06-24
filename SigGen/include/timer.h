#ifndef TIMER_H
#define TIMER_H
#include <m328io.h>
#include <avr/interrupt.h>


//disable compare registers and enable timer overflow interrupt
void timer_init();
uint32_t millis();
void delay(uint32_t ms);


#endif
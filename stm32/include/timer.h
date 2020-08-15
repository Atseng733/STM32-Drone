#ifndef TIMER_H
#define TIMER_H
#include <boards.h>
#include <interrupt.h>
#include <usart.h>
#include <stdlib.h>
#include <rcc.h>

#define SYSTICK_LOAD ((uint32_t)((F_CPU/1000000)*10)) //reload every 10us

void timer_init();
uint32_t micros();
uint32_t millis();
void delay_us(uint32_t _us);
void delay_ms(uint32_t _ms);

#endif
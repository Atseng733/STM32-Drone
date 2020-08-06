#ifndef TIMER_H
#define TIMER_H
#include <f407.h>
#include <f407_fn.h>
#include <interrupt.h>
#include <usart.h>
#include <stdlib.h>

void TIM6_init();
uint64_t millis();
void delay_ms(uint16_t _ms);

#endif
#ifndef TIMER_H
#define TIMER_H
#include <f407.h>
#include <f407_fn.h>
#include <interrupt.h>
#include <usart.h>
#include <stdlib.h>

extern "C" void TIM6_init();
uint32_t millis();
void delay_ms(uint32_t _ms);

#endif
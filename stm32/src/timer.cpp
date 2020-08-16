#include <timer.h>

volatile uint32_t ticks; //1 tick = 1ms

void timer_init() {
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE | SysTick_CTRL_TICKINT; //enable interrupt and use ahb clock
	SysTick->LOAD = SYSTICK_LOAD; //set reload register value
	SysTick->CTRL |= SysTick_CTRL_ENABLE; //enable counter
}

uint32_t micros() {
	return (ticks * 1000) + (uint64_t)((SYSTICK_LOAD - SysTick->VAL) / ((double)(SYSTICK_LOAD)) * 1000);
}

uint32_t millis() {
	return ticks;
}

void delay_us(uint32_t _us) {
	uint32_t end_time = micros() + _us;
	while (micros() < end_time);
}

void delay_ms(uint32_t _ms) {
	uint32_t end_time = millis() + _ms;
	while (millis() < end_time);
}

void SysTick_Handler() {
	ticks += 1;
}
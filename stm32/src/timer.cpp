#include <timer.h>
usart2 timer_usart;
volatile uint64_t ticks;
uint32_t ms;
// static volatile long ticks; //1 tick = 1us

void TIM6_init() {
	ticks = 0;
	RCC->APB1ENR |= 0x0010; //enable timer clock
	//RCC->APB1RSTR |= 0x10;
	//RCC->APB1RSTR &= ~(0x10);
	TIM6->CR1 |= 0x0004; //update interrupt generated on counter ovf/underflow only
	TIM6->DIER |= 0x0001; //enable update interrupt
	TIM6->EGR |= 0x0001; //update generation
	TIM6->PSC = 0x000F; //set prescaler to PSC + 1
	TIM6->ARR = 0x0100; //set auto reload register value
	TIM6->CR1 |= 0x0001; //enable counter
	enableInterrupt(54); //enable interrupts;

	timer_usart.println("TIM6 initialized");
}

uint32_t millis() {
	ms = (ticks / (uint64_t)1000);
	return ms;
}

void delay_ms(uint32_t _ms) {
	uint32_t end_time = millis() + _ms;
	while (millis() < end_time);
}

void TIM6_DAC_Handler() {
	TIM6->SR = 0x0000;
	ticks += 256;
}
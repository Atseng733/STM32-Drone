#include <timer.h>
usart timer_usart;

volatile uint64_t ticks = 0; //1 tick = 1us

void TIM6_init() {
	RCC->APB1ENR |= 0x0010; //enable timer clock
	RCC->APB1RSTR |= 0x10;
	RCC->APB1RSTR &= ~(0x10);
	TIM6->CR1 |= 0x0004; //update interrupt generated on counter ovf/underflow only
	TIM6->DIER |= 0x0001; //enable update interrupt
	TIM6->EGR |= 0x0001; //update generation
	TIM6->PSC = 0x000F; //set prescaler to PSC + 1
	TIM6->ARR = 0x0100; //set auto reload register value
	TIM6->CR1 |= 0x0001; //enable counter

	enableInterrupt(54); //enable interrupts
	timer_usart.println("TIM6 initialized");
}

uint64_t millis() {
	return (ticks / 1000);
}

void delay_ms(uint16_t _ms) {
	//TIM6->CR1 |= 0x0001; //enable counter
	uint64_t end_time = millis() + _ms;
	while((ticks/1000) < end_time) {
		timer_usart.printc('a');
	}
	//TIM6->CR1 &= ~0x0001; //disable counter
}

void TIM6_DAC_Handler() {
	while(!(TIM6->SR | 0)) {
		TIM6->SR &= ~0x0001;
		ticks+=256;
	}
	timer_usart.printc('t');
}
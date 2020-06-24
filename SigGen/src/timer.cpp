#include <timer.h>

uint32_t _millis = 0;
uint32_t _old_millis = 0;
uint16_t _1000us = 0;

ISR(TIMER0_OVF_vect) {
	_1000us += 128;
	while(_1000us > 1000) {
		_millis++;
		_1000us -= 1000;
	}
}

//disable compare registers and enable timer overflow interrupt
void timer_init() {
	TCCR0A = 0x00;
	TCCR0B = 0x02;
	TIMSK0 = 0x01;
	sei();
}

//return total elapsed time in milliseconds
uint32_t millis() {
	#ifdef INIT
	#else 
	timer_init();
	#define INIT 1
	#endif

	return _millis;
}

void delay(uint32_t ms) {
	_old_millis = millis();
	while(millis() - _old_millis < ms);
}
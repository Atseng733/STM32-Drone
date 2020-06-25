#include <avr_io.h>

//sets a pin's state by writing to DDR and PORT registers
void pinMode(uint8_t pin, uint8_t mode) {
	switch(pin) {
		//digital pins D0...D7
		case 0 ... 7:
		
			if(mode == INPUT) {
				DDRD &= ~(1<<pin);
				PORTD &= ~(1<<pin);
			}
			else if(mode == OUTPUT) {
				DDRD |= (1<<pin);
				PORTD &= ~(1<<pin);
			}
			else if(mode == INPUT_PULLUP) {
				DDRD &= ~(1<<pin);
				PORTD |= (1<<pin);
			}
			break;
		
		//digital pins D8...D13
		case 8 ... 13:
		
			if(mode == INPUT) {
				DDRB &= ~(1<<(pin-8));
				PORTB &= ~(1<<(pin-8));
			}
			else if(mode == OUTPUT) {
				DDRB |= (1<<(pin-8));
				PORTB &= ~(1<<(pin-8));
			}
			else if(mode == INPUT_PULLUP) {
				DDRB &= ~(1<<(pin-8));
				PORTB |= (1<<(pin-8));
			}
			break;
		
		//analog pins A0...A5
		case 14 ... 19:
		
			if(mode == INPUT) {
				DDRC &= ~(1<<(pin-14));
				PORTC &= ~(1<<(pin-14));
			}
			else if(mode == OUTPUT) {
				DDRC |= (1<<(pin-14));
				PORTC &= ~(1<<(pin-14));
			}
			else if(mode == INPUT_PULLUP) {
				DDRC &= ~(1<<(pin-14));
				PORTC |= (1<<(pin-14));
			}
			break;
	}
}

void digitalWrite(uint8_t PIN, uint8_t STATE) {
	switch(PIN) {
		//pins D0...D7
		case 0 ... 7: 
		
			if(DDRD & 1<<PIN) {
				switch(STATE) {
					case HIGH:
					PORTD |= (1<<PIN);
					break;
					case LOW:
					PORTD &= ~(1<<PIN);
					break;
				}
			}
			break;
		//pins D8...D13
		case 8 ... 13:
		
			if(DDRB & 1<<(PIN-8)) {
				switch(STATE) {
					case HIGH:
					PORTB |= (1<<(PIN-8));
					break;
					case LOW:
					PORTB &= ~(1<<(PIN-8));
					break;
				}
			}
			break;
		//pins A0...A5
		case 14 ... 19:
		if(DDRC & 1<<(PIN-14)) {
			switch(STATE) {
				case HIGH:
				PORTC |= (1<<(PIN-14));
				break;
				case LOW:
				PORTC &= ~(1<<(PIN-14));
				break;
			}
		}
		break;
	}
}

uint8_t digitalRead(uint8_t PIN) {
	switch(PIN) {
		case 0 ... 7:
			if(PIND & (1<<PIN)) 
			return 1;
			else return 0;
			break;
		
		case 8 ... 13:
			if(PINB & (1<<(PIN-8)))
			return 1;
			else return 0;
			break;
			
		case 14 ... 19:
			if(PINC & (1<<(PIN-14))) 
			return 1;
			else return 0;
			break;
	}
	return 0;
}

/*void attachExInterrupt(unsigned char PIN, void(*userFunc)(void), unsigned char INT_TYPE) {
	if(PIN == 2) {
		switch(INT_TYPE) {
			case ON_LOW:
			EICRA &= ~(1<<ISC00);
			EICRA &= ~(1<<ISC01);
			break;
			case CHANGE:
			EICRA |= (1<<ISC00);
			EICRA &= ~(1<<ISC01);
			break;
			case FALLING_EDGE:
			EICRA &= ~(1<<ISC00);
			EICRA |= (1<<ISC01);
			break;
			case RISING_EDGE:
			EICRA |= (1<<ISC00);
			EICRA |= (1<<ISC01);
			break;
		}
		EIMSK |= (1<<INT0);
	}
	else if(PIN == 3) 
	{
		switch(INT_TYPE) 
		{
			case ON_LOW:
			EICRA &= ~(1<<ISC10);
			EICRA &= ~(1<<ISC11);
			break;
			case CHANGE:
			EICRA |= (1<<ISC10);
			EICRA &= ~(1<<ISC11);
			break;
			case FALLING_EDGE:
			EICRA &= ~(1<<ISC10);
			EICRA |= (1<<ISC11);
			break;
			case RISING_EDGE:
			EICRA |= (1<<ISC10);
			EICRA |= (1<<ISC11);
			break;
		}
		EIMSK |= (1<<INT1);
	}
	sei();
}*/
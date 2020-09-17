#include <f407_fn.h>

void pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinMode) {
	gpio->MODER &= ~GPIO_WORD_MASK(pin);
	gpio->MODER |= GPIO_MODE(pin, pinMode);
}

void pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinMode, uint8_t pupd) {
	gpio->MODER &= ~GPIO_WORD_MASK(pin);
	gpio->MODER |= GPIO_MODE(pin, pinMode);
 	gpio->PUPDR &= ~GPIO_WORD_MASK(pin);
	gpio->PUPDR |= GPIO_PUPD(pin, pupd);
}

void pinOutputConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t mode, uint8_t speed, uint8_t pupd) {
	gpio->OTYPER &= ~GPIO_HWORD_MASK(pin);
	gpio->OTYPER |= GPIO_OTYPE(pin, mode);

	gpio->OSPEEDR &= ~GPIO_WORD_MASK(pin);
	gpio->OSPEEDR |= GPIO_SPEED(pin, speed);

	gpio->PUPDR &= ~GPIO_WORD_MASK(pin);
	gpio->PUPDR |= GPIO_PUPD(pin, pupd);
}

void pinAFNConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t AFx, uint8_t otype, uint8_t speed, uint8_t pupd) {
	gpio->OTYPER &= ~GPIO_HWORD_MASK(pin);
	gpio->OTYPER |= GPIO_OTYPE(pin, otype);

	gpio->OSPEEDR &= ~GPIO_WORD_MASK(pin);
	gpio->OSPEEDR |= GPIO_SPEED(pin, speed);

	gpio->PUPDR &= ~GPIO_WORD_MASK(pin);
	gpio->PUPDR |= GPIO_PUPD(pin, pupd);

	switch(pin) {
		case 0 ... 7 : 
			gpio->AFRL |= (AFx << (4*pin));
			break;
		case 8 ... 15 :
			gpio->AFRH |= (AFx << (4*(pin-8)));
			break;
	}
}

void writeHigh(GPIO_Typedef* gpio, uint8_t pin) {
	gpio->BSRR |= (1 << pin);
}

void writeLow(GPIO_Typedef* gpio, uint8_t pin) {
	gpio->BSRR |= (1 << (pin + 16));
}

void toggle(GPIO_Typedef* gpio, uint8_t pin) {
	gpio->ODR ^= (1 << pin);
}

void pinReset(GPIO_Typedef* gpio, uint8_t pin);

uint8_t pinRead(GPIO_Typedef* gpio, uint8_t pin) {
	return (gpio->IDR & (1 << pin));
}
#include <f1_gpio.h>

void pinMode(GPIO_Typedef* gpio, uint8_t pin, uint8_t mode) {
	switch(pin) {
		case 0 ... 7:
			gpio->CRL &= ~GPIO_MODE_MASK(pin);
			gpio->CRL |= GPIO_MODE(pin, mode);
			break;
		case 8 ... 15:
			gpio->CRH &= ~GPIO_MODE_MASK(pin - 8);
			gpio->CRH |= GPIO_MODE((pin - 8), mode);
	}
}

void pinConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t config) {
	switch(pin) {
		case 0 ... 7:
			gpio->CRL &= ~GPIO_CNF_MASK(pin);
			gpio->CRL |= GPIO_CNF(pin, config);
			break;
		case 8 ... 15:
			gpio->CRH &= ~GPIO_CNF_MASK(pin - 8);
			gpio->CRH |= GPIO_CNF((pin - 8), config);
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

uint8_t digitalRead(GPIO_Typedef* gpio, uint8_t pin) {
	return ((gpio->IDR & (1 << pin)) >> pin);
}
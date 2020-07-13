#include <f407_fn.h>

void GPIO_pinConfig(GPIO_Typedef* gpio, uint8_t pin, uint8_t pinDir, uint8_t pupd) {
	/*if(gpio == GPIOA) {
		RCC->AHB1ENR |= 0x01;
	}*/

	RCC->AHB1ENR |= (1 << ((gpio-GPIOA)/0x0400));

	switch(pinDir) {
		case 0b00 :
			gpio->MODER &= ~(0b11 << (pin*2));
			gpio->PUPDR &= ~(0b11 << (pin*2));
			gpio->PUPDR |= (pupd << (pin*2));
		case 0b01 :
			gpio->MODER &= ~(2 << (pin*2));
			gpio->MODER |= (1 << (pin*2));
			gpio->PUPDR &= ~(0b11 << (pin*2));
			gpio->PUPDR |= (pupd << (pin*2));
	}
}

void GPIO_pinSet(GPIO_Typedef* gpio, uint8_t pin) {
	gpio->BSRR |= (1 << pin);
}

void GPIO_pinReset(GPIO_Typedef* gpio, uint8_t pin) {
	gpio->BSRR |= (1 << (pin + 16));
}

void GPIO_pinReset(GPIO_Typedef* gpio, uint8_t pin);
uint8_t GPIO_pinRead(GPIO_Typedef* gpio, uint8_t pin) {}
void testFunc() {}
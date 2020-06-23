#include <gpio.h>
#include <iostream>

void pinMode(uint8_t pin, uint8_t mode) {
	switch(mode) {
		case 1:
			GPEN_SET = (1<<pin);
			break;
		default:
			std::cout << "pinMode error" << std::endl;
	}
}

void digitalWrite(uint8_t pin, uint8_t mode) {
	switch(mode) {
		case HIGH:
			GPO_SET = (1<<pin);
			break;
		default:
			std::cout << "digitalWrite error" << std::endl;
	}
}
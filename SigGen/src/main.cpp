#include <main.h>

uint32_t old = 0;
uint32_t nuw = 0;

int main() {
	timer_init();
	pinMode(8, OUTPUT);
	while(1) {
		digitalWrite(8, HIGH);
		delay(1000);
		digitalWrite(8, LOW);
		delay(1000);
	}
}
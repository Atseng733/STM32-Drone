#include <debug.h>

void debug_flash() {
	pinMode(8, OUTPUT);
	digitalWrite(8, HIGH);
	delay(1000);
	digitalWrite(8, LOW);
	delay(1000);
}

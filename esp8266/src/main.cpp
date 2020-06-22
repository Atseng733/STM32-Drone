//#include <gpio.h>
#include "testConfig.h"
#include <iostream>
#include <functional>

#define LED_PIN 14

int main() {
	if (argc < 2) {
    // report version
    std::cout << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
  	}
	/*pinMode(LED_PIN, HIGH);

	while(1) {
		digitalWrite(LED_PIN, HIGH);
		delay_1s();
		digitalWrite(LED_PIN, LOW);
		delay_1s();
	}*/
}





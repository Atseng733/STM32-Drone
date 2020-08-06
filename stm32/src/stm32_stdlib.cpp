#include <stm32_stdlib.h>

char* itoa(char* str, uint64_t i, char base) {
 	bool decrement = false;

 	if(i == 0) {
 		*str = '0';
 		*(str + 1) = 0;
 		return str;
 	}

	switch(base) {
		case 2:
			*str = 48;
			str++;
			*str = 'b';
			str++;
			decrement = true;
			break;
		case 16:
			*str = 48;
			str++;
			*str = 'x';
			str++;
			decrement = true;
			break;
		default: 
			break;
	}

	char* cp = str;
	uint64_t tempi = i;
	int counter = 0;

	while(tempi > 0) {
		*cp = '0' + (tempi % base);
		cp++;
		tempi /= base;
		counter++;
	}
	*cp = 0;
	cp--;

	char tempc;
	for(int j = 0; j < counter/2; j++) {
		tempc = *(str + j);
		*(str + j) = *(cp - j);
		*(cp - j) = tempc;
	}

	if(decrement)	str -= 2;

	return str;
}
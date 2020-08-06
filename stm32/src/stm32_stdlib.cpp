#include <stm32_stdlib.h>

char* itoa(char* str, int64_t i, uint8_t base) {
 	bool decrement = false;
 	bool negative = false;
 	int64_t tempi = i;

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
			if(tempi < 0) {
				*str = '-';
				str++;
				negative = true;
				tempi *= -1;
			}
			break;
	}

	char* cp = str;
	int counter = 0;

	while(tempi > 0) {
		if((tempi % base) > 9) {
			*cp = '0' + 7 + (tempi % base);
		}
		else {
			*cp = '0' + (tempi % base);
		}
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
	if(negative) str--;

	return str;
}
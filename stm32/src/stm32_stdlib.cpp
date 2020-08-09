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
//59.532
char* dtoa(char* str, double d) {
	double tempd = d;
	int64_t tempi = (int64_t)(tempd);
	uint8_t int_length;
	uint8_t dec_cnt = 0;
	char* cp = str;

	while(tempi/10 > 1) {
		int_length++;
		tempi /= 10;
	}

	tempi = (int64_t)(tempd);

	itoa(str, tempi, 10);
	cp += int_length;
	*cp = '.';
	cp++;
	USART.println(str);
	while((tempd - (int64_t)(tempd)) > 0) {
		tempd *= 10;
		dec_cnt++;
	}

	tempd = (int64_t)(tempd - (tempi * pow(10, dec_cnt)));

	itoa(cp, tempd, 10);
	cp += dec_cnt;
	//if(dec_cnt == 0) cp++;
	*cp = 0;
	
	return str;
}
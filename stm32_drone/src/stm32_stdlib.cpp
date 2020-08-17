#include <stm32_stdlib.h>
char stdlib_str[32];

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
//59.5320000000000000000
/*char* dtoa(char* str, double d, uint8_t prec) {
	double tempd = d + (1/pow(10, prec + 1));
	int64_t tempi = (int64_t)(tempd);
	uint8_t int_length;
	uint8_t dec_cnt = 0;
	char* cp = str;
	USART.println(tempi);

	while((tempd - (int)(tempd)) > 0) {
		tempd *= 10;
		dec_cnt++;
	}
	USART.println(dec_cnt);

	tempi = (d * pow(10, dec_cnt));
	USART.println(tempi);

	for(int i; i < (int_length + dec_cnt); i++) {
		if(i == dec_cnt) {
			*cp = '.';
			cp++;
		}

		*cp = tempi % 10;
		cp++;
		tempi /= 10;
	}

	return str;
}*/
static double PRECISION = 0.0001;
static int MAX_NUMBER_STRING_SIZE = 32;

/**
 * Double to ASCII
 */
char * dtoa(char *s, double n) {
    // handle special cases
    if (isnan(n)) {
        //strcpy(s, "nan");
    } else if (isinf(n)) {
        //strcpy(s, "inf");
    } else if (n == 0.0) {
        //strcpy(s, "0");
    } else {
        int digit, m, m1;
        char *c = s;
        int neg = (n < 0);
        if (neg)
            n = -n;
        // calculate magnitude
        m = log10(n);
        int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
        if (neg)
            *(c++) = '-';
        // set up for scientific notation
        if (useExp) {
            if (m < 0)
               m -= 1.0;
            n = n / pow(10.0, m);
            m1 = m;
            m = 0;
        }
        if (m < 1.0) {
            m = 0;
        }
        // convert the number
        while (n > PRECISION || m >= 0) {
            double weight = pow(10.0, m);
            if (weight > 0 && !isinf(weight)) {
                digit = floor(n / weight);
                n -= (digit * weight);
                *(c++) = '0' + digit;
            }
            if (m == 0 && n > 0)
                *(c++) = '.';
            m--;
        }
        if (useExp) {
            // convert the exponent
            int i, j;
            *(c++) = 'e';
            if (m1 > 0) {
                *(c++) = '+';
            } else {
                *(c++) = '-';
                m1 = -m1;
            }
            m = 0;
            while (m1 > 0) {
                *(c++) = '0' + m1 % 10;
                m1 /= 10;
                m++;
            }
            c -= m;
            for (i = 0, j = m-1; i<j; i++, j--) {
                // swap without temporary
                c[i] ^= c[j];
                c[j] ^= c[i];
                c[i] ^= c[j];
            }
            c += m;
        }
        *(c) = '\0';
    }
    return s;
}

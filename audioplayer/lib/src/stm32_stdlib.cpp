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

/**
 * Double to ASCII
 * from https://stackoverflow.com/questions/2302969/convert-a-float-to-a-string
 */
char * dtoa(char *s, double n, uint8_t prec) {
	const double PRECISION = (1 / pow(10, prec));

    // handle special cases
    if (isnan(n)) {
        //strcpy(s, "nan");
    } else if (isinf(n)) {
        //strcpy(s, "inf");
    } else if (n == 0.0) {
        *s = '0';
        *(s + 1) = 0;
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

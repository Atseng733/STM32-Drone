#ifndef STM32_STDLIB_H
#define STM32_STDLIB_H
#include <boards.h>
#include <math.h>
#include <usart.h>

char* itoa(char* str, int64_t i, uint8_t base = 10);
char* dtoa(char* str, double d);

extern char stdlib_str[32];

#endif
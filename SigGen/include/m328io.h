#ifndef M328IO_H
#define M328IO_H
#include <stdint.h>

//pin io types
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
//pin io states
#define LOW 0
#define HIGH 1
//interrupt types

//special function registers
#define REG_DEF(addr) *((volatile uint8_t*)(addr))
#define PINB REG_DEF(0x23)
#define DDRB REG_DEF(0x24)
#define PORTB REG_DEF(0x25)
#define PINC REG_DEF(0x26)
#define DDRC REG_DEF(0x27)
#define PORTC REG_DEF(0x28)
#define PIND REG_DEF(0x29)
#define DDRD REG_DEF(0x2A)
#define PORTD REG_DEF(0x2B)

#endif
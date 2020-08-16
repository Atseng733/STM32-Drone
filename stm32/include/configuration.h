#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define BOARD_F103 //select which board from boards.h
#define F_CPU 48000000UL //cpu frequency max 48MHz

#define PLL_CLK_SRC 1 //0: high speed internal/2		1: high speed external/2

#define USART_BAUD 230400
#define I2C_FREQ 200000

#endif
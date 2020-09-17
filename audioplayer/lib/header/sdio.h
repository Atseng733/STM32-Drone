#ifndef SDIO_H
#define SDIO_H
#include <boards.h>
#include <rcc.h>
#include <timer.h>
#include <usart.h>

void SDIO_CMD(uint32_t cmd, uint32_t arg);
void SDIO_Init();

#endif
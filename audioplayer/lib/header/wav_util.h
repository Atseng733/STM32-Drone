#ifndef WAV_UTIL_H
#define WAV_UTIL_H

#include <boards.h>
#include <dac.h>
#include <usart.h>

uint8_t GetWavContent(uint8_t* data);
template <typename T> T GetValue(T* type, uint16_t offset, uint8_t n, uint8_t* data);
#endif
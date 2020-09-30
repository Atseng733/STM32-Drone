#ifndef DAC_H
#define DAC_H

#include <boards.h>

#define DAC_TSEL_TIM6 0x0
#define DAC_TSEL_TIM8 0x1
#define DAC_TSEL_TIM7 0x2
#define DAC_TSEL_TIM5 0x3
#define DAC_TSEL_TIM2 0x4
#define DAC_TSEL_TIM4 0x5
#define DAC_TSEL_EXTI9 0x6
#define DAC_TSEL_SW 0x7

typedef struct {
	uint32_t CR;
} DAC_Struct;

void DAC_Init(DAC_Struct* pStruct);
template <typename T> void DAC_OutputData(T* data);

#endif
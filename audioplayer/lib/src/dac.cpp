#include <dac.h>

void DAC_Init(DAC_Struct* pStruct) {
	//Enable DAC clock
	DAC_CLK_EN;

	//Enable DAC channel 1 by setting EN1 in control register
	DAC->CR |= pStruct->CR;

	//enable dac output buffer to drive output without external amp

	DAC->DHR8R1 = 0xFF;
}

template <typename T> void DAC_OutputData(T* data) {
	
}
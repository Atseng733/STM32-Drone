#include <adv_timer.h>

void adv_timer::Init(Adv_Timer_Struct* pstruct) {
	pStruct = pstruct;

	if(pStruct->TIMx == TIM2) {
		TIM2_CLK_EN;
	}
	else if(pStruct->TIMx == TIM3) {
		TIM3_CLK_EN;
	}
	else if(pStruct->TIMx == TIM4) {
		TIM4_CLK_EN;
	}
	else if(pStruct->TIMx == TIM5) {
		TIM5_CLK_EN;
	}

	pStruct->TIMx->DIER |= pStruct->DIER;
	pStruct->TIMx->PSC = pStruct->PSC;
	Serial2.println(pStruct->TIMx->PSC, 16);
	pStruct->TIMx->ARR = pStruct->ARR;
	Serial2.println(pStruct->TIMx->ARR, 16);

	// pStruct->TIMx->CR2 = pStruct->CR2;
	// Serial1.println(pStruct->TIMx->CR2, 16);
	// pStruct->TIMx->CR1 = pStruct->CR1;
	// Serial1.println(pStruct->TIMx->CR1, 16);
	// pStruct->TIMx->CR1 |= GEN_TIM_CR1_CEN;
}
/*
void adv_timer::Configure(Adv_Timer_Config &config) {
	TIMx->CR1 = config.CR1;
	TIMx->DIER = config.DIER;
}*/

void adv_timer::OC1_Enable(uint8_t mode) {
	pStruct->TIMx->CCMR1 &= ~(0x7 << 4);
	pStruct->TIMx->CCMR1 |= (mode << 4);
	pStruct->TIMx->CCER |= 0x0001; //enable ch1 capture
}

void adv_timer::setCCR1(uint16_t ccr1) {
	pStruct->TIMx->CCR1 = ccr1;
}

void adv_timer::OC2_Enable(uint8_t mode) {
	pStruct->TIMx->CCMR1 &= ~(0x7 << 12);
	pStruct->TIMx->CCMR1 |= (mode << 12);
	pStruct->TIMx->CCER |= 0x0010; //enable ch1 capture
}

void adv_timer::setCCR2(uint16_t ccr2) {
	pStruct->TIMx->CCR2 = ccr2;
}


void adv_timer::OC3_Enable(uint8_t mode) {
	pStruct->TIMx->CCMR2 &= ~(0x7 << 4);
	pStruct->TIMx->CCMR2 |= (mode << 4);
	pStruct->TIMx->CCER |= 0x0100; //enable ch1 capture
}

void adv_timer::setCCR3(uint16_t ccr3) {
	pStruct->TIMx->CCR3 = ccr3;
}


void adv_timer::OC4_Enable(uint8_t mode) {
	pStruct->TIMx->CCMR2 &= ~(0x7 << 12);
	pStruct->TIMx->CCMR2 |= (mode << 12);
	pStruct->TIMx->CCER |= 0x1000; //enable ch1 capture
}

void adv_timer::setCCR4(uint16_t ccr4) {
	pStruct->TIMx->CCR4 = ccr4;
}


void adv_timer::Counter_Enable() {
	pStruct->TIMx->CR1 |= 0x0001;
}

void adv_timer::Generate_Update() {
	pStruct->TIMx->EGR |= 0x0001;
}
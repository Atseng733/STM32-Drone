#include <adv_timer.h>

void adv_timer::Init(GENERAL_TIM_Typedef* timx, uint16_t arr_value) {
	TIMx = timx;

	if(TIMx == TIM2) {
		TIM2_CLK_EN;
	}
	else if(TIMx == TIM3) {
		TIM3_CLK_EN;
	}
	else if(TIMx == TIM4) {
		TIM4_CLK_EN;
	}
	else if(TIMx == TIM5) {
		TIM5_CLK_EN;
	}

	TIMx->PSC = (F_CPU/1000000) - 1; //prescaler set so one tick is 1us
	TIMx->ARR = arr_value;
}

void adv_timer::Configure(Adv_Timer_Config &config) {
	TIMx->CR1 = config.CR1;
	TIMx->DIER = config.DIER;
}

void adv_timer::OC1_Enable(uint8_t mode) {
	TIMx->CCMR1 &= ~(0x7 << 4);
	TIMx->CCMR1 |= (mode << 4);
	TIMx->CCER |= 0x0001; //enable ch1 capture
}

void adv_timer::setCCR1(uint16_t ccr1) {
	TIMx->CCR1 = ccr1;
}

void adv_timer::OC2_Enable(uint8_t mode) {
	TIMx->CCMR1 &= ~(0x7 << 12);
	TIMx->CCMR1 |= (mode << 12);
	TIMx->CCER |= 0x0010; //enable ch1 capture
}

void adv_timer::setCCR2(uint16_t ccr2) {
	TIMx->CCR2 = ccr2;
}


void adv_timer::OC3_Enable(uint8_t mode) {
	TIMx->CCMR2 &= ~(0x7 << 4);
	TIMx->CCMR2 |= (mode << 4);
	TIMx->CCER |= 0x0100; //enable ch1 capture
}

void adv_timer::setCCR3(uint16_t ccr3) {
	TIMx->CCR3 = ccr3;
}


void adv_timer::OC4_Enable(uint8_t mode) {
	TIMx->CCMR2 &= ~(0x7 << 12);
	TIMx->CCMR2 |= (mode << 12);
	TIMx->CCER |= 0x1000; //enable ch1 capture
}

void adv_timer::setCCR4(uint16_t ccr4) {
	TIMx->CCR4 = ccr4;
}


void adv_timer::Counter_Enable() {
	TIMx->CR1 |= 0x0001;
}

void adv_timer::Generate_Update() {
	TIMx->EGR |= 0x0001;
}
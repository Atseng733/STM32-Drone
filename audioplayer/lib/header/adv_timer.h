#ifndef ADV_TIMER_H
#define ADV_TIMER_H
#include <rcc.h>
#include <f1_gpio.h>

#define OCM_Frozen 0x0
#define OCM_Active 0x1
#define OCM_Inactive 0x2
#define OCM_Toggle 0x3
#define OCM_ForceInactive 0x4
#define OCM_ForceActive 0x5
#define OCM_PWM1 0x6
#define OCM_PWM2 0x7

typedef struct {
	uint16_t CR1;
	uint16_t DIER;
} Adv_Timer_Config;

class adv_timer {
	private:
		GENERAL_TIM_Typedef* TIMx;
	public:
		void Init(GENERAL_TIM_Typedef* timx, uint16_t arr_value);
		void Configure(Adv_Timer_Config &config);
		void OC1_Enable(uint8_t mode);
		void setCCR1(uint16_t ccr1);
		void OC2_Enable(uint8_t mode);
		void setCCR2(uint16_t ccr2);
		void OC3_Enable(uint8_t mode);
		void setCCR3(uint16_t ccr3);
		void OC4_Enable(uint8_t mode);
		void setCCR4(uint16_t ccr4);
		void Counter_Enable();
		void Generate_Update();
};


#endif
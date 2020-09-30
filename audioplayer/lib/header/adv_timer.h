#ifndef ADV_TIMER_H
#define ADV_TIMER_H
#include <boards.h>
#include <usart.h>

#define OCM_Frozen 0x0
#define OCM_Active 0x1
#define OCM_Inactive 0x2
#define OCM_Toggle 0x3
#define OCM_ForceInactive 0x4
#define OCM_ForceActive 0x5
#define OCM_PWM1 0x6
#define OCM_PWM2 0x7

#define MMS_RESET 0x0
#define MMS_ENABLE 0x1
#define MMS_UPDATE 0x2
#define MMS_COMPARE_PULSE 0x3
#define MMS_COMPARE_OC1 0x4
#define MMS_COMPARE_OC2 0x5
#define MMS_COMPARE_OC3 0x6
#define MMS_COMPARE_OC4 0x7

typedef struct {
	GENERAL_TIM_Typedef* TIMx;
	uint16_t CR1;
	uint16_t CR2;
	uint16_t DIER;
	uint16_t PSC;
	uint32_t ARR;
} Adv_Timer_Struct;

class adv_timer {
	private:
		Adv_Timer_Struct* pStruct;
	public:
		void Init(Adv_Timer_Struct* pconfig);
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
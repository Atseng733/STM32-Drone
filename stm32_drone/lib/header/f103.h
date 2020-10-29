#ifndef F103_H
#define F103_H
#include <stdint.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define APB1_MAX_FREQ 36000000
#define APB2_MAX_FREQ 72000000
#define AHB_MAX_FREQ 72000000

#define F_HSE 16000000UL
#define F_HSI 8000000UL

typedef struct {
	volatile uint32_t CR1;       //0x00
	volatile uint32_t CR2;
				uint32_t RESERVED1;
	volatile uint32_t DIER;
	volatile uint32_t SR;        //0x10
	volatile uint32_t EGR;
				uint32_t RESERVED2;
				uint32_t RESERVED3;
				uint32_t RESERVED4; //0x20
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;

} BASIC_TIM_Typedef;

#define GEN_TIM_CR1_OPM (1 << 3)
#define GEN_TIM_CR1_URS (1 << 2)
#define GEN_TIM_CR1_UDIS (1 << 1)
#define GEN_TIM_CR1_CEN (1 << 0)

#define GEN_TIM_DIER_TDE (1 << 14)
#define GEN_TIM_DIER_CC4DE (1 << 12)
#define GEN_TIM_DIER_CC3DE (1 << 11)
#define GEN_TIM_DIER_CC2DE (1 << 10)
#define GEN_TIM_DIER_CC1DE (1 << 9)
#define GEN_TIM_DIER_UDE (1 << 8)
#define GEN_TIM_DIER_TIE (1 << 6)
#define GEN_TIM_DIER_CC4IE (1 << 4)
#define GEN_TIM_DIER_CC3IE (1 << 3)
#define GEN_TIM_DIER_CC2IE (1 << 2)
#define GEN_TIM_DIER_CC1IE (1 << 1)
#define GEN_TIM_DIER_UIE (1 << 0)

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
				uint32_t RESERVED1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
				uint32_t RESERVED2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
} GENERAL_TIM_Typedef;

#define I2C_CR1_ACK (1 << 10)
#define I2C_CR1_STOP (1 << 9)
#define I2C_CR1_START (1 << 8)
#define I2C_CR1_PE (1 << 0)

#define I2C_CR2_ITBUFEN (1 << 10)
#define I2C_CR2_ITEVTEN (1 << 9)
#define I2C_CR2_ITERREN (1 << 8)
#define I2C_CR2_FREQ (1 << 0)

#define I2C_SR1_TXE (1 << 7)
#define I2C_SR1_RXNE (1 << 6)
#define I2C_SR1_STOPF (1 << 4)
#define I2C_SR1_BTF (1 << 2)
#define I2C_SR1_ADDR (1 << 1)
#define I2C_SR1_SB (1 << 0)

#define I2C_SR2_BUSY (1 << 1)
#define I2C_SR2_MSL (1 << 0)

#define I2C_CCR_F_S (1 << 15)
#define I2C_CCR_DUTY (1 << 14)
#define I2C_CCR_CCR (1 << 0)

typedef struct {
	volatile uint32_t CR1;  //0x00
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
} I2C_Typedef;

#define USART_SR_TXE (1 << 7)
#define USART_SR_TC (1 << 6)
#define USART_SR_RXNE (1 << 5)
#define USART_SR_IDLE (1 << 4)
#define USART_SR_ORE (1 << 3)
#define USART_SR_NE (1 << 2)
#define USART_SR_FE (1 << 1)
#define USART_SR_PE (1 << 0)

#define USART_CR1_UE (1 << 13)
#define USART_CR1_PEIE (1 << 8)
#define USART_CR1_TXEIE (1 << 7)
#define USART_CR1_TCIE (1 << 6)
#define USART_CR1_RXNEIE (1 << 5)
#define USART_CR1_IDLEIE (1 << 4)
#define USART_CR1_TE (1 << 3)
#define USART_CR1_RE (1 << 2)

typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_Typedef;

typedef struct {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
				uint32_t RESERVED1;
	volatile uint32_t MAPR2;
} AFIO_Typedef;

typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} EXTI_Typedef;

typedef struct 
{
	volatile uint32_t CRL;   //0x00
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;    //0x20
} GPIO_Typedef;

typedef struct {
	volatile uint32_t ISR;
	volatile uint32_t IFCR;
	volatile uint32_t CCR1;
	volatile uint32_t CNDTR1;
	volatile uint32_t CPAR1;
	volatile uint32_t CMAR1;
				uint32_t RESERVED1;
	volatile uint32_t CCR2;
	volatile uint32_t CNDTR2;
	volatile uint32_t CPAR2;
	volatile uint32_t CMAR2;
				uint32_t RESERVED2;
	volatile uint32_t CCR3;
	volatile uint32_t CNDTR3;
	volatile uint32_t CPAR3;
	volatile uint32_t CMAR3;
				uint32_t RESERVED3;
	volatile uint32_t CCR4;
	volatile uint32_t CNDTR4;
	volatile uint32_t CPAR4;
	volatile uint32_t CMAR4;
				uint32_t RESERVED4;
	volatile uint32_t CCR5;
	volatile uint32_t CNDTR5;
	volatile uint32_t CPAR5;
	volatile uint32_t CMAR5;
				uint32_t RESERVED5;
	volatile uint32_t CCR6;
	volatile uint32_t CNDTR6;
	volatile uint32_t CPAR6;
	volatile uint32_t CMAR6;
				uint32_t RESERVED6;
	volatile uint32_t CCR7;
	volatile uint32_t CNDTR7;
	volatile uint32_t CPAR7;
	volatile uint32_t CMAR7;
				uint32_t RESERVED7;
} DMA_Typedef;

#define RCC_APB2ENR RCC->APB2ENR
#define RCC_APB1ENR RCC->APB1ENR

#define RCC_GPIOEN_REGISTER RCC_APB2ENR
	#define RCC_AFIO  (1 << 0)
	#define RCC_GPIOA (1 << 2)
	#define RCC_GPIOB (1 << 3)
	#define RCC_GPIOC (1 << 4)
	#define RCC_GPIOD (1 << 5)
	#define RCC_GPIOE (1 << 6)
	#define RCC_GPIOF (1 << 7)
	#define RCC_GPIOG (1 << 8)

#define RCC_CR_PLLRDY (1 << 25)
#define RCC_CR_PLLON (1 << 24)
#define RCC_CR_HSERDY (1 << 17)
#define RCC_CR_HSEON (1 << 16)
#define RCC_CR_HSIRDY (1 << 1)
#define RCC_CR_HSION (1 << 0)

#define RCC_CFGR_MCO (1 << 24)
#define RCC_CFGR_USBPRE (1 << 22)
#define RCC_CFGR_PLLMUL 18
#define RCC_CFGR_PLLXTPRE (1 << 17)
#define RCC_CFGR_PLLSRC (1 << 16)
#define RCC_CFGR_ADCPRE 14
#define RCC_CFGR_PPRE2 11
#define RCC_CFGR_PPRE1 8
#define RCC_CFGR_HPRE 4
#define RCC_CFGR_SWS 2
#define RCC_CFGR_SW 0

#define RCC_APB2ENR_USART1EN (1 << 14)


#define RCC_APB1ENR_I2C2EN (1 << 22)
#define RCC_APB1ENR_I2C1EN (1 << 21)
#define RCC_APB1ENR_UART5EN (1 << 20)
#define RCC_APB1ENR_UART4EN (1 << 19)
#define RCC_APB1ENR_USART3EN (1 << 18)
#define RCC_APB1ENR_USART2EN (1 << 17)
#define RCC_APB1ENR_TIM7EN (1 << 5)
#define RCC_APB1ENR_TIM6EN (1 << 4)
#define RCC_APB1ENR_TIM5EN (1 << 3)
#define RCC_APB1ENR_TIM4EN (1 << 2)
#define RCC_APB1ENR_TIM3EN (1 << 1)
#define RCC_APB1ENR_TIM2EN (1 << 0)

#define USART1_CLK_EN (RCC->APB2ENR |= RCC_APB2ENR_USART1EN)

#define USART2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_USART2EN)
#define I2C2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_I2C2EN)
#define I2C1_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN)
#define TIM7_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM7EN)
#define TIM6_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM6EN)
#define TIM5_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM5EN)
#define TIM4_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM4EN)
#define TIM3_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM3EN)
#define TIM2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM2EN)
	
typedef struct
{
	volatile uint32_t CR;        //0x00
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;  //0x10
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;  
   volatile uint32_t BDCR;      
   volatile uint32_t CSR;
} RCC_Typedef;

typedef struct {
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
				uint32_t RESERVED1;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
} FLASH_Typedef;

#define SysTick_CTRL_CLKSOURCE (1 << 2)
#define SysTick_CTRL_TICKINT (1 << 1)
#define SysTick_CTRL_ENABLE (1 << 0)

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
}	SysTick_Typedef;

typedef struct {
	volatile uint32_t ISER0; //0x0100
	volatile uint32_t ISER1;
	volatile uint32_t ISER2;
	volatile uint32_t ISER3;
	volatile uint32_t ISER4; //0x0110
	volatile uint32_t ISER5;
	volatile uint32_t ISER6;
	volatile uint32_t ISER7;
} NVIC_ISER_Typedef;

typedef struct {
	volatile uint32_t ICER0; //0x0180
	volatile uint32_t ICER1;
	volatile uint32_t ICER2;
	volatile uint32_t ICER3;
	volatile uint32_t ICER4; //0x0190
	volatile uint32_t ICER5;
	volatile uint32_t ICER6;
	volatile uint32_t ICER7;
	volatile uint32_t ISPR0; //0x0200
	volatile uint32_t ISPR1;
	volatile uint32_t ISPR2;
	volatile uint32_t ISPR3;
	volatile uint32_t ISPR4; //0x0210
	volatile uint32_t ISPR5;
	volatile uint32_t ISPR6;
	volatile uint32_t ISPR7;
} NVIC_ICER_Typedef;

typedef struct {
	volatile uint32_t ICPR0; //0x0280
	volatile uint32_t ICPR1;
	volatile uint32_t ICPR2;
	volatile uint32_t ICPR3;
	volatile uint32_t ICPR4; //0x0290
	volatile uint32_t ICPR5;
	volatile uint32_t ICPR6;
	volatile uint32_t ICPR7;
	volatile uint32_t IABR0; //0x0300
	volatile uint32_t IABR1;
	volatile uint32_t IABR2;
	volatile uint32_t IABR3;
	volatile uint32_t IABR4; //0x0310
	volatile uint32_t IABR5;
	volatile uint32_t IABR6;
	volatile uint32_t IABR7;
} NVIC_ICPR_Typedef;

typedef struct {
	volatile uint32_t IPR0; //0x0400
	volatile uint32_t IPR1;
	volatile uint32_t IPR2;
	volatile uint32_t IPR3;
	volatile uint32_t IPR4; //0x0410
	volatile uint32_t IPR5;
	volatile uint32_t IPR6;
	volatile uint32_t IPR7;
	volatile uint32_t IPR8; //0x0420
	volatile uint32_t IPR9;
	volatile uint32_t IPR10;
	volatile uint32_t IPR11;
	volatile uint32_t IPR12; //0x0430
	volatile uint32_t IPR13;
	volatile uint32_t IPR14;
	volatile uint32_t IPR15;
	volatile uint32_t IPR16; //0x0440
	volatile uint32_t IPR17;
	volatile uint32_t IPR18;
	volatile uint32_t IPR19;
	volatile uint32_t IPR20; //0x0450
	volatile uint32_t IPR21;
	volatile uint32_t IPR22;
	volatile uint32_t IPR23;
	volatile uint32_t IPR24; //0x0460
	volatile uint32_t IPR25;
	volatile uint32_t IPR26;
	volatile uint32_t IPR27;
	volatile uint32_t IPR28; //0x0470
	volatile uint32_t IPR29;
	volatile uint32_t IPR30;
	volatile uint32_t IPR31;
	volatile uint32_t IPR32; //0x0480
	volatile uint32_t IPR33;
	volatile uint32_t IPR34;
	volatile uint32_t IPR35;
	volatile uint32_t IPR36; //0x0490
	volatile uint32_t IPR37;
	volatile uint32_t IPR38;
	volatile uint32_t IPR39;
	volatile uint32_t IPR40; //0x04A0
	volatile uint32_t IPR41;
	volatile uint32_t IPR42;
	volatile uint32_t IPR43;
	volatile uint32_t IPR44; //0x04B0
	volatile uint32_t IPR45;
	volatile uint32_t IPR46;
	volatile uint32_t IPR47;
	volatile uint32_t IPR48; //0x04C0
	volatile uint32_t IPR49;
	volatile uint32_t IPR50;
	volatile uint32_t IPR51;
	volatile uint32_t IPR52; //0x04D0
	volatile uint32_t IPR53;
	volatile uint32_t IPR54;
	volatile uint32_t IPR55;
	volatile uint32_t IPR56; //0x04E0
	volatile uint32_t IPR57;
	volatile uint32_t IPR58;
	volatile uint32_t IPR59;
} NVIC_IPR_Typedef;

#define NVIC_STIR (*((uint32_t*)(0xED000E00)))

#define PERIPH_BASE ((uint32_t)(0x40000000))
	#define APB1PERIPH_BASE (PERIPH_BASE + 0x0000)
		#define TIM2_BASE (APB1PERIPH_BASE + 0x0000)
		#define TIM3_BASE (APB1PERIPH_BASE + 0x0400)
		#define TIM4_BASE (APB1PERIPH_BASE + 0x0800)
		#define TIM5_BASE (APB1PERIPH_BASE + 0x0C00)
		#define TIM6_BASE (APB1PERIPH_BASE + 0x1000)
		#define TIM7_BASE (APB1PERIPH_BASE + 0x1400)
		#define USART2_BASE (APB1PERIPH_BASE + 0x4400)
		#define USART3_BASE (APB1PERIPH_BASE + 0x4800)
		#define I2C1_BASE (APB1PERIPH_BASE + 0x5400)
		#define I2C2_BASE (APB1PERIPH_BASE + 0x5800)
	#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
		#define AFIO_BASE (APB2PERIPH_BASE + 0x0000)
		#define EXTI_BASE (APB2PERIPH_BASE + 0x0400)
		#define GPIOA_BASE (APB2PERIPH_BASE + 0x0800)
		#define GPIOB_BASE (APB2PERIPH_BASE + 0x0C00)
		#define GPIOC_BASE (APB2PERIPH_BASE + 0x1000)
		#define GPIOD_BASE (APB2PERIPH_BASE + 0x1400)
		#define USART1_BASE (APB2PERIPH_BASE + 0x3800)
	#define AHBPERIPH_BASE (PERIPH_BASE + 0x18000)
		#define DMA1_BASE	(AHBPERIPH_BASE + 0x8000)
		#define DMA2_BASE (AHBPERIPH_BASE + 0x8400)
		#define RCC_BASE (AHBPERIPH_BASE + 0x9000)
		#define FLASH_BASE (AHBPERIPH_BASE + 0xA000)

#define PRIV_PERIPH_BASE ((uint32_t)(0xE000E000))
	#define SysTick_BASE (PRIV_PERIPH_BASE + 0x0010)
	#define NVIC_ISER_BASE (PRIV_PERIPH_BASE + 0x0100)
	#define NVIC_ICER_BASE (PRIV_PERIPH_BASE + 0x0180)
	#define NVIC_ICPR_BASE (PRIV_PERIPH_BASE + 0x0280)
	#define NVIC_IPR_BASE  (PRIV_PERIPH_BASE + 0x0400)

#define SysTick ((SysTick_Typedef*)(SysTick_BASE))
#define NVIC_ISER ((NVIC_ISER_Typedef*)(NVIC_ISER_BASE))
#define NVIC_ICER ((NVIC_ICER_Typedef*)(NVIC_ICER_BASE))
#define NVIC_ICPR ((NVIC_ICPR_Typedef*)(NVIC_ICPR_BASE))
#define NVIC_IPR  ((NVIC_IPR_Typedef*)(NVIC_IPR_BASE))

#define TIM2 ((GENERAL_TIM_Typedef*)(TIM2_BASE))
#define TIM3 ((GENERAL_TIM_Typedef*)(TIM3_BASE))
#define TIM4 ((GENERAL_TIM_Typedef*)(TIM4_BASE))
#define TIM5 ((GENERAL_TIM_Typedef*)(TIM5_BASE))
#define TIM6 ((BASIC_TIM_Typedef*)(TIM6_BASE))
#define TIM7 ((BASIC_TIM_Typedef*)(TIM7_BASE))
#define I2C1 ((I2C_Typedef*)(I2C1_BASE))
#define I2C2 ((I2C_Typedef*)(I2C2_BASE))

#define USART1 ((USART_Typedef*)(USART1_BASE))
#define USART2 ((USART_Typedef*)(USART2_BASE))
#define USART3 ((USART_Typedef*)(USART3_BASE))

#define AFIO ((AFIO_Typedef*)(AFIO_BASE))
#define EXTI ((EXTI_Typedef*)(EXTI_BASE))
#define GPIOA ((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOB ((GPIO_Typedef*)(GPIOB_BASE))
#define GPIOC ((GPIO_Typedef*)(GPIOC_BASE))
#define GPIOD ((GPIO_Typedef*)(GPIOD_BASE))
#define RCC ((RCC_Typedef*)(RCC_BASE))
#define FLASH ((FLASH_Typedef*)(FLASH_BASE))

#endif
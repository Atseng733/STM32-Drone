#ifndef F407_H
#define F407_H
#include <stdint.h>

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
	volatile uint32_t FLTR;
} I2C_Typedef;

#define USART_TXE (1 << 7)

typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_Typedef;

typedef struct 
{
	volatile uint32_t MODER;   //0x00
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;     //0x10
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;    //0x20
	volatile uint32_t AFRH;
} GPIO_Typedef;

#define RCC_USART1EN_REGISTER RCC->APB2ENR
	#define RCC_USART1EN (1 << 4)

#define RCC_GPIOEN_REGISTER RCC->AHB1ENR
	#define RCC_GPIOA (1 << 0)
	#define RCC_GPIOB (1 << 1)
	#define RCC_GPIOC (1 << 2)
	#define RCC_GPIOD (1 << 3)
#define RCC_TIM6EN_REGISTER RCC->APB1ENR
#define RCC_TIM6EN (1 << 4)

typedef struct
{
	volatile uint32_t CR;        //0x00
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;  //0x10
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	         uint32_t RESERVED1;
	volatile uint32_t APB1RSTR;  //0x20
	volatile uint32_t APB2RSTR;
             uint32_t RESERVED2;
	         uint32_t RESERVED3;
	volatile uint32_t AHB1ENR;   //0x30
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	         uint32_t RESERVED4;
	volatile uint32_t APB1ENR;   //0x40
	volatile uint32_t APB2ENR;
	         uint32_t RESERVED5;
	         uint32_t RESERVED6;
	volatile uint32_t AHB1LPENR; //0x50
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	         uint32_t RESERVED7;
	volatile uint32_t APB1LPENR; //0x60
	volatile uint32_t APB2LPENR;
            uint32_t RESERVED8;
            uint32_t RESERVED9;
   volatile uint32_t BDCR;      //0x70
   volatile uint32_t CSR;
            uint32_t RESERVED10;
            uint32_t RESERVED11;
   volatile uint32_t SSCGR;     //0x80
   volatile uint32_t PLLI2SCFGR;
} RCC_Typedef;

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

#define NVIC_STIR *((uint32_t*)(0xED000E00))

#define PERIPH_BASE ((uint32_t)(0x40000000))
	#define APB1PERIPH_BASE (PERIPH_BASE + 0x0000)
		#define TIM6_BASE (APB1PERIPH_BASE + 0x1000)
		#define TIM7_BASE (APB1PERIPH_BASE + 0x1400)
		#define I2C1_BASE (APB1PERIPH_BASE + 0x5400)
	#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
		#define USART1_BASE (APB2PERIPH_BASE + 0x1000)
	#define AHB1PERIPH_BASE (PERIPH_BASE + 0x20000)
		#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000)
		#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400)
		#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800)
		#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00)
		#define RCC_BASE (AHB1PERIPH_BASE + 0x3800)

#define PRIV_PERIPH_BASE ((uint32_t)(0xE000E000))
	#define NVIC_ISER_BASE (PRIV_PERIPH_BASE + 0x0100)
	#define NVIC_ICER_BASE (PRIV_PERIPH_BASE + 0x0180)
	#define NVIC_ICPR_BASE (PRIV_PERIPH_BASE + 0x0280)
	#define NVIC_IPR_BASE  (PRIV_PERIPH_BASE + 0x0400)

#define NVIC_ISER ((NVIC_ISER_Typedef*)(NVIC_ISER_BASE))
#define NVIC_ICER ((NVIC_ICER_Typedef*)(NVIC_ICER_BASE))
#define NVIC_ICPR ((NVIC_ICPR_Typedef*)(NVIC_ICPR_BASE))
#define NVIC_IPR  ((NVIC_IPR_Typedef*)(NVIC_IPR_BASE))

#define TIM6 ((BASIC_TIM_Typedef*)(TIM6_BASE))
#define TIM7 ((BASIC_TIM_Typedef*)(TIM7_BASE))
#define I2C1 ((I2C_Typedef*)(I2C1_BASE))

#define USART1 ((USART_Typedef*)(USART1_BASE))

#define GPIOA ((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOB ((GPIO_Typedef*)(GPIOB_BASE))
#define GPIOC ((GPIO_Typedef*)(GPIOC_BASE))
#define GPIOD ((GPIO_Typedef*)(GPIOD_BASE))
#define RCC ((RCC_Typedef*)(RCC_BASE))

#endif
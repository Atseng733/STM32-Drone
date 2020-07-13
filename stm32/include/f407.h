#ifndef F407_H
#define F407_H
#include <stdint.h>


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

#define PERIPH_BASE ((uint32_t)(0x40000000))

	#define AHB1PERIPH_BASE (PERIPH_BASE + 0x20000)
		#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000)
		#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400)
		#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800)
		#define RCC_BASE (AHB1PERIPH_BASE + 0x3800)


#define GPIOA ((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOB ((GPIO_Typedef*)(GPIOB_BASE))
#define GPIOC ((GPIO_Typedef*)(GPIOC_BASE))
#define RCC ((RCC_Typedef*)(RCC_BASE))

#endif
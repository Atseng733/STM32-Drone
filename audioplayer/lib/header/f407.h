#ifndef F407_H
#define F407_H
#include <stdint.h>


#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define F_HSE 8000000UL
#define F_HSI 16000000UL

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

#define GEN_TIM_CR1_CKD 8
#define GEN_TIM_CR1_ARPE (1 << 7)
#define GEN_TIM_CR1_CMS 5
#define GEN_TIM_CR1_DIR (1 << 4)
#define GEN_TIM_CR1_OPM (1 << 3)
#define GEN_TIM_CR1_URS (1 << 2)
#define GEN_TIM_CR1_UDIS (1 << 1)
#define GEN_TIM_CR1_CEN (1 << 0)

#define GEN_TIM_CR2_TI1S (1 << 7)
#define GEN_TIM_CR2_MMS 4
#define GEN_TIM_CR2_CCDS (1 << 3)

#define GEN_TIM_DIER_UIE (1 << 0)

#define GEN_TIM_SR_UIF (1 << 0)

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
	volatile uint32_t TIM2_OR;
	volatile uint32_t TIM5_OR;
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
	volatile uint32_t FLTR;
} I2C_Typedef;

#define DAC_CR_EN1 (1 << 0)
#define DAC_CR_BOFF1 (1 << 1)
#define DAC_CR_TEN1 (1 << 2)
#define DAC_CR_TSEL1 3
#define DAC_CR_WAVE1 6
#define DAC_CR_MAMP 8
#define DAC_CR_DMAEN1 12
#define DAC_CR_DMAUDRIE 13

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t SWTRIGR;
	volatile uint32_t DHR12R1;
	volatile uint32_t DHR12L1;
	volatile uint32_t DHR8R1;
	volatile uint32_t DHR12R2;
	volatile uint32_t DHR12L2;
	volatile uint32_t DHR8R2;
	volatile uint32_t DHR12RD;
	volatile uint32_t DHR12LD;
	volatile uint32_t DHR8RD;
	volatile uint32_t DOR1;
	volatile uint32_t DOR2;
	volatile uint32_t SR;
} DAC_Typedef;

#define SPI_CR1_BIDIMODE (1 << 15)
#define SPI_CR1_BIDIOE (1 << 14)
#define SPI_CR1_CRCEN (1 << 13)
#define SPI_CR1_CRCNEXT (1 << 12)
#define SPI_CR1_DFF (1 << 11)
#define SPI_CR1_RXONLY (1 << 10)
#define SPI_CR1_SSM (1 << 9)
#define SPI_CR1_SSI (1 << 8)
#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_SPE (1 << 6)
#define SPI_CR1_BR 3
#define SPI_CR1_MSTR (1 << 2)
#define SPI_CR1_CPOL (1 << 1)
#define SPI_CR1_CPHA (1 << 0)

#define SPI_CR2_TXEIE (1 << 7)
#define SPI_CR2_RXNEIE (1 << 6)
#define SPI_CR2_ERRIE (1 << 5)
#define SPI_CR2_FRF (1 << 4)
#define SPI_CR2_SSOE (1 << 2)
#define SPI_CR2_TXDMAEN (1 << 1)
#define SPI_CR2_RXDMAEN (1 << 0)

#define SPI_SR_FRE (1 << 8)
#define SPI_SR_BSY (1 << 7)
#define SPI_SR_OVR (1 << 6)
#define SPI_SR_MODF (1 << 5)
#define SPI_SR_CRCERR (1 << 4)
#define SPI_SR_UDR (1 << 3)
#define SPI_SR_CHSIDE (1 << 2)
#define SPI_SR_TXE (1 << 1)
#define SPI_SR_RXNE (1 << 0)

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
} SPI_Typedef;

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

#define SDIO_POWER_PWRCTRL 0

#define SDIO_CLKCR_WIDBUS 11
#define SDIO_CLKCR_BYPASS (1 << 10)
#define SDIO_CLKCR_PWRSAV (1 << 9)
#define SDIO_CLKCR_CLKEN (1 << 8);
#define SDIO_CLKCR_CLKDIV 0

#define SDIO_CMD_CPSMEN (1 << 10)
#define SDIO_CMD_WAITPEND (1 << 9)
#define SDIO_CMD_WAITINT (1 << 8)
#define SDIO_CMD_WAITRESP 6
#define SDIO_CMD_INDEX 0

#define SDIO_STA_SDIOIT (1 << 22)
#define SDIO_STA_RXDAVL (1 << 21)
#define SDIO_STA_TXDAVL (1 << 20)
#define SDIO_STA_RXFIFOE (1 << 19)
#define SDIO_STA_TXFIFOE (1 << 18)
#define SDIO_STA_RXFIFOF (1 << 17)
#define SDIO_STA_TXFIFOF (1 << 16)
#define SDIO_STA_RXFIFOHF (1 << 15)
#define SDIO_STA_TXFIFOHE (1 << 14)
#define SDIO_STA_RXACT (1 << 13)
#define SDIO_STA_TXACT (1 << 12)
#define SDIO_STA_CMDACT (1 << 11)
#define SDIO_STA_DBCKEND (1 << 10)
#define SDIO_STA_STBITERR (1 << 9)
#define SDIO_STA_DATAEND (1 << 8)
#define SDIO_STA_CMDSENT (1 << 7)
#define SDIO_STA_CMDREND (1 << 6)
#define SDIO_STA_RXOVERR (1 << 5)
#define SDIO_STA_TXUNDERR (1 << 4)
#define SDIO_STA_DTIMEOUT (1 << 3)
#define SDIO_STA_CTIMEOUT (1 << 2)
#define SDIO_STA_DCRCFAIL (1 << 1)
#define SDIO_STA_CCRCFAIL (1 << 0)

#define SDIO_ICR_CEATAENDC (1 << 23)
#define SDIO_ICR_SDIOITC (1 << 22)
#define SDIO_ICR_DBCKENDC (1 << 10)
#define SDIO_ICR_STBITERRC (1 << 9)
#define SDIO_ICR_DATAENDC (1 << 8)
#define SDIO_ICR_CMDSENTC (1 << 7)
#define SDIO_ICR_CMDRENDC (1 << 6)
#define SDIO_ICR_RXOVERRC (1 << 5)
#define SDIO_ICR_TXUNDERRC (1 << 4)
#define SDIO_ICR_DTIMEOUTC (1 << 3)
#define SDIO_ICR_CTIMEOUTC (1 << 2)
#define SDIO_ICR_DCRCFAILC (1 << 1)
#define SDIO_ICR_CCRCFAILC (1 << 0)

typedef struct {
	volatile uint32_t POWER;
	volatile uint32_t CLKCR;
	volatile uint32_t ARG;
	volatile uint32_t CMD;
	volatile uint32_t RESPCMD;
	volatile uint32_t RESP1;
	volatile uint32_t RESP2;
	volatile uint32_t RESP3;
	volatile uint32_t RESP4;
	volatile uint32_t DTIMER;
	volatile uint32_t DLEN;
	volatile uint32_t DCTRL;
	volatile uint32_t DCOUNT;
	volatile uint32_t STA;
	volatile uint32_t ICR;
	volatile uint32_t MASK; //0x3C
				uint32_t RESERVED1;
				uint32_t RESERVED2;
	volatile uint32_t FIFOCNT; //0x48
				uint32_t RESERVED3;
				uint32_t RESERVED4;
				uint32_t RESERVED5;
				uint32_t RESERVED6;
				uint32_t RESERVED7;
				uint32_t RESERVED8;
				uint32_t RESERVED9;
				uint32_t RESERVED10;
				uint32_t RESERVED11;
				uint32_t RESERVED12;
				uint32_t RESERVED13;
				uint32_t RESERVED14;
				uint32_t RESERVED15;
	volatile uint32_t FIFO;
} SDIO_Typedef;

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


typedef struct {
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
} FLASH_Typedef;

#define RCC_USART1EN_REGISTER RCC->APB2ENR
	#define RCC_USART1EN (1 << 4)

#define RCC_GPIOEN_REGISTER RCC->AHB1ENR
	#define RCC_GPIOA (1 << 0)
	#define RCC_GPIOB (1 << 1)
	#define RCC_GPIOC (1 << 2)
	#define RCC_GPIOD (1 << 3)
#define RCC_TIM6EN_REGISTER RCC->APB1ENR
#define RCC_TIM6EN (1 << 4)


#define RCC_CR_PLLRDY (1 << 25)
#define RCC_CR_PLLON (1 << 24)
#define RCC_CR_HSERDY (1 << 17)
#define RCC_CR_HSEON (1 << 16)
#define RCC_CR_HSIRDY (1 << 1)
#define RCC_CR_HSION (1 << 0)

#define RCC_PLLCFGR_PLLSRC (1 << 22)
#define RCC_PLLCFGR_PLLP (16)
#define RCC_PLLCFGR_PLLN (6)
#define RCC_PLLCFGR_PLLM (0)

#define RCC_CFGR_MCO2 (1 << 30)
#define RCC_CFGR_MCO2_SYSCLK 0x00
#define RCC_CFGR_MCO2_PLLI2S 0x01
#define RCC_CFGR_MCO2_HSE 0x10
#define RCC_CFGR_MCO2_PLL 0x11
#define RCC_CFGR_MCO1 (1 << 21)
#define RCC_CFGR_MCO1_HSI 0x00
#define RCC_CFGR_MCO1_LSE 0x01
#define RCC_CFGR_MCO1_HSE 0x10
#define RCC_CFGR_MCO1_PLL 0x11

#define RCC_APB2ENR_USART1EN (1 << 4)
#define RCC_APB2ENR_USART6EN (1 << 5)


#define RCC_APB1ENR_I2C2EN (1 << 22)
#define RCC_APB1ENR_I2C1EN (1 << 21)
#define RCC_APB1ENR_DACEN (1 << 29)

#define RCC_APB1ENR_UART5EN (1 << 20)
#define RCC_APB1ENR_UART4EN (1 << 19)
#define RCC_APB1ENR_USART3EN (1 << 18)
#define RCC_APB1ENR_USART2EN (1 << 17)
#define RCC_APB1ENR_SPI2EN (1 << 14)
#define RCC_APB1ENR_TIM7EN (1 << 5)
#define RCC_APB1ENR_TIM6EN (1 << 4)
#define RCC_APB1ENR_TIM5EN (1 << 3)
#define RCC_APB1ENR_TIM4EN (1 << 2)
#define RCC_APB1ENR_TIM3EN (1 << 1)
#define RCC_APB1ENR_TIM2EN (1 << 0)

#define RCC_APB2ENR_SDIOEN (1 << 11)

#define GPIOA_CLK_EN (RCC_GPIOEN_REGISTER |= RCC_GPIOA)
#define GPIOB_CLK_EN (RCC_GPIOEN_REGISTER |= RCC_GPIOB)
#define GPIOC_CLK_EN (RCC_GPIOEN_REGISTER |= RCC_GPIOC)
#define GPIOD_CLK_EN (RCC_GPIOEN_REGISTER |= RCC_GPIOD)
#define USART1_CLK_EN (RCC->APB2ENR |= RCC_APB2ENR_USART1EN)
#define USART2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_USART2EN)
#define SPI2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_SPI2EN)
#define I2C2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_I2C2EN)
#define I2C1_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN)
#define DAC_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_DACEN)
#define TIM7_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM7EN)
#define TIM6_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM6EN)
#define TIM5_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM5EN)
#define TIM4_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM4EN)
#define TIM3_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM3EN)
#define TIM2_CLK_EN (RCC->APB1ENR |= RCC_APB1ENR_TIM2EN)

#define SDIO_CLK_EN (RCC->APB2ENR |= RCC_APB2ENR_SDIOEN)

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

#define SysTick_CTRL_ENABLE (1 << 0)
#define SysTick_CTRL_TICKINT (1 << 1)
#define SysTick_CTRL_CLKSOURCE (1 << 2)

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
} SysTick_Typedef;

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
		#define TIM2_BASE (APB1PERIPH_BASE + 0x0000)
		#define TIM3_BASE (APB1PERIPH_BASE + 0x0400)
		#define TIM4_BASE (APB1PERIPH_BASE + 0x0800)
		#define TIM5_BASE (APB1PERIPH_BASE + 0x0C00)
		#define TIM6_BASE (APB1PERIPH_BASE + 0x1000)
		#define TIM7_BASE (APB1PERIPH_BASE + 0x1400)
		#define SPI2_BASE (APB1PERIPH_BASE + 0x3800)
		#define USART2_BASE (APB1PERIPH_BASE + 0x4400)
		#define I2C1_BASE (APB1PERIPH_BASE + 0x5400)
		#define I2C2_BASE (APB1PERIPH_BASE + 0x5800)
		#define DAC_BASE (APB1PERIPH_BASE + 0x7400)
	#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
		#define USART1_BASE (APB2PERIPH_BASE + 0x1000)
		#define SDIO_BASE (APB2PERIPH_BASE + 0x2C00)
		#define SPI1_BASE (APB2PERIPH_BASE + 0x3000)
	#define AHB1PERIPH_BASE (PERIPH_BASE + 0x20000)
		#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000)
		#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400)
		#define GPIOC_BASE (AHB1PERIPH_BASE + 0x0800)
		#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00)
		#define RCC_BASE (AHB1PERIPH_BASE + 0x3800)
		#define FLASH_BASE (AHB1PERIPH_BASE + 0x3C00)

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

#define TIM1 ((GENERAL_TIM_Typedef*)(TIM1_BASE))
#define TIM2 ((GENERAL_TIM_Typedef*)(TIM2_BASE))
#define TIM3 ((GENERAL_TIM_Typedef*)(TIM3_BASE))
#define TIM4 ((GENERAL_TIM_Typedef*)(TIM4_BASE))
#define TIM5 ((GENERAL_TIM_Typedef*)(TIM5_BASE))
#define TIM6 ((BASIC_TIM_Typedef*)(TIM6_BASE))
#define TIM7 ((BASIC_TIM_Typedef*)(TIM7_BASE))
#define I2C1 ((I2C_Typedef*)(I2C1_BASE))
#define I2C2 ((I2C_Typedef*)(I2C2_BASE))
#define DAC ((DAC_Typedef*)(DAC_BASE))

#define USART1 ((USART_Typedef*)(USART1_BASE))
#define USART2 ((USART_Typedef*)(USART2_BASE))
#define SDIO ((SDIO_Typedef*)(SDIO_BASE))
#define SPI1 ((SPI_Typedef*)(SPI1_BASE))
#define SPI2 ((SPI_Typedef*)(SPI2_BASE))

#define GPIOA ((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOB ((GPIO_Typedef*)(GPIOB_BASE))
#define GPIOC ((GPIO_Typedef*)(GPIOC_BASE))
#define GPIOD ((GPIO_Typedef*)(GPIOD_BASE))
#define RCC ((RCC_Typedef*)(RCC_BASE))
#define FLASH ((FLASH_Typedef*)(FLASH_BASE))

#endif
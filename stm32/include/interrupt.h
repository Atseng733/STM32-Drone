#ifndef INTERRUPT_H
#define INTERRUPT_H
#include <stdint.h> 
#include <f407.h>
#include <f407_fn.h>

void Default_Handler();

#define DECLARE_HANDLER(vector) extern "C" void vector##_Handler(void);
#define DEFINE_HANDLER(vector) extern "C" void __attribute__ ((weak)) vector##_Handler(void) { Default_Handler(); }

#define IRQ0_Handler WWDG_Handler
#define IRQ1_Handler PVD_Handler
#define IRQ2_Handler TAMP_STAMP_Handler
#define IRQ3_Handler RTC_WKUP_Handler
#define IRQ4_Handler FLASH_Handler
#define IRQ5_Handler RCC_Handler
#define IRQ6_Handler EXTI0_Handler
#define IRQ7_Handler EXTI1_Handler
#define IRQ8_Handler EXTI2_Handler
#define IRQ9_Handler EXTI3_Handler
#define IRQ10_Handler EXTI4_Handler
#define IRQ11_Handler DMA1_Stream0_Handler
#define IRQ12_Handler DMA1_Stream1_Handler
#define IRQ13_Handler DMA1_Stream2_Handler
#define IRQ14_Handler DMA1_Stream3_Handler
#define IRQ15_Handler DMA1_Stream4_Handler
#define IRQ16_Handler DMA1_Stream5_Handler
#define IRQ17_Handler DMA1_Stream6_Handler
#define IRQ18_Handler ADC_Handler
#define IRQ19_Handler CAN1_TX_Handler
#define IRQ20_Handler CAN1_RX0_Handler
#define IRQ21_Handler CAN1_RX1_Handler
#define IRQ22_Handler CAN1_SCE_Handler
#define IRQ23_Handler EXTI9_5_Handler
#define IRQ24_Handler TIM1_BRK_TIM9_Handler
#define IRQ25_Handler TIM1_UP_TIM10_Handler
#define IRQ26_Handler TIM1_TRG_COM_TIM11_Handler
#define IRQ27_Handler TIM1_CC_Handler
#define IRQ28_Handler TIM2_Handler
#define IRQ29_Handler TIM3_Handler
#define IRQ30_Handler TIM4_Handler
#define IRQ31_Handler I2C1_EV_Handler
#define IRQ32_Handler I2C1_ER_Handler
#define IRQ33_Handler I2C2_EV_Handler
#define IRQ34_Handler I2C2_ER_Handler
#define IRQ35_Handler SPI1_Handler
#define IRQ36_Handler SPI2_Handler
#define IRQ37_Handler USART1_Handler
#define IRQ38_Handler USART2_Handler
#define IRQ39_Handler USART3_Handler
#define IRQ40_Handler EXTI15_10_Handler
#define IRQ41_Handler RTC_Alarm_Handler
#define IRQ42_Handler OTG_FS_WKUP_Handler
#define IRQ43_Handler TIM8_BRK_TIM12_Handler
#define IRQ44_Handler TIM8_UP_TIM13_Handler
#define IRQ45_Handler TIM8_TRG_COM_TIM14_Handler
#define IRQ46_Handler TIM8_CC_Handler
#define IRQ47_Handler DMA1_Stream7_Handler
#define IRQ48_Handler FSMC_Handler
#define IRQ49_Handler SDIO_Handler
#define IRQ50_Handler TIM5_Handler
#define IRQ51_Handler SPI3_Handler
#define IRQ52_Handler UART4_Handler
#define IRQ53_Handler UART5_Handler
#define IRQ54_Handler TIM6_DAC_Handler 
#define IRQ55_Handler TIM7_Handler
#define IRQ56_Handler DMA2_Stream0_Handler
#define IRQ57_Handler DMA2_Stream1_Handler
#define IRQ58_Handler DMA2_Stream2_Handler
#define IRQ59_Handler DMA2_Stream3_Handler
#define IRQ60_Handler DMA2_Stream4_Handler
#define IRQ61_Handler ETH_Handler
#define IRQ62_Handler ETH_WKUP_Handler
#define IRQ63_Handler CAN2_TX_Handler
#define IRQ64_Handler CAN2_RX0_Handler
#define IRQ65_Handler CAN2_RX1_Handler
#define IRQ66_Handler CAN2_SCE_Handler
#define IRQ67_Handler OTG_FS_Handler
#define IRQ68_Handler DMA2_Stream5_Handler
#define IRQ69_Handler DMA2_Stream6_Handler
#define IRQ70_Handler DMA2_Stream7_Handler
#define IRQ71_Handler USART6_Handler
#define IRQ72_Handler I2C3_EV_Handler
#define IRQ73_Handler I2C3_ER_Handler
#define IRQ74_Handler OTG_HS_EP1_OUT_Handler
#define IRQ75_Handler OTG_HS_EP1_IN_Handler
#define IRQ76_Handler OTG_HS_WKUP_Handler
#define IRQ77_Handler OTG_HS_Handler
#define IRQ78_Handler DCMI_Handler
#define IRQ79_Handler CRYP_Handler
#define IRQ80_Handler HASH_RNG_Handler
#define IRQ81_Handler FPU_Handler

DECLARE_HANDLER(Reset)
DECLARE_HANDLER(NMI)
DECLARE_HANDLER(HardFault)
DECLARE_HANDLER(MemManage)
DECLARE_HANDLER(BusFault)
DECLARE_HANDLER(UsageFault)
DECLARE_HANDLER(SVCall)
DECLARE_HANDLER(DebugMonitor)
DECLARE_HANDLER(PendSV)
DECLARE_HANDLER(SysTick)
DECLARE_HANDLER(IRQ0)
DECLARE_HANDLER(IRQ1)
DECLARE_HANDLER(IRQ2)
DECLARE_HANDLER(IRQ3)
DECLARE_HANDLER(IRQ4)
DECLARE_HANDLER(IRQ5)
DECLARE_HANDLER(IRQ6)
DECLARE_HANDLER(IRQ7)
DECLARE_HANDLER(IRQ8)
DECLARE_HANDLER(IRQ9)
DECLARE_HANDLER(IRQ10)
DECLARE_HANDLER(IRQ11)
DECLARE_HANDLER(IRQ12)
DECLARE_HANDLER(IRQ13)
DECLARE_HANDLER(IRQ14)
DECLARE_HANDLER(IRQ15)
DECLARE_HANDLER(IRQ16)
DECLARE_HANDLER(IRQ17)
DECLARE_HANDLER(IRQ18)
DECLARE_HANDLER(IRQ19)
DECLARE_HANDLER(IRQ20)
DECLARE_HANDLER(IRQ21)
DECLARE_HANDLER(IRQ22)
DECLARE_HANDLER(IRQ23)
DECLARE_HANDLER(IRQ24)
DECLARE_HANDLER(IRQ25)
DECLARE_HANDLER(IRQ26)
DECLARE_HANDLER(IRQ27)
DECLARE_HANDLER(IRQ28)
DECLARE_HANDLER(IRQ29)
DECLARE_HANDLER(IRQ30)
DECLARE_HANDLER(IRQ31)
DECLARE_HANDLER(IRQ32)
DECLARE_HANDLER(IRQ33)
DECLARE_HANDLER(IRQ34)
DECLARE_HANDLER(IRQ35)
DECLARE_HANDLER(IRQ36)
DECLARE_HANDLER(IRQ37)
DECLARE_HANDLER(IRQ38)
DECLARE_HANDLER(IRQ39)
DECLARE_HANDLER(IRQ40)
DECLARE_HANDLER(IRQ41)
DECLARE_HANDLER(IRQ42)
DECLARE_HANDLER(IRQ43)
DECLARE_HANDLER(IRQ44)
DECLARE_HANDLER(IRQ45)
DECLARE_HANDLER(IRQ46)
DECLARE_HANDLER(IRQ47)
DECLARE_HANDLER(IRQ48)
DECLARE_HANDLER(IRQ49)
DECLARE_HANDLER(IRQ50)
DECLARE_HANDLER(IRQ51)
DECLARE_HANDLER(IRQ52)
DECLARE_HANDLER(IRQ53)
DECLARE_HANDLER(IRQ54)
DECLARE_HANDLER(IRQ55)
DECLARE_HANDLER(IRQ56)
DECLARE_HANDLER(IRQ57)
DECLARE_HANDLER(IRQ58)
DECLARE_HANDLER(IRQ59)
DECLARE_HANDLER(IRQ60)
DECLARE_HANDLER(IRQ61)
DECLARE_HANDLER(IRQ62)
DECLARE_HANDLER(IRQ63)
DECLARE_HANDLER(IRQ64)
DECLARE_HANDLER(IRQ65)
DECLARE_HANDLER(IRQ66)
DECLARE_HANDLER(IRQ67)
DECLARE_HANDLER(IRQ68)
DECLARE_HANDLER(IRQ69)
DECLARE_HANDLER(IRQ70)
DECLARE_HANDLER(IRQ71)
DECLARE_HANDLER(IRQ72)
DECLARE_HANDLER(IRQ73)
DECLARE_HANDLER(IRQ74)
DECLARE_HANDLER(IRQ75)
DECLARE_HANDLER(IRQ76)
DECLARE_HANDLER(IRQ77)
DECLARE_HANDLER(IRQ78)
DECLARE_HANDLER(IRQ79)
DECLARE_HANDLER(IRQ80)
DECLARE_HANDLER(IRQ81)

extern "C" void enableInterrupt(uint8_t IRQx);
extern "C" void disableInterrupt(uint8_t IRQx);

#endif
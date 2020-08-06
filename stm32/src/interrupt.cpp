#include <interrupt.h>

void Default_Handler() {
	GPIO_pinMode(GPIOD, 6, OUTPUT);
	GPIO_writeHigh(GPIOD, 6);
	while(1);
}

DEFINE_HANDLER(Reset)
DEFINE_HANDLER(NMI)
DEFINE_HANDLER(HardFault)
DEFINE_HANDLER(MemManage)
DEFINE_HANDLER(BusFault)
DEFINE_HANDLER(UsageFault)
DEFINE_HANDLER(SVCall)
DEFINE_HANDLER(DebugMonitor)
DEFINE_HANDLER(PendSV)
DEFINE_HANDLER(SysTick)
DEFINE_HANDLER(IRQ0)
DEFINE_HANDLER(IRQ1)
DEFINE_HANDLER(IRQ2)
DEFINE_HANDLER(IRQ3)
DEFINE_HANDLER(IRQ4)
DEFINE_HANDLER(IRQ5)
DEFINE_HANDLER(IRQ6)
DEFINE_HANDLER(IRQ7)
DEFINE_HANDLER(IRQ8)
DEFINE_HANDLER(IRQ9)
DEFINE_HANDLER(IRQ10)
DEFINE_HANDLER(IRQ11)
DEFINE_HANDLER(IRQ12)
DEFINE_HANDLER(IRQ13)
DEFINE_HANDLER(IRQ14)
DEFINE_HANDLER(IRQ15)
DEFINE_HANDLER(IRQ16)
DEFINE_HANDLER(IRQ17)
DEFINE_HANDLER(IRQ18)
DEFINE_HANDLER(IRQ19)
DEFINE_HANDLER(IRQ20)
DEFINE_HANDLER(IRQ21)
DEFINE_HANDLER(IRQ22)
DEFINE_HANDLER(IRQ23)
DEFINE_HANDLER(IRQ24)
DEFINE_HANDLER(IRQ25)
DEFINE_HANDLER(IRQ26)
DEFINE_HANDLER(IRQ27)
DEFINE_HANDLER(IRQ28)
DEFINE_HANDLER(IRQ29)
DEFINE_HANDLER(IRQ30)
DEFINE_HANDLER(IRQ31)
DEFINE_HANDLER(IRQ32)
DEFINE_HANDLER(IRQ33)
DEFINE_HANDLER(IRQ34)
DEFINE_HANDLER(IRQ35)
DEFINE_HANDLER(IRQ36)
DEFINE_HANDLER(IRQ37)
DEFINE_HANDLER(IRQ38)
DEFINE_HANDLER(IRQ39)
DEFINE_HANDLER(IRQ40)
DEFINE_HANDLER(IRQ41)
DEFINE_HANDLER(IRQ42)
DEFINE_HANDLER(IRQ43)
DEFINE_HANDLER(IRQ44)
DEFINE_HANDLER(IRQ45)
DEFINE_HANDLER(IRQ46)
DEFINE_HANDLER(IRQ47)
DEFINE_HANDLER(IRQ48)
DEFINE_HANDLER(IRQ49)
DEFINE_HANDLER(IRQ50)
DEFINE_HANDLER(IRQ51)
DEFINE_HANDLER(IRQ52)
DEFINE_HANDLER(IRQ53)
DEFINE_HANDLER(IRQ54)
DEFINE_HANDLER(IRQ55)
DEFINE_HANDLER(IRQ56)
DEFINE_HANDLER(IRQ57)
DEFINE_HANDLER(IRQ58)
DEFINE_HANDLER(IRQ59)
DEFINE_HANDLER(IRQ60)
DEFINE_HANDLER(IRQ61)
DEFINE_HANDLER(IRQ62)
DEFINE_HANDLER(IRQ63)
DEFINE_HANDLER(IRQ64)
DEFINE_HANDLER(IRQ65)
DEFINE_HANDLER(IRQ66)
DEFINE_HANDLER(IRQ67)
DEFINE_HANDLER(IRQ68)
DEFINE_HANDLER(IRQ69)
DEFINE_HANDLER(IRQ70)
DEFINE_HANDLER(IRQ71)
DEFINE_HANDLER(IRQ72)
DEFINE_HANDLER(IRQ73)
DEFINE_HANDLER(IRQ74)
DEFINE_HANDLER(IRQ75)
DEFINE_HANDLER(IRQ76)
DEFINE_HANDLER(IRQ77)
DEFINE_HANDLER(IRQ78)
DEFINE_HANDLER(IRQ79)
DEFINE_HANDLER(IRQ80)
DEFINE_HANDLER(IRQ81)

extern void (*const vectors[])() __attribute__ ((section(".vectors"))) = {
	(void (*)())0x20000400,  //0x0000
	Reset_Handler,         
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0,
	0,                       //0x0020
	0,
	0,
	SVCall_Handler,
	DebugMonitor_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,
	IRQ0_Handler,            //0x0040
	IRQ1_Handler,
	IRQ2_Handler,
	IRQ3_Handler,
	IRQ4_Handler,
	IRQ5_Handler,
	IRQ6_Handler,
	IRQ7_Handler,
	IRQ8_Handler,            //0x0060
	IRQ9_Handler,
	IRQ10_Handler,
	IRQ11_Handler,
	IRQ12_Handler,
	IRQ13_Handler,
	IRQ14_Handler,
	IRQ15_Handler,
	IRQ16_Handler,           //0x0080
	IRQ17_Handler,
	IRQ18_Handler,
	IRQ19_Handler,
	IRQ20_Handler,
	IRQ21_Handler,
	IRQ22_Handler,
	IRQ23_Handler,
	IRQ24_Handler,           //0x00A0
	IRQ25_Handler,
	IRQ26_Handler,
	IRQ27_Handler,
	IRQ28_Handler,
	IRQ29_Handler,
	IRQ30_Handler,
	IRQ31_Handler,
	IRQ32_Handler,           //0x00C0
	IRQ33_Handler,
	IRQ34_Handler,
	IRQ35_Handler,
	IRQ36_Handler,
	IRQ37_Handler,
	IRQ38_Handler,
	IRQ39_Handler,
	IRQ40_Handler,           //0x00E0
	IRQ41_Handler,
	IRQ42_Handler,
	IRQ43_Handler,
	IRQ44_Handler,
	IRQ45_Handler,
	IRQ46_Handler,
	IRQ47_Handler,
	IRQ48_Handler,           //0x0100
	IRQ49_Handler,
	IRQ50_Handler,
	IRQ51_Handler,
	IRQ52_Handler,
	IRQ53_Handler,
	IRQ54_Handler,
	IRQ55_Handler,
	IRQ56_Handler,           //0x0120
	IRQ57_Handler,
	IRQ58_Handler,
	IRQ59_Handler,
	IRQ60_Handler,
	IRQ61_Handler,
	IRQ62_Handler,
	IRQ63_Handler,
	IRQ64_Handler,           //0x0140
	IRQ65_Handler,
	IRQ66_Handler,
	IRQ67_Handler,
	IRQ68_Handler,
	IRQ69_Handler,
	IRQ70_Handler,
	IRQ71_Handler,
	IRQ72_Handler,           //0x0160
	IRQ73_Handler,
	IRQ74_Handler,
	IRQ75_Handler,
	IRQ76_Handler,
	IRQ77_Handler,
	IRQ78_Handler,
	IRQ79_Handler,
	IRQ80_Handler,           //0x0180
	IRQ81_Handler,
};

void enableInterrupt(uint8_t IRQx) {
	switch(IRQx/32) {
		case 0:
			NVIC_ISER->ISER0 |= (1 << (IRQx % 32));
			break;
		case 1:
			NVIC_ISER->ISER1 |= (1 << (IRQx % 32));
			break;
		case 2:
			NVIC_ISER->ISER2 |= (1 << (IRQx % 32));
			break;
		case 3:
			NVIC_ISER->ISER3 |= (1 << (IRQx % 32));
			break;
		case 4:
			NVIC_ISER->ISER4 |= (1 << (IRQx % 32));
			break;
		case 5:
			NVIC_ISER->ISER5 |= (1 << (IRQx % 32));
			break;
		case 6:
			NVIC_ISER->ISER6 |= (1 << (IRQx % 32));
			break;
		case 7:
			NVIC_ISER->ISER7 |= (1 << (IRQx % 32));
			break;
	}
}

void disableInterrupt(uint8_t IRQx) {
	switch(IRQx/32) {
		case 0:
			NVIC_ICER->ICER0 |= (1 << (IRQx % 32));
			break;
		case 1:
			NVIC_ICER->ICER1 |= (1 << (IRQx % 32));
			break;
		case 2:
			NVIC_ICER->ICER2 |= (1 << (IRQx % 32));
			break;
		case 3:
			NVIC_ICER->ICER3 |= (1 << (IRQx % 32));
			break;
		case 4:
			NVIC_ICER->ICER4 |= (1 << (IRQx % 32));
			break;
		case 5:
			NVIC_ICER->ICER5 |= (1 << (IRQx % 32));
			break;
		case 6:
			NVIC_ICER->ICER6 |= (1 << (IRQx % 32));
			break;
		case 7:
			NVIC_ICER->ICER7 |= (1 << (IRQx % 32));
			break;
	}
}
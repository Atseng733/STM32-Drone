#ifndef USART_H
#define USART_H

#include <boards.h>
#include <stm32_stdlib.h>
#include <rcc.h>
#include <interrupt.h>

#define USARTDIV(baud, f_cpu) ((double)f_cpu / (16 * baud))
#define BRR_MANTISSA(usartdiv) ((uint16_t)(usartdiv))
#define BRR_FRACTION(usartdiv) ((uint16_t)((usartdiv - (uint16_t)usartdiv) * 16))

#define USART_READY 0
#define USART_BUSY_TX 1
#define USART_BUSY_RX 2

#define USART_MODE_TX 0
#define USART_MODE_RX 1
#define USART_MODE_TXRX 2

#define RX_BUFFER_SIZE 0x7F //make sure it's something like 0b11111111 not 0b11011111

typedef struct {
	USART_Typedef* USARTx;
	uint8_t RxBuffer[RX_BUFFER_SIZE];
	uint16_t RxLen;
	uint8_t RxBuffer_w;
	uint8_t RxBuffer_r;
} USART_Struct;

class usart {
	private:
		USART_Struct* pUSART_Struct;
	public:
		void Init(USART_Struct* pusart_struct, uint32_t baud, uint8_t mode);
		void USART_InterruptEnable();
		uint8_t GetFlagStatus(uint32_t reg, uint32_t flag);
		void printc(char c);
		void print(char* str);
		void println(char* str);
		void println(int32_t num, uint8_t base);
		void printd(double d, uint8_t prec);
		void sendIT(char* str);
		void receiveIT();
		void read(uint8_t* data, uint16_t len);
		int readSync(uint8_t* data, uint16_t len, uint8_t syncByte);
		void USART_ISR();
};

extern usart Serial1;
extern usart Serial2;

#endif
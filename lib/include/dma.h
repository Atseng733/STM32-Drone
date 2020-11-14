#ifndef DMA_H
#define DMA_H

#include <boards.h>
#include <usart.h>
#define DMA_CCRx(n) CCR ## n
#define DMA_CPARx(n) CPAR ## n
#define DMA_CMARx(n) CMAR ## n
#define DMA_CNDTRx(n) CNDTR ## n

typedef struct {
    uint16_t CCR;
    uint16_t CNDTR;
    uint32_t CPAR;
    uint32_t CMAR;
} DMA_Struct;

void DMA_Channel_Config(DMA_Typedef* DMAx, uint8_t channel, DMA_Struct* pDMA_Struct);


#endif
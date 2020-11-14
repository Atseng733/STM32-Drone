#include <dma.h>

void DMA_Channel_Config(DMA_Typedef* DMAx, uint8_t channel, DMA_Struct* pDMA_Struct) {
    if(channel == 1) {
        //Set peripheral address register
        DMAx->CPAR1 = pDMA_Struct->CPAR;

        //Set memory address register
        DMAx->CMAR1 = pDMA_Struct->CMAR;

        //Set data number register
        DMAx->CNDTR1 = pDMA_Struct->CNDTR;

        //Configure channel and enable
        DMAx->CCR1 = pDMA_Struct->CCR;
        DMAx->CCR1 |= DMA_CCR_EN;
    }
    else if(channel == 2) {
        DMAx->CPAR2 = pDMA_Struct->CPAR;
        DMAx->CMAR2 = pDMA_Struct->CMAR;
        DMAx->CNDTR2 = pDMA_Struct->CNDTR;
        DMAx->CCR2 = pDMA_Struct->CCR;
        DMAx->CCR2 |= DMA_CCR_EN;
    }
    else if(channel == 3) {
        DMAx->CPAR3 = pDMA_Struct->CPAR;
        DMAx->CMAR3 = pDMA_Struct->CMAR;
        DMAx->CNDTR3 = pDMA_Struct->CNDTR;
        DMAx->CCR3 = pDMA_Struct->CCR;
        DMAx->CCR3 |= DMA_CCR_EN;
    }
    else if(channel == 4) {
        DMAx->CPAR4 = pDMA_Struct->CPAR;
        DMAx->CMAR4 = pDMA_Struct->CMAR;
        DMAx->CNDTR4 = pDMA_Struct->CNDTR;
        DMAx->CCR4 = pDMA_Struct->CCR;
        DMAx->CCR4 |= DMA_CCR_EN;
    }
    else if(channel == 5) {
        DMAx->CPAR5 = pDMA_Struct->CPAR;
        DMAx->CMAR5 = pDMA_Struct->CMAR;
        DMAx->CNDTR5 = pDMA_Struct->CNDTR;
        DMAx->CCR5 = pDMA_Struct->CCR;
        DMAx->CCR5 |= DMA_CCR_EN;
    }
    else if(channel == 6) {
        DMAx->CPAR6 = pDMA_Struct->CPAR;
        DMAx->CMAR6 = pDMA_Struct->CMAR;
        DMAx->CNDTR6 = pDMA_Struct->CNDTR;
        DMAx->CCR6 = pDMA_Struct->CCR;
        DMAx->CCR6 |= DMA_CCR_EN;
    }
    else if(channel == 7) {
        DMAx->CPAR7 = pDMA_Struct->CPAR;
        DMAx->CMAR7 = pDMA_Struct->CMAR;
        DMAx->CNDTR7 = pDMA_Struct->CNDTR;
        DMAx->CCR7 = pDMA_Struct->CCR;
        DMAx->CCR7 |= DMA_CCR_EN;
    }
    else {
        Serial2.println("Invalid DMA channel");
    }
}
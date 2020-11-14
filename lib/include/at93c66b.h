#ifndef AT93C66B_H
#define AT93C66B_H

#include <boards.h>
#include <spi.h>
#include <usart.h>

class at93c66b {
    private:
        SPI_Struct *pSPI_Struct;
    public:
        at93c66b();
        void Init(SPI_Struct *pStruct);
        uint16_t Read(uint8_t addr);
};

#endif
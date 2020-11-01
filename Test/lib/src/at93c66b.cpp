#include <at93c66b.h>

at93c66b::at93c66b() {}

void at93c66b::Init(SPI_Struct *pStruct) {
    //Max 1 MHz at 3.3V
    pSPI_Struct = pStruct;
}

uint16_t at93c66b::Read(uint8_t addr) {
    //all commands begin with CS rising edge and a start bit(1) and op code
    //read opcode is 0b10
    uint16_t temp = (((0b110 << 8) | addr) << 5);

    //manually toggle CS
    if(pSPI_Struct->SPIx == SPI1) {
        writeLow(GPIOA, 4);
        writeHigh(GPIOA, 4);
    }

    //send start bit, opcode, and read address
    SPI_Tx(pSPI_Struct, 0xFFFF);

    writeLow(GPIOA, 4);
    
    //Read data
    //temp = SPI_Rx(pSPI_Struct);
    //Serial2.printc('c');
    return temp;
}
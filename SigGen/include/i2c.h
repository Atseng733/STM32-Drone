/*
 * i2c.h
 *
 * Created: 6/10/2020 11:03:44 PM
 *  Author: Anthony
 */ 


#ifndef I2C_H
#define I2C_H

void I2CStart(unsigned char _i2caddr);
void I2CStop();
void I2CSend(unsigned char data);
void write8(unsigned char addr, unsigned char reg, unsigned char value);

#endif /* I2C_H_ */
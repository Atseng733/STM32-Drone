#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H
#include <stdint.h>
#include <boards.h>

typedef struct {
	uint32_t I2C_SCLSpeed;
	uint8_t I2C_DeviceAddress;
	uint8_t I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
} I2C_Config_t;

typedef struct {
	I2C_Typedef* pI2Cx;
	I2C_Config_t I2C_Config;
} I2C_Handle_t;

#define I2C_SCL_SPEED_SM 100000
#define I2C_SCL_SPEED_FM_200K 100000
#define I2C_SCL_SPEED_FM_400K 400000

#define I2C_ACK_DISABLE 0
#define I2C_ACK_ENABLE 1

#define I2C_FM_DUTY_2 0
#define I2C_FM_DUTY_16_9 1

void I2C_Init(I2C_Handle_t* I2CHandle);
void I2C_DeInit(I2C_Typedef* I2Cx);

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnDis);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

#endif
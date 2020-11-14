#include <mpu6050.h>

mpu6050::mpu6050() {
}

uint8_t mpu6050::Init(uint8_t gyro_addr) {
    addr = gyro_addr;
    I2C.Write(addr, PWR_MGMT_1, 0x00); //reset all registers to default values
   
    return I2C.Read(addr, WHO_AM_I);
}

void mpu6050::Gyro_FS_Select(uint8_t fs_range) {
    I2C.Write(addr, GYRO_CONFIG, fs_range << 3);
}

void mpu6050::Accel_FS_Select(uint8_t fs_range) {
    I2C.Write(addr, ACCEL_CONFIG, fs_range << 3);
}

void mpu6050::Read_Gyro_Data(int16_t* gyro_data) {
    uint8_t raw_gyro_data[6];

    I2C.Read(addr, GYRO_XOUT_H, raw_gyro_data, 6);

    gyro_data[0] = (((int16_t)raw_gyro_data[0] << 8) | raw_gyro_data[1]);
	gyro_data[1] = (((int16_t)raw_gyro_data[2] << 8) | raw_gyro_data[3]);
	gyro_data[2] = (((int16_t)raw_gyro_data[4] << 8) | raw_gyro_data[5]);
}

void mpu6050::Read_Accel_Data(int16_t* accel_data) {
    uint8_t raw_accel_data[6];

    I2C.Read(addr, ACCEL_XOUT_H, raw_accel_data, 6);

    accel_data[0] = (((int16_t)raw_accel_data[0] << 8) | raw_accel_data[1]);
	accel_data[1] = (((int16_t)raw_accel_data[2] << 8) | raw_accel_data[3]);
	accel_data[2] = (((int16_t)raw_accel_data[4] << 8) | raw_accel_data[5]);
}
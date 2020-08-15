#include <mpu9250.h>

void mpu9250::init(uint8_t sAddr) {
	addr = sAddr;
	I2C.write(addr, PWR_MGMT_1, 0x80); //reset all registers to default values
	delay_ms(10);
	//delay_us(1000);
	//delay_ms(100);
	gyro_fs_select(GYRO_FS_1000dps);
	accel_fs_select(ACCEL_FS_8g);
}

uint8_t mpu9250::who_am_i() {
	return I2C.read(addr, WHO_AM_I);
}

void mpu9250::selftest_enable() {
	uint8_t gyro_config;
	gyro_config = 0xE0;
	I2C.write(addr, GYRO_CONFIG, 15);
}

void mpu9250::fifo_enable_gyro() {
	uint8_t fifo_en = I2C.read(addr, FIFO_EN);
	fifo_en |= 0x70;
	I2C.write(addr, FIFO_EN, fifo_en);
}

void mpu9250::gyro_fs_select(uint8_t fs) {
	I2C.write(addr, GYRO_CONFIG, (fs << 3));
}

void mpu9250::accel_fs_select(uint8_t fs) {
	I2C.write(addr, ACCEL_CONFIG, (fs << 3));
}

void mpu9250::read_gyro_data(int16_t* gyro_data) {
	I2C.read(addr, GYRO_XOUT_H, raw_gyro_data, 6);
	gyro_data[0] = (((int16_t)raw_gyro_data[0] << 8) | raw_gyro_data[1]);
	gyro_data[1] = (((int16_t)raw_gyro_data[2] << 8) | raw_gyro_data[3]);
	gyro_data[2] = (((int16_t)raw_gyro_data[4] << 8) | raw_gyro_data[5]);
}

void mpu9250::read_accel_data(int16_t* accel_data) {
	I2C.read(addr, ACCEL_XOUT_H, raw_accel_data, 6);
	accel_data[0] = (((int16_t)raw_accel_data[0] << 8) | raw_accel_data[1]);
	accel_data[1] = (((int16_t)raw_accel_data[2] << 8) | raw_accel_data[3]);
	accel_data[2] = (((int16_t)raw_accel_data[4] << 8) | raw_accel_data[5]);
}

int16_t mpu9250::read_temp_data() {
	I2C.read(addr, TEMP_OUT_H, raw_temp_data, 2);
	return ((raw_temp_data[0] << 8) | raw_temp_data[1]);
}
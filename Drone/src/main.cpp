#include <main.h>

const uint8_t MPU_ADDR = 0x68;
uint8_t data[14];

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;

char tmp_str[7];
char* convert_int16_to_str(int16_t i) {
	print(itoa(i, tmp_str, 10));
	return tmp_str;
}
int i = 0;
int main() {
	display.begin();
	print("gy-521 test ");
	TWI_Write(MPU_ADDR, 0x6B, 0);
	while(1) {
		display.clearDisplay();
		gyro_x = TWI_Read(MPU_ADDR, 0x43) << 8;
		//gyro_x |= TWI_Read(MPU_ADDR, 0x44);
		display.print(itoa(gyro_x, tmp_str, 16));
		/*TWI_Read(MPU_ADDR, 0x3B, 14, data);
		accelerometer_x = data[0]<<8 | data[1];
		accelerometer_y = data[2]<<8 | data[3];
		accelerometer_z = data[4]<<8 | data[5];
		temperature = TWI_Read(MPU_ADDR, 0x41)<<8;
		temperature |= TWI_Read(MPU_ADDR, 0x42);	//data[6]<<8 | data[7];
		gyro_x = data[8]<<8 | data[9];
		gyro_y = data[10]<<8 | data[11];
		gyro_z = data[12]<<8 | data[13];
		display.clearDisplay();
		display.print(itoa(accelerometer_x, tmp_str, 10)); display.print(" ");
		display.print(itoa(accelerometer_y, tmp_str, 10)); display.print(" ");
		display.print(itoa(accelerometer_z, tmp_str, 10)); 
		display.setCursor(0,1);
		display.print(itoa(gyro_x, tmp_str, 10)); display.print(" ");
		display.print(itoa(gyro_y, tmp_str, 10)); display.print(" ");
		display.print(itoa(gyro_z, tmp_str, 10));
		display.setCursor(0,2);
		display.print(itoa(temperature, tmp_str, 10)); display.print(" ");
		display.print(itoa(i, tmp_str, 10));*/
		display.display();
		delay(100);
		i++;
	}
}
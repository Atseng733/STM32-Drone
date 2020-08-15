#include <main.h>
mpu9250 IMU;
ssd1306 display;
char str[32];
int16_t gyro_data[3];
int16_t accel_data[3];
int16_t gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z;
int32_t gyro_x_cal, gyro_y_cal, gyro_z_cal, accel_vect;
double pitch_angle, roll_angle, yaw_angle;
double accel_pitch, accel_roll, accel_yaw;
uint64_t loop_timer;
uint16_t ch1, ch2, ch3, ch4, ch5, ch6;

#define REFRESH_RATE 90
#define LOOP_PERIOD ((uint32_t)((1 / (double)REFRESH_RATE) * 1000000))

void read_sensor_data() {
	IMU.read_gyro_data(gyro_data);
	IMU.read_accel_data(accel_data);
	gyro_x = gyro_data[0];
	gyro_y = gyro_data[1];
	gyro_z = gyro_data[2];
	accel_x = accel_data[0];
	accel_y = accel_data[1];
	accel_z = accel_data[2];
}

void calibrate_sensors(int n) {
	gyro_x_cal = 0;
	gyro_y_cal = 0;
	gyro_z_cal = 0;

	for(int i = 0; i < n; i++) {
		read_sensor_data();
		gyro_x_cal += gyro_x;
		gyro_y_cal += gyro_y;
		gyro_z_cal += gyro_z;
		delay_ms(2);
	}

	gyro_x_cal /= n;
	gyro_y_cal /= n;
	gyro_z_cal /= n;
	//USART.print("gyro cal: "); USART.print(gyro_x_cal); USART.print(" ; "); USART.print(gyro_y_cal); USART.print(" ; "); USART.println(gyro_z_cal);
}

void calculate_axes() {
	read_sensor_data();
	gyro_x -= gyro_x_cal;
	gyro_y -= gyro_y_cal;
	gyro_z -= gyro_z_cal;
	//USART.print(gyro_x); USART.print(" ; "); USART.print(gyro_y); USART.print(" ; "); USART.println(gyro_z);
	//USART.print(accel_x, 10); USART.print(" ; "); USART.print(accel_y, 10); USART.print(" ; "); USART.println(accel_z, 10);
	pitch_angle += (gyro_x / (REFRESH_RATE*65.5*.5));
	roll_angle += (gyro_y / (REFRESH_RATE*65.5*.5));
	pitch_angle += roll_angle * sin((gyro_z * (M_PI/180)) / (REFRESH_RATE*65.5*.5));
	roll_angle -= roll_angle * sin((gyro_z * (M_PI/180)) / (REFRESH_RATE*65.5*.5));

	accel_vect = sqrt((accel_x * accel_x) + (accel_y * accel_y) + (accel_z * accel_z));
	accel_pitch = asin((double)accel_y/accel_vect) * (180 / M_PI);
	accel_roll = asin((double)accel_x / accel_vect) * -(180 / M_PI);
	accel_pitch -= 5.3;
	accel_roll -= 1.8;
	//USART.println(accel_pitch);
	//USART.println(accel_roll);
	pitch_angle = (pitch_angle * .9996) + (accel_pitch * .0004);
	roll_angle = (roll_angle * .9996) + (accel_roll * .0004);

	USART.println(pitch_angle);
	USART.println(roll_angle);

	//USART.println("");
}

uint8_t receiverData[32];
int main(void) {
	IMU.init(0x68);
	//display.begin(0x3C);
	
	pitch_angle = 0;
	roll_angle = 0;
	yaw_angle = 0;

	USART.println("Starting Program");

	pinMode(GPIOC, 13, OUTPUT);
	pinConfig(GPIOC, 13, GPO_PP);
	pinMode(GPIOB, 9, OUTPUT);
	pinConfig(GPIOB, 9, GPO_PP);

	calibrate_sensors(2000);

	/*USART.receiveIT(receiverData, 32);
	if(receiverData[0] != 0x20) {
		delay_ms(7);
		USART.receiveIT(receiverData, 32);
	}*/
	for(int i = 0; i < 32; i++) {
		receiverData[i] = USART.read();
	}
	
	for(uint8_t i: receiverData) {
		USART.println(i, 16);
	}

	ch1 = (receiverData[2]) | (receiverData[3] << 8);
	ch2 = (receiverData[4]) | (receiverData[5] << 8);
	ch3 = (receiverData[6]) | (receiverData[7] << 8);
	ch4 = (receiverData[8]) | (receiverData[9] << 8);
	ch5 = (receiverData[10]) | (receiverData[11] << 8);
	
	USART.println(ch1, 10);
	USART.println(ch2, 10);
	USART.println(ch3, 10);
	USART.println(ch4, 10);
	USART.println(ch5, 10);

	loop_timer = micros();
	while(true) {
		toggle(GPIOC, 13);
		toggle(GPIOB, 9);
		//calculate_axes();
		while(micros() - loop_timer < LOOP_PERIOD); //250Hz refresh rate, T = 4ms = 4000us
		loop_timer = micros();
	}

	return 0;
}

void Reset_Handler() {
	rcc_sys_clk_setup();
	rcc_io_enable(RCC_GPIOA);
	rcc_io_enable(RCC_GPIOB);
	rcc_io_enable(RCC_GPIOC);
	rcc_io_enable(RCC_GPIOD);
	rcc_io_enable(RCC_AFIO);
	USART.init(USART1, 115200);
	timer_init();
	I2C.init();
	main();
}

#include <main.h>
mpu9250 IMU;
ssd1306 display;

char str[32]; //for integer-value to array functions

int16_t gyro_data[3];
int16_t accel_data[3];
int16_t gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z;
int32_t gyro_x_cal, gyro_y_cal, gyro_z_cal, accel_vect;
double pitch_angle, roll_angle, yaw_angle;
double accel_pitch, accel_roll, accel_yaw;

uint8_t receiverData[32];
uint16_t ch1, ch2, ch3, ch4, ch5, ch6;

uint64_t loop_timer;
volatile uint64_t last_exti;
volatile bool syncing;
#define REFRESH_RATE 250 //main loop frequency and period
#define LOOP_PERIOD ((uint16_t)(1000000 / (double)REFRESH_RATE))

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

	pitch_angle += (gyro_x / (REFRESH_RATE*65.5*.5));
	roll_angle += (gyro_y / (REFRESH_RATE*65.5*.5));
	pitch_angle += roll_angle * sin((gyro_z * (M_PI/180)) / (REFRESH_RATE*65.5*.5));
	roll_angle -= roll_angle * sin((gyro_z * (M_PI/180)) / (REFRESH_RATE*65.5*.5));

	accel_vect = sqrt((accel_x * accel_x) + (accel_y * accel_y) + (accel_z * accel_z));
	accel_pitch = asin((double)accel_y/accel_vect) * (180 / M_PI);
	accel_roll = asin((double)accel_x / accel_vect) * -(180 / M_PI);
	accel_pitch -= 5.3;
	accel_roll -= 1.8;

	pitch_angle = (pitch_angle * .9996) + (accel_pitch * .0004);
	roll_angle = (roll_angle * .9996) + (accel_roll * .0004);
}

int main(void) {
	rcc_sys_clk_setup();
	rcc_io_enable(RCC_GPIOA);
	rcc_io_enable(RCC_GPIOB);
	rcc_io_enable(RCC_GPIOC);
	rcc_io_enable(RCC_GPIOD);
	rcc_io_enable(RCC_AFIO);
	timer_init();
	I2C.Init(I2C1, 300000);
	Serial1.Init(USART1, 115200, USART_MODE_RX);
	Serial2.Init(USART2, 230400, USART_MODE_TX);

	Serial2.println("Starting program");

	IMU.init(0x68);

	pitch_angle = 0;
	roll_angle = 0;
	yaw_angle = 0;

	
	pinMode(GPIOC, 13, OUTPUT);
	pinConfig(GPIOC, 13, GPO_PP);
	pinMode(GPIOB, 9, OUTPUT);
	pinConfig(GPIOB, 9, GPO_PP);

	calibrate_sensors(2000);

	Serial1.receiveIT(32);
	
	// Serial2.println(receiverData[0], 16);
	// Serial2.println(receiverData[1], 16);
	//Serial2.sendIT("test");
	

	loop_timer = micros();
	while(true) {
		Serial1.readSync(receiverData, 32, 0x20);
		ch1 = receiverData[2] | (receiverData[3] << 8);
		ch2 = receiverData[4] | (receiverData[5] << 8);
		ch3 = receiverData[6] | (receiverData[7] << 8);
		ch4 = receiverData[8] | (receiverData[9] << 8);
		ch5 = receiverData[10] | (receiverData[11] << 8);
		ch6 = receiverData[12] | (receiverData[13] << 8);
		Serial2.println(ch1, 10);
		Serial2.println(ch2, 10);
		Serial2.println(ch3, 10);
		Serial2.println(ch4, 10);
		Serial2.println(ch5, 10);
		Serial2.println(ch6, 10);
		Serial2.println("");

		//calculate_axes();
		double d = 1.234;
		
		Serial2.println(dtoa(str, d));
		//Serial2.println(roll_angle, 10);
		toggle(GPIOB, 9);
		
		while(micros() - loop_timer < LOOP_PERIOD); //250Hz refresh rate, T = 4ms = 4000us
		loop_timer = micros();
	}

	return 0;
}


void Reset_Handler() {
	main();
}

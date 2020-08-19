#include <main.h>
mpu9250 IMU;
adv_timer TIMER3;
int16_t gyro_data[3];
int16_t accel_data[3];
int16_t gyro_pitch, gyro_roll, gyro_yaw;
int16_t gyro_pitch_rate, gyro_roll_rate, gyro_yaw_rate;
int32_t gyro_x_cal, gyro_y_cal, gyro_z_cal, accel_vect;

double pitch_angle, roll_angle, yaw_angle;
double accel_pitch, accel_roll, accel_yaw;

uint8_t receiverData[32];
uint16_t ch1, ch2, ch3, ch4, ch5, ch6;

double pitch_setpoint, roll_setpoint, yaw_setpoint;
double pid_error_temp, last_pitch_error, last_roll_error, last_yaw_error;
double total_pitch_error, total_roll_error, total_yaw_error;
double pid_pitch_output, pid_roll_output, pid_yaw_output;

uint16_t motor1, motor2, motor3, motor4;

#define PID_MAX_PITCH 400
#define PID_MAX_ROLL 400
#define PID_MAX_YAW 400

#define PITCH_P_GAIN 1.0
#define PITCH_I_GAIN 1.0
#define PITCH_D_GAIN 1.0
#define ROLL_P_GAIN 1.0
#define ROLL_I_GAIN 1.0
#define ROLL_D_GAIN 1.0
#define YAW_P_GAIN 1.0
#define YAW_I_GAIN 1.0
#define YAW_D_GAIN 1.0

uint32_t loop_timer;
#define REFRESH_RATE 250 //main loop frequency and period
#define LOOP_PERIOD ((uint16_t)(1000000 / (double)REFRESH_RATE))

void read_imu_data() {
	IMU.read_gyro_data(gyro_data);
	IMU.read_accel_data(accel_data);
}

void read_receiver_data() {
	Serial1.readSync(receiverData, 32, 0x20); //read received data
	ch1 = receiverData[2] | (receiverData[3] << 8); //calculate receiver values
	ch2 = receiverData[4] | (receiverData[5] << 8);
	ch3 = receiverData[6] | (receiverData[7] << 8);
	ch4 = receiverData[8] | (receiverData[9] << 8);
	ch5 = receiverData[10] | (receiverData[11] << 8);
	ch6 = receiverData[12] | (receiverData[13] << 8);
}

void calibrate_sensors(int n) {
	gyro_x_cal = 0;
	gyro_y_cal = 0;
	gyro_z_cal = 0;

	for(int i = 0; i < n; i++) {
		IMU.read_gyro_data(gyro_data);
		IMU.read_accel_data(accel_data);
		gyro_x_cal += gyro_data[0];
		gyro_y_cal += gyro_data[1];
		gyro_z_cal += gyro_data[2];
		delay_ms(2);
	}

	gyro_x_cal /= n;
	gyro_y_cal /= n;
	gyro_z_cal /= n;
}

void calculate_autolevel() {
	read_imu_data();

	gyro_data[0] -= gyro_x_cal;
	gyro_data[1] -= gyro_y_cal;
	gyro_data[2] -= gyro_z_cal;

	gyro_pitch_rate = (gyro_pitch_rate * .8) + ((gyro_data[0] / GYRO_OUTPUT_DIV) * .2);
	gyro_roll_rate = (gyro_roll_rate * .8) + ((gyro_data[1] / GYRO_OUTPUT_DIV) * .2);
	gyro_yaw_rate = (gyro_yaw_rate * .8) + ((gyro_data[2] / GYRO_OUTPUT_DIV) * .2);

	read_receiver_data();
	pitch_setpoint = 0;
	roll_setpoint = 0;
	yaw_setpoint = 0;

	//pitch calculations
	if(PITCH_CHANNEL > 1508) pitch_setpoint = ((PITCH_CHANNEL - 1508) / 3.0);
	else if(PITCH_CHANNEL < 1492) pitch_setpoint = ((PITCH_CHANNEL - 1492) / 3.0);

	pid_error_temp = gyro_pitch_rate - pitch_setpoint;
	total_pitch_error += pid_error_temp;
	pid_pitch_output = (pid_error_temp * PITCH_P_GAIN) + (total_pitch_error * PITCH_I_GAIN) + ((pid_error_temp - last_pitch_error) * PITCH_D_GAIN);
	
	if(pid_pitch_output > PID_MAX_PITCH) pid_pitch_output = PID_MAX_PITCH;
	else if(pid_pitch_output < PID_MAX_PITCH * -1) pid_pitch_output = PID_MAX_PITCH * -1;
	last_pitch_error = pid_error_temp;

	//roll calculations
	if(ROLL_CHANNEL > 1508) roll_setpoint = ((ROLL_CHANNEL - 1508) / 3.0);
	else if(ROLL_CHANNEL < 1492) roll_setpoint = ((ROLL_CHANNEL - 1492) / 3.0);

	pid_error_temp = gyro_roll_rate - roll_setpoint;
	total_roll_error += pid_error_temp;
	pid_roll_output = (pid_error_temp * ROLL_P_GAIN) + (total_roll_error * ROLL_I_GAIN) + ((pid_error_temp - last_roll_error) * ROLL_D_GAIN);
	
	if(pid_roll_output > PID_MAX_ROLL) pid_roll_output = PID_MAX_ROLL;
	else if(pid_roll_output < PID_MAX_ROLL * -1) pid_roll_output = PID_MAX_ROLL * -1;
	last_roll_error = pid_error_temp;

	//yaw calculations
	if(YAW_CHANNEL > 1508) yaw_setpoint = ((YAW_CHANNEL - 1508) / 3.0);
	else if(YAW_CHANNEL < 1492) yaw_setpoint = ((YAW_CHANNEL - 1492) / 3.0);

	pid_error_temp = gyro_yaw_rate - yaw_setpoint;
	total_yaw_error += pid_error_temp;
	pid_yaw_output = (pid_error_temp * YAW_P_GAIN) + (total_yaw_error * YAW_I_GAIN) + ((pid_error_temp - last_yaw_error) * YAW_D_GAIN);

	if(pid_yaw_output > PID_MAX_YAW) pid_yaw_output = PID_MAX_YAW;
	else if(pid_yaw_output < PID_MAX_YAW * -1) pid_yaw_output = PID_MAX_YAW * -1;

	motor1 = THROTTLE_CHANNEL + pid_pitch_output - pid_roll_output + pid_yaw_output;
	motor2 = THROTTLE_CHANNEL - pid_pitch_output - pid_roll_output - pid_yaw_output;
	motor3 = THROTTLE_CHANNEL - pid_pitch_output + pid_roll_output + pid_yaw_output;
	motor4 = THROTTLE_CHANNEL + pid_pitch_output + pid_roll_output - pid_yaw_output;

	if(motor1 > 2000) motor1 = 2000;
	else if(motor1 < 1100) motor1 = 1100;
	if(motor2 > 2000) motor2 = 2000;
	else if(motor2 < 1100) motor2 = 1100;
	if(motor3 > 2000) motor3 = 2000;
	else if(motor3 < 1100) motor3 = 1100;
	if(motor4 > 2000) motor4 = 2000;
	else if(motor4 < 1100) motor4 = 1100;
}

void calculate_axes() {
	read_imu_data();
	gyro_data[0] -= gyro_x_cal;
	gyro_data[1] -= gyro_y_cal;
	gyro_data[2] -= gyro_z_cal;

	pitch_angle += (gyro_data[0] / (REFRESH_RATE * GYRO_OUTPUT_DIV));
	roll_angle += (gyro_data[1] / (REFRESH_RATE * GYRO_OUTPUT_DIV));
	pitch_angle += roll_angle * sin((gyro_data[2] * (M_PI / 180)) / (REFRESH_RATE * GYRO_OUTPUT_DIV));
	roll_angle -= roll_angle * sin((gyro_data[2] * (M_PI / 180)) / (REFRESH_RATE * GYRO_OUTPUT_DIV));

	accel_vect = sqrt((accel_data[0] * accel_data[0]) + (accel_data[1] * accel_data[1]) + (accel_data[2] * accel_data[2]));
	accel_pitch = asin((double)accel_data[1] / accel_vect) * (180 / M_PI);
	accel_roll = asin((double)accel_data[0] / accel_vect) * -(180 / M_PI);
	accel_pitch -= 0;
	accel_roll -= 0;

	pitch_angle = (pitch_angle * .9996) + (accel_pitch * .0004);
	roll_angle = (roll_angle * .9996) + (accel_roll * .0004);
}

int main(void) {
	rcc_sys_clk_setup();
	rcc_io_enable(RCC_GPIOA);
	rcc_io_enable(RCC_GPIOB);
	rcc_io_enable(RCC_GPIOC);
	rcc_io_enable(RCC_AFIO);

	timer_init();
	TIMER3.Init(TIM3, 5000);

	I2C.Init(I2C1, 300000);
	IMU.init(0x68);
	IMU.gyro_fs_select(GYRO_FS_RANGE);
	IMU.accel_fs_select(ACCEL_FS_RANGE);

	Serial1.Init(USART1, 115200, USART_MODE_RX);
	Serial2.Init(USART2, 230400, USART_MODE_TX);

	pitch_angle = 0;
	roll_angle = 0;
	yaw_angle = 0;

	pinMode(GPIOC, 13, OUTPUT); //leds
	pinConfig(GPIOC, 13, GPO_PP);
	pinMode(GPIOB, 12, OUTPUT);
	pinConfig(GPIOB, 12, GPO_PP);
	pinMode(GPIOB, 13, OUTPUT);
	pinConfig(GPIOB, 13, GPO_PP);

	writeHigh(GPIOB, 13);

	pinMode(GPIOA, 6, OUTPUT); //pwm outputs to motors
	pinConfig(GPIOA, 6, AFO_PP);
	pinMode(GPIOA, 7, OUTPUT);
	pinConfig(GPIOA, 7, AFO_PP);
	pinMode(GPIOB, 0, OUTPUT);
	pinConfig(GPIOB, 0, AFO_PP);
	pinMode(GPIOB, 1, OUTPUT);
	pinConfig(GPIOB, 1, AFO_PP);

	calibrate_sensors(2000);

	Serial1.receiveIT(); //start receiving data from transmitter

	TIMER3.OC1_Enable(OCM_PWM1);
	TIMER3.OC2_Enable(OCM_PWM1);
	TIMER3.OC3_Enable(OCM_PWM1);
	TIMER3.OC4_Enable(OCM_PWM1);

	TIMER3.Counter_Enable();

	loop_timer = millis();
	while(1) {
		read_receiver_data();
		read_imu_data();

		if(DISARM_MODE_CHANNEL > DISARM_DISABLE_RANGE_MIN && DISARM_MODE_CHANNEL < DISARM_DISABLE_RANGE_MAX) {
			writeLow(GPIOC, 13); //onboard led low = high

			//autolevel mode
			if(AUTOLEVEL_MODE_ENABLED && (AUTOLEVEL_MODE_CHANNEL > AUTOLEVEL_ENABLE_RANGE_MIN) && (AUTOLEVEL_MODE_CHANNEL < AUTOLEVEL_ENABLE_RANGE_MAX)) {
				

				gyro_data[0] -= gyro_x_cal;
				gyro_data[1] -= gyro_y_cal;
				gyro_data[2] -= gyro_z_cal;

				gyro_pitch_rate = (gyro_pitch_rate * .8) + ((gyro_data[0] / GYRO_OUTPUT_DIV) * .2);
				gyro_roll_rate = (gyro_roll_rate * .8) + ((gyro_data[1] / GYRO_OUTPUT_DIV) * .2);
				gyro_yaw_rate = (gyro_yaw_rate * .8) + ((gyro_data[2] / GYRO_OUTPUT_DIV) * .2);

				
				pitch_setpoint = 0;
				roll_setpoint = 0;
				yaw_setpoint = 0;

				//pitch calculations
				if(PITCH_CHANNEL > 1508) pitch_setpoint = ((PITCH_CHANNEL - 1508) / 3.0);
				else if(PITCH_CHANNEL < 1492) pitch_setpoint = ((PITCH_CHANNEL - 1492) / 3.0);

				pid_error_temp = gyro_pitch_rate - pitch_setpoint;
				total_pitch_error += pid_error_temp;
				pid_pitch_output = (pid_error_temp * PITCH_P_GAIN) + (total_pitch_error * PITCH_I_GAIN) + ((pid_error_temp - last_pitch_error) * PITCH_D_GAIN);
				
				if(pid_pitch_output > PID_MAX_PITCH) pid_pitch_output = PID_MAX_PITCH;
				else if(pid_pitch_output < PID_MAX_PITCH * -1) pid_pitch_output = PID_MAX_PITCH * -1;
				last_pitch_error = pid_error_temp;

				//roll calculations
				if(ROLL_CHANNEL > 1508) roll_setpoint = ((ROLL_CHANNEL - 1508) / 3.0);
				else if(ROLL_CHANNEL < 1492) roll_setpoint = ((ROLL_CHANNEL - 1492) / 3.0);

				pid_error_temp = gyro_roll_rate - roll_setpoint;
				total_roll_error += pid_error_temp;
				pid_roll_output = (pid_error_temp * ROLL_P_GAIN) + (total_roll_error * ROLL_I_GAIN) + ((pid_error_temp - last_roll_error) * ROLL_D_GAIN);
				
				if(pid_roll_output > PID_MAX_ROLL) pid_roll_output = PID_MAX_ROLL;
				else if(pid_roll_output < PID_MAX_ROLL * -1) pid_roll_output = PID_MAX_ROLL * -1;
				last_roll_error = pid_error_temp;

				//yaw calculations
				if(YAW_CHANNEL > 1508) yaw_setpoint = ((YAW_CHANNEL - 1508) / 3.0);
				else if(YAW_CHANNEL < 1492) yaw_setpoint = ((YAW_CHANNEL - 1492) / 3.0);

				pid_error_temp = gyro_yaw_rate - yaw_setpoint;
				total_yaw_error += pid_error_temp;
				pid_yaw_output = (pid_error_temp * YAW_P_GAIN) + (total_yaw_error * YAW_I_GAIN) + ((pid_error_temp - last_yaw_error) * YAW_D_GAIN);

				if(pid_yaw_output > PID_MAX_YAW) pid_yaw_output = PID_MAX_YAW;
				else if(pid_yaw_output < PID_MAX_YAW * -1) pid_yaw_output = PID_MAX_YAW * -1;

				motor1 = THROTTLE_CHANNEL + pid_pitch_output - pid_roll_output + pid_yaw_output;
				motor2 = THROTTLE_CHANNEL - pid_pitch_output - pid_roll_output - pid_yaw_output;
				motor3 = THROTTLE_CHANNEL - pid_pitch_output + pid_roll_output + pid_yaw_output;
				motor4 = THROTTLE_CHANNEL + pid_pitch_output + pid_roll_output - pid_yaw_output;

				if(motor1 > 2000) motor1 = 2000;
				else if(motor1 < 1100) motor1 = 1100;
				if(motor2 > 2000) motor2 = 2000;
				else if(motor2 < 1100) motor2 = 1100;
				if(motor3 > 2000) motor3 = 2000;
				else if(motor3 < 1100) motor3 = 1100;
				if(motor4 > 2000) motor4 = 2000;
				else if(motor4 < 1100) motor4 = 1100;

				TIMER3.setCCR1(1000);
				TIMER3.setCCR2(1250);
				TIMER3.setCCR3(1500);
				TIMER3.setCCR4(2000);
				TIMER3.Generate_Update();

			} //acro mode (no autoleveling)
			else if(ACRO_MODE_ENABLED && (ACRO_MODE_CHANNEL > ACRO_MODE_ENABLE_RANGE_MIN) && (ACRO_MODE_CHANNEL < ACRO_MODE_ENABLE_RANGE_MAX)) {

				TIMER3.setCCR1(1000);
				TIMER3.setCCR2(1250);
				TIMER3.setCCR3(1500);
				TIMER3.setCCR4(1750);
				TIMER3.Generate_Update();

				
			}

			while(millis() - loop_timer < 4); //250Hz refresh rate, T = 4ms = 4000us
		}
		else if(DISARM_MODE_CHANNEL > DISARM_ENABLE_RANGE_MIN && DISARM_MODE_CHANNEL < DISARM_ENABLE_RANGE_MAX) {
			toggle(GPIOC, 13);
			while(millis() - loop_timer < 500);
		}

		loop_timer = millis();
	}

	return 0;
}


void Reset_Handler() {
	main();
}

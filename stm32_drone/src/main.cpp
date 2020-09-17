#include <main.h>
mpu9250 IMU;
adv_timer TIMER3;
int16_t gyro_data[3];
int16_t accel_data[3];

double gyro_pitch_rate, gyro_roll_rate, gyro_yaw_rate;
int32_t gyro_x_cal, gyro_y_cal, gyro_z_cal, accel_vect;

bool startup;
double gyro_pitch, gyro_roll, gyro_yaw;
double accel_pitch, accel_roll, accel_yaw;
double pitch_angle, roll_angle, yaw_angle;

uint8_t receiverData[32];
uint16_t ch1, ch2, ch3, ch4, ch5, ch6;

float pitch_setpoint, roll_setpoint, yaw_setpoint;
float pid_error_temp, last_pitch_error, last_roll_error, last_yaw_error;
float pitch_error_sum, roll_error_sum, yaw_error_sum;
float pid_pitch_output, pid_roll_output, pid_yaw_output;

uint16_t motor1, motor2, motor3, motor4;
uint8_t last_arm_state;
#define ACCEL_PITCH_OFFSET 2
#define ACCEL_ROLL_OFFSET 0

#define PID_MAX_PITCH 400
#define PID_MAX_ROLL 400
#define PID_MAX_YAW 400

#define PITCH_P_GAIN 3
#define PITCH_I_GAIN 0
#define PITCH_D_GAIN 0
#define ROLL_P_GAIN 3
#define ROLL_I_GAIN 0
#define ROLL_D_GAIN 0
#define YAW_P_GAIN 1
#define YAW_I_GAIN 0
#define YAW_D_GAIN 0

#define MAX_TILT_ANGLE 30.0 //max tilt angle in autolevel mode

uint32_t loop_timer;
#define REFRESH_RATE 250 //main loop frequency

void read_imu_data() {
	IMU.read_gyro_data(gyro_data);
	IMU.read_accel_data(accel_data);
}

void calculate_angle_data() {
	//gyro values adjusted for noise
	gyro_data[0] -= gyro_x_cal; 
	gyro_data[1] -= gyro_y_cal;
	gyro_data[2] -= gyro_z_cal;

	//calculate angular rates based on previous and new values
	gyro_pitch_rate = (gyro_pitch_rate * 0.7) + ((gyro_data[0] / GYRO_OUTPUT_DIV) * 0.3);
	gyro_roll_rate = (gyro_roll_rate * 0.7) + ((gyro_data[1] / GYRO_OUTPUT_DIV) * 0.3);
	gyro_yaw_rate = (gyro_yaw_rate * 0.7) + ((gyro_data[2] / GYRO_OUTPUT_DIV) * 0.3);

	//calculate angle based on angular rate data
	gyro_pitch += (gyro_pitch_rate / REFRESH_RATE); 
	gyro_roll += (gyro_roll_rate / REFRESH_RATE);
	gyro_yaw += (gyro_yaw_rate / REFRESH_RATE);

	//adjust pitch and roll based on yaw angle ---------- these screw it up
	//gyro_pitch -= gyro_roll * sin((gyro_yaw * (M_PI / 180)));
	//gyro_pitch -= gyro_roll * sin(0);
	//gyro_roll += gyro_roll * sin((gyro_yaw * (M_PI / 180)));

	//Serial2.printd(gyro_pitch, 1);
	//Serial2.printd(gyro_roll, 1);

	//calculate angles using accelerometer data
	accel_vect = sqrt((accel_data[0] * accel_data[0]) + (accel_data[1] * accel_data[1]) + (accel_data[2] * accel_data[2]));
	if(abs(accel_data[1]) < accel_vect) {
		accel_pitch = asin((double)accel_data[1] / accel_vect) * (180 / M_PI);
	}
	if(abs(accel_data[0]) < accel_vect) {
		accel_roll = asin((double)accel_data[0] / accel_vect) * (-180 / M_PI);
	}

	accel_pitch -= ACCEL_PITCH_OFFSET;
	accel_roll -= ACCEL_ROLL_OFFSET;

	//calculate total angle based on gyro and accel data
	if(!startup) {
		pitch_angle = (gyro_pitch * .9996) + (accel_pitch * .0004);
		roll_angle = (gyro_roll * .9996) + (accel_roll * .0004);
	}
	else {
		pitch_angle = accel_pitch;
		roll_angle = accel_roll;
		startup = false;
	}
}

void pid_control() {
	//Autolevel mode - stick position correlates to absolute angle
	//calculate pitch angle setpoint based on stick position
	pitch_setpoint = 0;
	if(PITCH_CHANNEL > 1508) pitch_setpoint = (((PITCH_CHANNEL - 1508) / 3));
	else if(PITCH_CHANNEL < 1492) pitch_setpoint = (((PITCH_CHANNEL - 1492) / 3));

	//error is expected angle minus current angle
	pid_error_temp	= -gyro_pitch_rate - pitch_setpoint;
	//add current error to sum
	pitch_error_sum += pid_error_temp;
	//calculate motor outputs
	pid_pitch_output = (pid_error_temp * PITCH_P_GAIN) + (pitch_error_sum * PITCH_I_GAIN) + ((pid_error_temp - last_pitch_error) * PITCH_D_GAIN);
	last_pitch_error = pid_error_temp;

	//same thing for roll
	roll_setpoint = 0;
	if(ROLL_CHANNEL > 1508) roll_setpoint = (((ROLL_CHANNEL - 1508) / 3));
	else if(ROLL_CHANNEL < 1492) roll_setpoint = (((ROLL_CHANNEL - 1492) / 3));

	pid_error_temp = -gyro_roll_rate - roll_setpoint;
	roll_error_sum += pid_error_temp;
	pid_roll_output = (pid_error_temp * ROLL_P_GAIN) + (roll_error_sum * ROLL_I_GAIN) + ((pid_error_temp - last_roll_error) * ROLL_D_GAIN);
	last_roll_error = pid_error_temp;

	if(YAW_CHANNEL > 1508) yaw_setpoint = (((YAW_CHANNEL - 1508) / 3));
	else if(YAW_CHANNEL < 1492) yaw_setpoint = (((YAW_CHANNEL - 1492) / 3));

	pid_error_temp = -gyro_yaw_rate - yaw_setpoint;
	yaw_error_sum += pid_error_temp;
	pid_yaw_output = (pid_error_temp * YAW_P_GAIN) + (yaw_error_sum * YAW_I_GAIN) + ((pid_error_temp - last_yaw_error) * YAW_D_GAIN);
	last_yaw_error = pid_error_temp;


	motor1 = THROTTLE_CHANNEL - pid_pitch_output + pid_roll_output - pid_yaw_output;
	motor2 = THROTTLE_CHANNEL + pid_pitch_output + pid_roll_output + pid_yaw_output;
	motor3 = THROTTLE_CHANNEL + pid_pitch_output - pid_roll_output - pid_yaw_output;
	motor4 = THROTTLE_CHANNEL - pid_pitch_output - pid_roll_output + pid_yaw_output;
	/*motor1 = THROTTLE_CHANNEL;
	motor2 = THROTTLE_CHANNEL;
	motor3 = THROTTLE_CHANNEL;
	motor4 = THROTTLE_CHANNEL;*/

	if(motor1 < 1100) motor1 = 1100;
	else if(motor1 > 1800) motor1 = 1800;

	if(motor2 < 1100) motor2 = 1100;
	else if(motor2 > 1800) motor2 = 1800;

	if(motor3 < 1100) motor3 = 1100;
	else if(motor3 > 1800) motor3 = 1800;

	if(motor4 < 1100) motor4 = 1100;
	else if(motor4 > 1800) motor4 = 1800;
}

void read_receiver_data() {
	if(Serial1.readSync(receiverData, 32, 0x20)) { //read received data
		ch1 = receiverData[2] | (receiverData[3] << 8); //calculate receiver values
		ch2 = receiverData[4] | (receiverData[5] << 8);
		ch3 = receiverData[6] | (receiverData[7] << 8);
		ch4 = receiverData[8] | (receiverData[9] << 8);
		ch5 = receiverData[10] | (receiverData[11] << 8);
		ch6 = receiverData[12] | (receiverData[13] << 8);
	} 
	else {

	}
}

void calibrate_sensors(int n) {
	gyro_x_cal = 0;
	gyro_y_cal = 0;
	gyro_z_cal = 0;

	for(int i = 0; i < n; i++) {
		read_imu_data();
		gyro_x_cal += gyro_data[0];
		gyro_y_cal += gyro_data[1];
		gyro_z_cal += gyro_data[2];
		delay_ms(2);
	}

	gyro_x_cal /= n;
	gyro_y_cal /= n;
	gyro_z_cal /= n;
}

int main(void) {
	gyro_x_cal = 0;
	gyro_y_cal = 0;
	gyro_z_cal = 0;

	gyro_pitch = 0;
	gyro_roll = 0;
	gyro_yaw = 0;
	gyro_pitch_rate = 0;
	gyro_roll_rate = 0;
	gyro_yaw_rate = 0;


	pitch_error_sum = 0;
	last_pitch_error = 0;
	roll_error_sum = 0;
	last_roll_error = 0;
	yaw_error_sum = 0;
	last_yaw_error = 0;

	startup = true; 
	last_arm_state = 0;

	rcc_sys_clk_setup();
	rcc_io_enable(RCC_GPIOA);
	rcc_io_enable(RCC_GPIOB);
	rcc_io_enable(RCC_GPIOC);
	rcc_io_enable(RCC_AFIO);
	enableMCO(RCC_MCO_PLL_DIV_2);

	pinMode(GPIOC, 13, OUTPUT); //leds
	pinConfig(GPIOC, 13, GPO_PP);
	pinMode(GPIOB, 12, OUTPUT);
	pinConfig(GPIOB, 12, GPO_PP);
	pinMode(GPIOB, 13, OUTPUT);
	pinConfig(GPIOB, 13, GPO_PP);

	pinMode(GPIOA, 6, OUTPUT); //pwm outputs to motors
	pinConfig(GPIOA, 6, AFO_PP);
	pinMode(GPIOA, 7, OUTPUT);
	pinConfig(GPIOA, 7, AFO_PP);
	pinMode(GPIOB, 0, OUTPUT);
	pinConfig(GPIOB, 0, AFO_PP);
	pinMode(GPIOB, 1, OUTPUT);
	pinConfig(GPIOB, 1, AFO_PP);

	timer_init();

	TIMER3.Init(TIM3, 5000); //max timer count is 4000 + 1000us for some leeway
	TIMER3.OC1_Enable(OCM_PWM1);
	TIMER3.OC2_Enable(OCM_PWM1);
	TIMER3.OC3_Enable(OCM_PWM1);
	TIMER3.OC4_Enable(OCM_PWM1);

	I2C.Init(I2C1, 200000); //200k max
	IMU.init(0x68);
	IMU.gyro_fs_select(GYRO_FS_RANGE);
	IMU.accel_fs_select(ACCEL_FS_RANGE);

	Serial1.Init(USART1, 115200, USART_MODE_RX);
	Serial2.Init(USART2, 230400, USART_MODE_TX);
	Serial1.receiveIT();

	delay_ms(500);
	calibrate_sensors(1000);

	TIMER3.Generate_Update();
	TIMER3.Counter_Enable();
	TIMER3.setCCR1(1000);
	TIMER3.setCCR2(1000);
	TIMER3.setCCR3(1000);
	TIMER3.setCCR4(1000);

	loop_timer = millis();

	while(1) {
		read_receiver_data();
		read_imu_data();
		calculate_angle_data();
		//Serial2.printd(accel_roll, 2);

		if(DISARM_MODE_CHANNEL < DISARM_DISABLE_RANGE_MAX && DISARM_MODE_CHANNEL > DISARM_DISABLE_RANGE_MIN) {
			if(last_arm_state) { ///if already armed
				pid_control();
				TIMER3.setCCR1(motor1);
				TIMER3.setCCR2(motor2);
				TIMER3.setCCR3(motor3);
				TIMER3.setCCR4(motor4);
			}
			else if(!last_arm_state) { // if switching to armed state
				if(THROTTLE_CHANNEL > 1050) { //disable motors if throttle is high
					TIMER3.setCCR1(1000);
					TIMER3.setCCR2(1000);
					TIMER3.setCCR3(1000);
					TIMER3.setCCR4(1000);
				}
				else if(THROTTLE_CHANNEL < 1050) { //if throttle is low, then start pwm output
					last_arm_state = true;
				}
			}
		}
		else if(DISARM_MODE_CHANNEL < DISARM_ENABLE_RANGE_MAX && DISARM_MODE_CHANNEL > DISARM_ENABLE_RANGE_MIN) { //disable motors when disarmed
			last_arm_state = false;

			TIMER3.setCCR1(1000);
			TIMER3.setCCR2(1000);
			TIMER3.setCCR3(1000);
			TIMER3.setCCR4(1000);

			//reset variables
			pitch_error_sum = 0;
			last_pitch_error = 0;
			roll_error_sum = 0;
			last_roll_error = 0;
			yaw_error_sum = 0;
			last_yaw_error = 0;
		}

	/*	TIMER3.setCCR1(THROTTLE_CHANNEL); //for esc calibration
		TIMER3.setCCR2(THROTTLE_CHANNEL);
		TIMER3.setCCR3(THROTTLE_CHANNEL);
		TIMER3.setCCR4(THROTTLE_CHANNEL);*/

		TIMER3.Generate_Update();
		while(millis() - loop_timer < 4);
		loop_timer = millis();
	}
	
	return 0;
}


void Reset_Handler() {
	main();
}

void HardFault_Handler() {
	while(1) {
		for(int i = 0; i < 3; i++) {
			toggle(GPIOB, 12);
			delay_ms(250);
		}
		delay_ms(1000);
	}
}

void MemManage_Handler() {
	while(1) {
		for(int i = 0; i < 3; i++) {
			toggle(GPIOB, 12);
			delay_ms(250);
		}
		delay_ms(1000);
	}
}

void BusFault_Handler() {
	while(1) {
		for(int i = 0; i < 3; i++) {
			toggle(GPIOB, 12);
			delay_ms(250);
		}
		delay_ms(1000);
	}
}
#include <main.h>

int main(void) {
	//watchdog setup
	RCC->CSR |= 1; //enable LSI clock
	while(!(RCC->CSR & (1 << 1)));
	IWDG->KR = 0x5555; //Enable PR and RLR registers
	IWDG->PR = 0x0002; //0 prescaler
	IWDG->KR = 0xCCCC;

	rcc_sys_clk_setup();
	rcc_io_enable(RCC_GPIOA);
	rcc_io_enable(RCC_GPIOB);
	rcc_io_enable(RCC_GPIOC);
	rcc_io_enable(RCC_AFIO);

	timer_init();

	//on-board LEDs
	pinMode(GPIOB, 12, OUTPUT);
	pinConfig(GPIOB, 12, GPO_PP);
	pinMode(GPIOB, 13, OUTPUT);
	pinConfig(GPIOB, 13, GPO_PP);

	writeHigh(GPIOB, 12);
	writeHigh(GPIOB, 13);

	pinMode(GPIOB, 11, INPUT); //usart3 rx pin
	pinConfig(GPIOB, 11, INPUT_PUPD);
	writeHigh(GPIOB, 11);
	pinMode(GPIOA, 2, OUTPUT); //usart2 tx pin
	pinConfig(GPIOA, 2, AFO_PP);
	//pinMode(GPIOA, 9, OUTPUT);
	//pinConfig(GPIOA, 9, AFO_PP);
	//pinMode(GPIOA, 10, INPUT); //usart1 rx pin
	//pinConfig(GPIOA, 10, INPUT_PUPD);
	//writeHigh(GPIOA, 10);
	USART3_Struct.USARTx = USART3; //Receiver
	USART2_Struct.USARTx = USART2; //Serial
	//USART1_Struct.USARTx = USART1; //GPS
	Serial3.Init(&USART3_Struct, 115200, USART_MODE_RX);
	Serial2.Init(&USART2_Struct, 230400, USART_MODE_TX);
	//Serial1.Init(&USART1_Struct, 115200, USART_MODE_TXRX);

	//Serial1.print("$PUBX,41,1,0007,0003,115200,0*18\r\n"); //115200 baud setting
	//Serial1.print("$PUBX,41,1,0007,0003,19200,0*25\r\n"); //19200 baud setting
	//Serial1.receiveIT(); //can't use both interrupts at the same time
	Serial3.receiveIT();
	
	Serial2.println("Drone Startup");
	
	I2C.Init(I2C1, 300000);
	
	if(IMU.Init(0x68) == 0x68) {
		Serial2.println("IMU working");
	}
	else {
		Serial2.println("IMU returned incorrect value");
		while(1);
	}
	
	IMU.Gyro_FS_Select(GYRO_FS_RANGE);
	IMU.Accel_FS_Select(ACCEL_FS_RANGE);
	
	pinMode(GPIOA, 6, OUTPUT); //timer 3 channel 1-4 pins
	pinConfig(GPIOA, 6, AFO_PP);
	pinMode(GPIOA, 7, OUTPUT);
	pinConfig(GPIOA, 7, AFO_PP);
	pinMode(GPIOB, 0, OUTPUT);
	pinConfig(GPIOB, 0, AFO_PP);
	pinMode(GPIOB, 1, OUTPUT);
	pinConfig(GPIOB, 1, AFO_PP);
	TIM3_Struct.TIMx = TIM3;
	TIM3_Struct.PSC = F_CPU/1000000 - 1; //1 count = 1us
	TIM3_Struct.ARR = 5000;
	TIMER3.Init(&TIM3_Struct);
	TIMER3.OC1_Enable(OCM_PWM1);
	TIMER3.OC2_Enable(OCM_PWM1);
	TIMER3.OC3_Enable(OCM_PWM1);
	TIMER3.OC4_Enable(OCM_PWM1);
	
	calibrate_gyro(2000);
	
	//Make sure the motors don't spin immediately if the receiver is already armed on power-up
	Get_RX_Data();
	while(armCheck() == 1) {
		Get_RX_Data();
		IWDG->KR = 0xAAAA;
	}

	TIMER3.Generate_Update();
	TIMER3.Counter_Enable();
	TIMER3.setCCR1(1000);
	TIMER3.setCCR2(1000);
	TIMER3.setCCR3(1000);
	TIMER3.setCCR4(1000);

	loop_timer = millis();
	while(1) {
		calculate_angle_data();
		Get_RX_Data();
		IWDG->KR = 0xAAAA;

		//if armed
		if(armCheck() && !RX_OVERRIDE) {
			//if previously armed
			if(last_arm_state && !THROTTLE_OVERRIDE) {
				PID_Control();
			}
			//else if switching to arm from disarm
			else {
				//if throttle is high, don't arm
				if(THROTTLE_CHANNEL > 1050 || THROTTLE_OVERRIDE) {
					Serial2.println("Don't Arm");
					Serial2.println(THROTTLE_CHANNEL, 10);
					THROTTLE_OVERRIDE = true;
					last_arm_state = 0;
				}
				//if throttle is low, arm
				else if(THROTTLE_CHANNEL < 1050) {
					Serial2.println("Arming");
					last_arm_state = 1;
				}
			}
			
		}
		//else if disarmed
		else {
			//last arm state and throttle override to 0
			last_arm_state = 0;
			THROTTLE_OVERRIDE = false;

			//stop motors
			MOTOR_S1 = 1000;
			MOTOR_S2 = 1000;
			MOTOR_S3 = 1000;
			MOTOR_S4 = 1000;

			//reset PID variables
			pitch_integrator = 0;
			roll_integrator = 0;
			yaw_integrator = 0;
			prev_pitch_error = 0;
			prev_roll_error = 0;
			prev_yaw_error = 0;
		}

		TIMER3.setCCR1(MOTOR_S1);
		TIMER3.setCCR2(MOTOR_S2);
		TIMER3.setCCR3(MOTOR_S3);
		TIMER3.setCCR4(MOTOR_S4);
		
		TIMER3.Generate_Update();
		while(millis() - loop_timer < 4);
		loop_timer = millis();
	};
	
	return 0;
}

void calibrate_gyro(uint16_t n) {
	gyro_x_cal = 0;
	gyro_y_cal = 0;
	gyro_z_cal = 0;

	for(int i = 0; i < n; i++) {
		IMU.Read_Gyro_Data(gyro_data);
		Serial2.println("Test");
		gyro_x_cal += gyro_data[0];
		gyro_y_cal += gyro_data[1];
		gyro_z_cal += gyro_data[2];
	}

	gyro_x_cal /= n;
	gyro_y_cal /= n;
	gyro_z_cal /= n;
}

void calculate_angle_data() {
	IMU.Read_Gyro_Data(gyro_data);
	IMU.Read_Accel_Data(accel_data);

	gyro_data[0] -= gyro_x_cal;
	gyro_data[1] -= gyro_y_cal;
	gyro_data[2] -= gyro_z_cal;

	gyro_pitch_rate = (gyro_pitch_rate * 0.7) + ((gyro_data[0] / GYRO_OUTPUT_DIV) * 0.3);
	gyro_roll_rate = (gyro_roll_rate * 0.7) + ((gyro_data[1] / GYRO_OUTPUT_DIV) * 0.3);
	gyro_yaw_rate = (gyro_yaw_rate * 0.7) + ((gyro_data[2] / GYRO_OUTPUT_DIV) * 0.3);

	pitch_angle += (gyro_pitch_rate / REFRESH_RATE);
	roll_angle += (gyro_roll_rate / REFRESH_RATE);
	yaw_angle += (gyro_yaw_rate / REFRESH_RATE);

	accel_vect = sqrt((accel_data[0] * accel_data[0]) + (accel_data[1] * accel_data[1]) + (accel_data[2] * accel_data[2]));
	// if(abs(accel_data[1]) < accel_vect) {
	accel_pitch = asin((double)accel_data[1] / accel_vect) * (180 / M_PI);
	// }
	// if(abs(accel_data[0]) < accel_vect) {
	accel_roll = asin((double)accel_data[0] / accel_vect) * (-180 / M_PI);
	// }

	if(startup_read) {
		pitch_angle = (pitch_angle * (1 - FILTER_ALPHA)) + (accel_pitch * FILTER_ALPHA);
		roll_angle = (roll_angle * (1 - FILTER_ALPHA)) + (accel_roll * FILTER_ALPHA);
	}
	else {
		pitch_angle = accel_pitch;
		roll_angle = accel_roll;

		startup_read = true;
	}

	if(1) {
		//Serial2.printd(1.0, 1);
		//Serial2.printd(roll_angle, 1);
		//Serial2.printd(yaw_angle, 1);
	}
}

/*
Get the values from the receiver. If no signal detected, override the motor outputs.
*/
void Get_RX_Data() {
	if(Serial3.readSync(rx_data, 32, 0x20)) {
		rx_fail_count = 0;
		RX_OVERRIDE = false;

		ch1 = rx_data[2] | (rx_data[3] << 8); //calculate receiver values
		ch2 = rx_data[4] | (rx_data[5] << 8);
		ch3 = rx_data[6] | (rx_data[7] << 8);
		ch4 = rx_data[8] | (rx_data[9] << 8);
		ch5 = rx_data[10] | (rx_data[11] << 8);
		ch6 = rx_data[12] | (rx_data[13] << 8);

		if(0) {
			Serial2.println(ch1, 10);
		}
	}
	else {
		if(++rx_fail_count == 3) {
			//Serial2.println("RX Fail");
			rx_fail_count = 0;
			RX_OVERRIDE = true;
		}
	}
}

/*
Control the motor output signals based on rotational data from the gyroscope
*/
void PID_Control() {
	pitch_output = 0;
	roll_output = 0;
	yaw_output = 0;

	//compare the receiver input to the gyroscope angular rates
	//max angular rate is 500/16 = 31.25 deg
	pitch_setpoint = (PITCH_CHANNEL - 1500) / 16;
	roll_setpoint = (ROLL_CHANNEL - 1500) / 16;
	yaw_setpoint = (YAW_CHANNEL - 1500) / 16;

	Serial2.println((int32_t)yaw_setpoint, 10);
	
	/*
	error
	negative gyro rate because directions are reversed
	*/
	pitch_error = pitch_setpoint - (-gyro_pitch_rate);
	roll_error = roll_setpoint - gyro_roll_rate;
	yaw_error = yaw_setpoint - gyro_yaw_rate;

	//proportional
	pitch_output += PITCH_KP * pitch_error;
	roll_output += ROLL_KP * roll_error;
	yaw_error += YAW_KP * yaw_error;

	//integral
	pitch_integrator = pitch_integrator + (.5f * PITCH_KI * (1 / REFRESH_RATE) * (pitch_error + prev_pitch_error));
	pitch_output += pitch_integrator;
	roll_integrator = roll_integrator + (.5f * ROLL_KI * (1 / REFRESH_RATE) * (roll_error + prev_roll_error));
	roll_output += roll_integrator;
	yaw_integrator = yaw_integrator + (.5f * YAW_KI * (1 / REFRESH_RATE) * (yaw_error + prev_yaw_error));
	yaw_output += yaw_integrator;

	//derivative
	pitch_output += PITCH_KD * (pitch_error - prev_pitch_error);
	roll_output += ROLL_KD * (roll_error - prev_roll_error);
	yaw_output += YAW_KD * (yaw_error - prev_yaw_error);

	//adding everything together for motor output signals
	MOTOR_S1 = THROTTLE_CHANNEL + pitch_output - roll_output + yaw_output;
	MOTOR_S2 = THROTTLE_CHANNEL - pitch_output - roll_output - yaw_output;
	MOTOR_S3 = THROTTLE_CHANNEL - pitch_output + roll_output + yaw_output;
	MOTOR_S4 = THROTTLE_CHANNEL + pitch_output + roll_output - yaw_output;

	//clamping
	if(MOTOR_S1 < MIN_MOTOR_OUTPUT) MOTOR_S1 = MIN_MOTOR_OUTPUT;
	else if(MOTOR_S1 > MAX_MOTOR_OUTPUT) MOTOR_S1 = MAX_MOTOR_OUTPUT;
	if(MOTOR_S2 < MIN_MOTOR_OUTPUT) MOTOR_S2 = MIN_MOTOR_OUTPUT;
	else if(MOTOR_S2 > MAX_MOTOR_OUTPUT) MOTOR_S2 = MAX_MOTOR_OUTPUT;
	if(MOTOR_S3 < MIN_MOTOR_OUTPUT) MOTOR_S3 = MIN_MOTOR_OUTPUT;
	else if(MOTOR_S3 > MAX_MOTOR_OUTPUT) MOTOR_S3 = MAX_MOTOR_OUTPUT;
	if(MOTOR_S4 < MIN_MOTOR_OUTPUT) MOTOR_S4 = MIN_MOTOR_OUTPUT;
	else if(MOTOR_S4 > MAX_MOTOR_OUTPUT) MOTOR_S4 = MAX_MOTOR_OUTPUT;

	//exit
	prev_pitch_error = pitch_error;
	prev_roll_error = roll_error;
	prev_yaw_error = yaw_error;

	//Serial2.printd(pitch_angle, 1);
	//Serial2.printd(gyro_pitch_rate, 1);
	//Serial2.printd(yaw_output, 1);
}

//Return 1 if armed, 0 if disarmed
uint8_t armCheck() {
	//if in the disarm range, return 0
	if(DISARM_MODE_CHANNEL > DISARM_ENABLE_RANGE_MIN && DISARM_MODE_CHANNEL < DISARM_ENABLE_RANGE_MAX) {
		return 0;
	}
	//else if in the arm range, return 1
	else if(DISARM_MODE_CHANNEL > DISARM_DISABLE_RANGE_MIN && DISARM_MODE_CHANNEL < DISARM_DISABLE_RANGE_MAX) {
		return 1;
	}
}

void Reset_Handler() {
	//initialize static variables to zero
	for(char *bss_ptr = &_sbss; bss_ptr < &_ebss;) {
		*bss_ptr++ = 0;
	}

	//Copy initial values from text to data
	char *text_ptr = &_etext;
	char *data_ptr = &_sdata;

	if(text_ptr != data_ptr) {
		for(;data_ptr < &_edata;) {
			*data_ptr++ = *text_ptr++;
		}
	}

	main();

	while(1);
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
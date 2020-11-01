#ifndef MAIN_H
#define MAIN_H

#include <boards.h>
#include <interrupt.h>
#include <configuration.h>
#include <rcc.h>
#include <usart.h>
#include <timer.h>
#include <adv_timer.h>
#include <ssd1306.h>
#include <mpu9250.h>
#include <math.h>
#include <mpu6050.h>
#include <at93c66b.h>
#include <spi.h>

#define M_PI (atan(1)*4)

extern char _sbss;
extern char _ebss;
extern char _etext;
extern char _sdata;
extern char _edata;

mpu6050 IMU;
at93c66b EEPROM;
SPI_Struct SPI1_Struct;
USART_Struct USART3_Struct;
USART_Struct USART2_Struct;
USART_Struct USART1_Struct;
adv_timer TIMER3;
Adv_Timer_Struct TIM3_Struct;

//IMU data
int16_t gyro_data[3];
int16_t accel_data[3];
int32_t gyro_x_cal, gyro_y_cal, gyro_z_cal, accel_vect;

//Angle data
double gyro_pitch_rate, gyro_roll_rate, gyro_yaw_rate;
double pitch_angle, roll_angle, yaw_angle;
double accel_pitch, accel_roll;

//Receiver data
uint8_t rx_data[32];
uint16_t ch1, ch2, ch3, ch4, ch5, ch6;
uint8_t rx_fail_count;

//PID variables
float pitch_setpoint, roll_setpoint, yaw_setpoint;
float pitch_error, roll_error, yaw_error;
float pitch_integrator, roll_integrator, yaw_integrator;
float prev_pitch_error, prev_roll_error, prev_yaw_error;
float pitch_output, roll_output, yaw_output;

//Loop and counter variables
uint16_t MOTOR_S1, MOTOR_S2, MOTOR_S3, MOTOR_S4;
uint32_t loop_timer;
float T_MILLIS; //time between IMU measurements in milliseconds

//Logic variables
bool startup_read; //whether to use accelerometer or gyroscope measurements when calculating angle
uint8_t last_arm_state;
bool RX_OVERRIDE;
bool THROTTLE_OVERRIDE;

//Functions
void calibrate_gyro(uint16_t n);
void calculate_angle_data();
void Get_RX_Data();
void PID_Control();
uint8_t armCheck();

#endif
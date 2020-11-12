#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//Select board and main clock frequency
#define BOARD_F103 //select which board from boards.h
#define F_CPU 64000000UL //cpu frequency max 48MHz

#define PLL_CLK_SRC 1 //0: high speed internal/2		1: high speed external/2

//main loop frequency in Hz
#define REFRESH_RATE ((double)(250))

//complimentary filter accelerometer proportion
#define FILTER_ALPHA .05

//Motor limits
#define MIN_MOTOR_OUTPUT 1100
#define MAX_MOTOR_OUTPUT 1900
#define MAX_INTEGRATOR 100
#define MIN_INTEGRATOR -100

//PID gain values
#define PITCH_KP 4
#define ROLL_KP 4
#define YAW_KP 5
#define PITCH_KI 2
#define ROLL_KI 2
#define YAW_KI 1
#define PITCH_KD 20
#define ROLL_KD 20
#define YAW_KD 0

//IMU config
#define GYRO_FS_RANGE GYRO_FS_2000dps
#define GYRO_OUTPUT_DIV (131 / pow(2, GYRO_FS_RANGE))
#define ACCEL_FS_RANGE ACCEL_FS_8g
#define ACCEL_OUTPUT_DIV (16384 / pow(2, ACCEL_FS_RANGE))

//Receiver channels
#define ROLL_CHANNEL ch1
#define PITCH_CHANNEL ch2
#define THROTTLE_CHANNEL ch3
#define YAW_CHANNEL ch4

//Flight modes and settings
#define DISARM_MODE_CHANNEL ch5
#define DISARM_ENABLE_RANGE_MIN 500
#define DISARM_ENABLE_RANGE_MAX 1500
#define DISARM_DISABLE_RANGE_MIN 1500
#define DISARM_DISABLE_RANGE_MAX 2500

#define ANGLE_MODE_ENABLED true
#define ANGLE_MODE_CHANNEL ch6
#define ANGLE_ENABLE_RANGE_MIN 750
#define ANGLE_ENABLE_RANGE_MAX 1250
#define ANGLE_MODE_MAX_ANGLE 30

#define ACRO_TRAINER_MODE_ENABLED true
#define ACRO_TRAINER_MODE_CHANNEL ch6
#define ACRO_TRAINER_MODE_ENABLE_RANGE_MIN 1250
#define ACRO_TRAINER_MODE_ENABLE_RANGE_MAX 1750

#define ACRO_MODE_ENABLED true
#define ACRO_MODE_CHANNEL ch6
#define ACRO_MODE_ENABLE_RANGE_MIN 1750
#define ACRO_MODE_ENABLE_RANGE_MAX 2250

#endif
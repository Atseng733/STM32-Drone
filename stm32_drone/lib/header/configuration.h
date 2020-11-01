#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define BOARD_F103 //select which board from boards.h
#define F_CPU 64000000UL //cpu frequency max 48MHz

#define PLL_CLK_SRC 1 //0: high speed internal/2		1: high speed external/2

#define GYRO_FS_RANGE GYRO_FS_500dps
#define GYRO_OUTPUT_DIV (131 / pow(2, GYRO_FS_RANGE))
#define ACCEL_FS_RANGE ACCEL_FS_8g
#define ACCEL_OUTPUT_DIV (16384 / pow(2, ACCEL_FS_RANGE))

#define ROLL_CHANNEL ch1
#define PITCH_CHANNEL ch2
#define THROTTLE_CHANNEL ch3
#define YAW_CHANNEL ch4

#define DISARM_MODE_ENABLED true //arm and disarm switch
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
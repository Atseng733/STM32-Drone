#ifndef MAIN_H
#define MAIN_H

#include <boards.h>
#include <interrupt.h>
#include <configuration.h>
#include <rcc.h>
#include <usart.h>
#include <timer.h>
#include <ssd1306.h>
#include <mpu9250.h>
#include <math.h>

#define M_PI (atan(1)*4)

void read_sensor_data();
void calibrate_sensors();

#endif
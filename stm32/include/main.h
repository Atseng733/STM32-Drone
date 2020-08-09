#ifndef MAIN_H
#define MAIN_H

#include <boards.h>
#include <interrupt.h>
#include <configuration.h>
#include <rcc.h>
#include <f1_gpio.h>
#include <usart.h>

void read_sensor_data();
void calibrate_sensors();

#endif
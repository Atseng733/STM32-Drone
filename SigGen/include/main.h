#ifndef MAIN_H
#define MAIN_H

#include <m328io.h>
#include <avr_io.h>
#include <timer.h>
#include <usart.h>
#include <debug.h>
#include <ssd1306.h>
#include <ad9833.h>
#include <Rotary.h>
#include <stdlib.h>

#define MAX_FREQ 15000000L
#define MIN_FREQ 0L
#define funcButton 7
double convertFreq();
void setDisplay();
void checkButtons();
void encChange();

unsigned long lastFuncPress = 0;
unsigned char funcState = 0;
unsigned char lastFuncState = 0;

#define rotaryButton 4
unsigned long lastRotaryPress;
unsigned char rotaryState = 0;
unsigned char lastRotaryState = 0;

char dispStr[8];
unsigned char currentScreen = 1;
char *freqMag[] = {" ", "k", "M"};
char *waveform[] = {"SIN", "TRI", "SQR"};
unsigned int stepSize[] = {1, 100, 10000};
unsigned char currentStep = 2;
unsigned char currentFreqMag = 1;
unsigned char currentWaveform = 0;
unsigned int decFreq = 0;
unsigned int whlFreq = 1;
long freqVal = 1000;
volatile bool updateDisplay = false;
spi SPI;
Rotary encoder(2, 3);
ad9833 sigGen(10, MAX_FREQ);
ssd1306 display(0x3C);
#endif
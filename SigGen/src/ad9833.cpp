#include <ad9833.h>
#include <usart.h>
#include <stdlib.h>
ad9833::ad9833(unsigned char _FSYNC, unsigned long _mclk) {
	  FSYNC = _FSYNC;
	  pinMode(FSYNC, OUTPUT);     // Set FSYNC pin as input
	  mclk = _mclk;               // Set the oscillator used, for example 24MHz
	  controlRegister = 0x2000;   // Default control register : FREQ0, PHASE0, Sine
	  fqRegister = 0x4000;        // Default frequency register is 0
	  pRegister = 0xC000;         // Default phase register is 0
	  SPI.begin();                // Initialise the SPI BUS
	  SPI.setMode(2); // Set SPI in mode2, this should be moved in
	  // methods when SPI.transfer is called in case you
	  // have multiple devices using the SPI bus
}

void ad9833::writeData(int data) {
	digitalWrite(FSYNC, LOW);
	SPI.transfer8((char)(data >> 8));
	SPI.transfer8((char)(data & 0xFF));
	digitalWrite(FSYNC, HIGH);
}
char str3[10];
void ad9833::setFreq(unsigned long _freq) {
	unsigned long freqReg;
	
	if(_freq < 0) {
		freqReg = 0;
		freq = 0;
	}
	else if(_freq > mclk) {
		freqReg = pow(2, 28) - 1;
		freq = mclk/2;
	}
	else {
		freq = _freq;
		freqReg = (freq * pow(2, 28)) / mclk;
	}
	
	int LSW = ((int)(freqReg & 0x3FFF)) | fqRegister;
	int MSW = ((int)(freqReg >> 14)) | fqRegister;
	
	writeData(LSW);
	writeData(MSW);
	//print("set frequency to ");
	//print(ltoa(_freq, str3, 10));
}

unsigned long ad9833::getFreq() {
	return freq;
}

void ad9833::setPhase(int _phase) {
	// Phase can't be negative
	if (_phase < 0) {
		phase = 0;
	}
	// Phase maximum is 2^12
	else if (_phase >= 4096) {
		phase = 4096 - 1;
	}
	// If all is good, set the new phase value
	else {
		phase = _phase;
	}
	
	int phaseData = phase | pRegister;
	writeData(phaseData);
}

int ad9833::getPhase() {
	return phase;
}

void ad9833::setCtrlReg(unsigned long _controlRegister) {
	controlRegister = _controlRegister & 0x3FFF;
	writeCtrlReg();
}

int ad9833::getCtrlReg() {
	return controlRegister;
}

void ad9833::writeCtrlReg() {
	writeData(controlRegister);
}

void ad9833::sleep(int s) {
	switch (s) {

		case 0: {
			controlRegister &= 0xFF3F; // No power-down: D7-0 and D6-0
		} break;

		case 1: {
			controlRegister &= 0xFF7F; // DAC powered down: D7-0 and D6-1
			controlRegister |= 0x0040;
		} break;

		case 2: {
			controlRegister &= 0xFFBF; // Internal clock disabled: D7-1 and D6-0
			controlRegister |= 0x0080;
		} break;

		case 3: {
			controlRegister |=
			0x00C0; // Both DAC powered down and internal clock disabled
		} break;
	}
	// Update the control register
	writeCtrlReg();
}

void ad9833::reset(int r) {
	if (r == 0) {
		controlRegister &= 0xFEFF; // Set D8 to 0
	}

	else if (r == 1) {
		controlRegister |= 0x0100; // Set D8 to 1
	}
	writeCtrlReg();
}

void ad9833::mode(int m) {
	switch (m) {
		case 0: {
			controlRegister &= 0xFFDD; // Output sine: D5-0 and D1-0
		} break;
		case 1: {
			controlRegister &= 0xFFDF; // Output triangle: D5-0 and D1-1
			controlRegister |= 0x0002;
		} break;
		case 2: {
			controlRegister &= 0xFFFD; // Output clock (rectangle): D5-1 and D1-0
			controlRegister |= 0x0020;
		} break;
	}
	writeCtrlReg();
}

void ad9833::setFPRegister(int r) {
	if (r == 0) {
		controlRegister &= 0xF3FF; // Set D11 and D10 in control register to 0
		fqRegister = 0x4000; // Set D15 to 0 and D14 to 1 in a variable that will
		// later choose the FREQ0 register
		pRegister =
		0xC000; // Set D15 to 1 and D14 to 1 and D13 to 0 for the PHASE register
		} else if (r == 1) {
		controlRegister |= 0x0C00; // Set D11 and D10 in control register to 1
		fqRegister = 0x8000; // Set D15 to 1 and D14 to 0 in a variable that will
		// later choose the FREQ1 register
		pRegister =
		0xD000; // Set D15 to 1 and D14 to 1 and D13 to 1 for the PHASE register
	}
	writeCtrlReg();
}

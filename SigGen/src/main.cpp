#include <main.h>

int main() {
	display.begin();
	display.setTextSize(2);
	display.setCursor(35,0);
	display.print("Signal");
	display.setCursor(20, 2);
	display.print("Generator");
	display.display();
	delay(1000);
	display.clearDisplay();
	display.display();
	setDisplay();
	
	attachExInterrupt(2, encChange, CHANGE);
	attachExInterrupt(3, encChange, CHANGE);
	pinMode(rotaryButton, INPUT_PULLUP);
	pinMode(funcButton, INPUT_PULLUP);
	
	sigGen.reset(1);
	sigGen.setFreq(1000);
	sigGen.reset(0);
	
	while(1) 
	{
		if(updateDisplay) 
		{
			setDisplay();
			updateDisplay = false;
		}
		
		checkButtons();
	}
}

void setDisplay() {
	switch(currentScreen) {
		case 1:
		display.clearDisplay();
		display.setCursor(0,0);
		display.print(dtostrf(convertFreq(), 7, 3, dispStr));
		display.setCursor(84, 0);
		display.print(freqMag[currentFreqMag]);
		display.setCursor(95, 0);
		display.print("Hz");
		display.setCursor(0, 2);
		display.print(utoa(stepSize[currentStep], dispStr, 10));
		display.setCursor(84, 2);
		display.print(waveform[currentWaveform]);
		display.display();
		break;
	}
}

double convertFreq() {
	double d;
	if(currentFreqMag == 0) {
		d = (double)(freqVal);
	}
	else {
		d = (double)(freqVal/pow(10,currentFreqMag*3));
	}
	
	return d;
}

void encChange() {
	unsigned char state = encoder.process();
	if(state == DIR_CW) 
	{
		freqVal += stepSize[currentStep];
		if(freqVal > MAX_FREQ) {
			freqVal = MAX_FREQ;
			currentFreqMag = 2;
		}
		/*else if(freqVal - stepSize[currentStep] < 1000 && currentStep != 2)
		{
			currentStep ++;
		}*/
	}
	else if(state == DIR_CCW)
	{
		if(freqVal == 0 | freqVal - stepSize[currentStep] == 0) {
			freqVal = MIN_FREQ;
		}
		else if(freqVal - stepSize[currentStep] < 0) {
			freqVal = stepSize[currentStep]/10 - 1;
			currentStep --;
		}
		else
		{
			freqVal -= stepSize[currentStep];
		}
		
		if(freqVal < MIN_FREQ) {
			freqVal = MIN_FREQ;
			currentFreqMag = 0;
		}
		
	}
	
	if(freqVal/pow(10, 6) >= 1) {
		currentFreqMag = 2;
	}
	else if(freqVal/pow(10, 3) >= 1) {
		currentFreqMag = 1;
	}
	else currentFreqMag = 0;
	sigGen.setFreq(freqVal);
	updateDisplay = true;
}

ISR(INT0_vect) {
	encChange();
}
ISR(INT1_vect) {
	encChange();
}

void checkButtons() {
	if(lastRotaryPress - millis() > 100) 
	{
		rotaryState = digitalRead(rotaryButton);
		if(rotaryState != lastRotaryState) 
		{
			lastRotaryState = rotaryState;
			if(rotaryState == 0) 
			{
				switch(currentScreen) 
				{
					case 1:
					if(++currentWaveform > 2) 
					{
						currentWaveform = 0;
					}
					sigGen.mode(currentWaveform);
					break;
				}
				updateDisplay = true;
			}
		}
		lastRotaryPress = millis();
	}
	
	if(lastFuncPress - millis() > 100)
	{
		funcState = digitalRead(funcButton);
		if(funcState != lastFuncState)
		{
			lastFuncState = funcState;
			if(funcState == 0)
			{
				switch(currentScreen)
				{
					case 1:
					if(++currentStep > 2)
					{
						currentStep = 0;
					}
				}
				updateDisplay = true;
			}
		}
		lastFuncPress = millis();
	}
}
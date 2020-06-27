#include "twi.h"
#include <usart.h>
#include <stdlib.h>
char str[10];

void twi_init(){
	print("Setting TWBR to "); print(utoa((unsigned int)(TWI_BAUD), str, 16));
	TWBR = TWI_BAUD;	//	Baud rate is set by calculating
	
	//print(utoa((unsigned int)(TWI_BAUD), str, 16));
	TWCR = (1<<TWEN);	//Enable I2C
	TWSR = 0x00;		//Prescaler set to 1
}
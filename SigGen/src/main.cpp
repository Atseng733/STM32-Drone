#include <main.h>
#include <twi.h>
#include <stdio.h>

ssd1306 display;

int main() {
	TWI_Init();
	print("init ");
	TWI_Start();
	print("start ");
	TWI_Send(0x3C << 1);
	print("send slave address ");
	TWI_Send(0x00);
	print("send control register ");
	TWI_Send(0xAF);
	print("send data");
	TWI_Stop();
	print("stop");
	display.begin(0x3C);
	display.print("koalas are beautiful creatures");
	display.display();
	delay(2000);
	display.clearDisplay();
	display.print("are they");
	display.display();
	while(1);
}
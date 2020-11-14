#include <ssd1306.h>

uint8_t ssd1306::get_addr() {
	return addr;
}

void ssd1306::ssd1306_command(uint8_t c)
{
	// I2C
	uint8_t control = 0x00;   // Co = 0, D/C = 0
	I2C.Write(addr, control, c); //Set direction
}

void ssd1306::begin(uint8_t sAddr)
{
	addr = sAddr;
	CURSOR_LOC = 0;
	text_size = 1;
	// Init sequence
	ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
	ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
	ssd1306_command(0x80);                                  // the suggested ratio 0x80

	ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
	ssd1306_command(SSD1306_LCDHEIGHT - 1);

	ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
	ssd1306_command(0x0);                                   // no offset
	ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0
	ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
	ssd1306_command(0x14);
	ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
	ssd1306_command(0x00);                                  // 0x0 act like ks0108
	ssd1306_command(SSD1306_SEGREMAP | 0x1);
	ssd1306_command(SSD1306_COMSCANDEC);

	ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
	ssd1306_command(0x02);
	ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
	ssd1306_command(0x8F);


	ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
	ssd1306_command(0xF1);
	ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
	ssd1306_command(0x40);
	ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
	ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6

	ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

	ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
	clearDisplay();
}


void ssd1306::display(void)
{
	ssd1306_command(SSD1306_COLUMNADDR);
	ssd1306_command(0);   // Column start address (0 = reset)
	ssd1306_command(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)

	ssd1306_command(SSD1306_PAGEADDR);
	ssd1306_command(0); // Page start address (0 = reset)
	ssd1306_command(3); // Page end address

	I2C.Write(addr, 0x40, ssd1306_buffer, 512);
}

void ssd1306::clearDisplay() {
	ssd1306_command(SSD1306_COLUMNADDR);
	ssd1306_command(0);
	ssd1306_command(SSD1306_LCDWIDTH-1); // Column end address (127 = reset)
	
	ssd1306_command(SSD1306_PAGEADDR);
	ssd1306_command(0); // Page start address (0 = reset)
	ssd1306_command(3); // Page end address

	for(int i = 0; i < 512; i++) {
		ssd1306_buffer[i] = 0x00;
	}
	setCursor(0, 0);
}

void ssd1306::print(char* str) {
	int memloc;		//location in font table
	uint8_t k = 0;
	
	uint8_t cf;		//size 2 text variables
	uint8_t cb;
	uint8_t b1;
	uint8_t b2;
	
	switch(text_size) {
		case 1:
		while(str[k] !=  0) {
			memloc = (str[k] - 32) * 5;
			for(int j = 0; j < 5; j++) {
				if(CURSOR_LOC < 512) {
					//ssd1306_buffer[CURSOR_LOC] = pgm_read_byte(&(ASCII5x7[0]) + memloc + j);
					ssd1306_buffer[CURSOR_LOC] = ASCII5x7[memloc + j];
					CURSOR_LOC++;
				}
			}
			k++;
		}
		break;
		
		
		case 2:
		while(str[k] !=  0x00) {
			memloc = (str[k] - 32) * 5;
			for(int j = 0; j < 5; j++) {
				if(CURSOR_LOC < 512) {
					//cf = pgm_read_byte(&(ASCII5x7[0]) + memloc + j);
					cf = ASCII5x7[memloc + j];
					cb = cf & 0x0F;
					cf >>= 4;
					for(uint8_t l = 0; l < 4; l++) {
						if(cf & 0x08) {
							b1 |= 0x03;
						}
						else {
							b1 &= ~(0x03);
						}
						
						if(cb & 0x08) {
							b2 |= 0x03;
						}
						else {
							b2 &= ~(0x03);
						}
						if(l != 3) {
							b1 <<= 2;
							cf <<= 1;
							b2 <<= 2;
							cb <<= 1;
						}
					}
					ssd1306_buffer[CURSOR_LOC] = b2;
					ssd1306_buffer[CURSOR_LOC + 1] = b2;
					ssd1306_buffer[CURSOR_LOC + 128] = b1;
					ssd1306_buffer[CURSOR_LOC + 129] = b1;
					CURSOR_LOC += 2;
					if(CURSOR_LOC%128 > (128 - text_size*5)) {
						setCursor(0, CURR_ROW + text_size);
					}
				}
			}
			k++;
		}
		CURSOR_LOC = 256;
		break;
	}
}

void ssd1306::setCursor(uint8_t col, uint8_t row) {
	CURSOR_LOC = row*128 + col;
	CURR_ROW = CURSOR_LOC/128;
	CURR_COL = CURSOR_LOC%128;
}

void ssd1306::setTextSize(uint8_t size) {
	text_size = size;
}

uint16_t ssd1306::inc_CURSOR_LOC(uint8_t inc) {
	uint16_t ret = CURSOR_LOC;
	CURSOR_LOC += inc;
	if(CURSOR_LOC > 511) {
		CURSOR_LOC = CURSOR_LOC-512;
	}
	CURR_COL = CURR_COL%128;
	CURR_ROW = CURR_ROW/128;
	return ret;
}

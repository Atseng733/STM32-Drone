#include <main.h>

int main() {
	GPIO_pinConfig(GPIOA, 6, OUTPUT, NOPULL);
	/*while (1) {
        int ctr;
        ctr = (8000000);
        for(ctr; ctr > 0; ctr--) {
        	asm("");
        }
        GPIO_pinReset(GPIOA, 6);
        ctr = (8000000);
        // each loop iteration takes 3 cycles to execute.
        while (ctr) {
            asm ("");
            --ctr;
        }
        GPIO_pinSet(GPIOA, 6);
	}*/
	if(RCC->CR & 0x00010000) {
		GPIO_pinReset(GPIOA, 6);
	}
}

void RESTART_HANDLER() {
	RCC->CR |= 1 << 16; //enable external high-speed clock
	RCC->CR &= ~(1 << 0);
	main();
	while(1);
}

extern void (*const vectors[])() __attribute__ ((section(".vectors"))) = {
	(void (*)())0x20000400,
	RESTART_HANDLER,
};
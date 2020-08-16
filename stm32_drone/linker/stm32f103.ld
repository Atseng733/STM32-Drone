OUTPUT_FORMAT(elf32-littlearm)
OUTPUT_ARCH(arm)

MEMORY {
    rom (rx)    : ORIGIN = 0x08000000, LENGTH = 0x00010000
    ram (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x00005000
}

STACK_SIZE = 0x1000;

SECTIONS {
    .vectors : {
    	*(.vectors)
    } > rom
     
    .text : {
        *(.text*)
        _etext = . ;
    } > rom

    .bss (NOLOAD) : {
   		_sbss = . ;
    	*(.bss*)
    	*(COMMON)
    	_ebss = . ;
    } > ram

    .stack (NOLOAD) : {
    	. = ALIGN(8);
    	. = . + STACK_SIZE;
    	. = ALIGN(8);
    } > ram

    .data : {
   		_sdata = . ;
    	*(.data*);
    	_edata = . ;
    } > ram AT > rom 

    _end = . ;
}

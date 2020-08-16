target extended-remote /dev/ttyBmpGdb
monitor swdp_scan
attach 1
set mem inaccessible-by-default off
make debug
file build/stm32.elf
load build/stm32.elf

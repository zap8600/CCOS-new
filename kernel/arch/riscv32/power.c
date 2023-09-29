#include <stdint.h>
#include <kernel/libk/stdio.h>
#include <kernel/power.h>

unsigned int * syscon = (unsigned int *)0x100000;

void poweroff(void) {
    printf("Poweroff.\n");
    *syscon = 0x5555;
}

void reboot(void) {
    printf("Reboot.\n");
    *syscon = 0x7777;
}
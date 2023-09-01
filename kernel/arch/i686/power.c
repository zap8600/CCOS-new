#include <stdint.h>
#include <kernel/stdio.h>
#include <kernel/power.h>

#include "io.h"

void poweroff(void) {
    printf("Poweroff.\n");
    outw(0x604, 0x2000);
}

void reboot(void) {
    printf("Reboot.\n");
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
}

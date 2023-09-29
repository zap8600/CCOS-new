#include <stdint.h>
#include <kernel/libk/stdio.h>
#include <kernel/power.h>

void poweroff(void) {
    printf("Poweroff not yet supported on ARM!\n");
}

void reboot(void) {
    printf("Reboot not yet supported for ARM!\n");
}

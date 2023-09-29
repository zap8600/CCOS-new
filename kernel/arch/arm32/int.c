#include <stdint.h>
#include <kernel/libk/stdio.h>
#include <kernel/int.h>

void init_ints(void) {
   printf("Interrupts not yet supported on ARM!");
}

void breakpoint(void) {
    printf("Breakpoints not yet supported on ARM!\n");
}

#include <kernel/stdio.h>
#include <kernel/tty.h>
#include <kernel/power.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	poweroff();
}

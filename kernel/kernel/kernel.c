#include <kernel/stdio.h>
#include <kernel/tty.h>
#include <kernel/power.h>
#include <kernel/int.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	init_ints();
	printf("Initialized interrupts!\n");
	while(1) {}
	__asm__ __volatile__("int $3");
	poweroff();
}

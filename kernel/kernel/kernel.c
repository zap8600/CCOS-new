#include <kernel/libk/stdio.h>
#include <kernel/tty.h>
#include <kernel/power.h>
#include <kernel/int.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n");
	/* Memory Management should be added before Interrupts
	init_ints();
	printf("Initialized interrupts!\n");
	breakpoint();
	*/
	poweroff();
}

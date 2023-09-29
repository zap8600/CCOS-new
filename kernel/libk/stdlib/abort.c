#include <kernel/libk/stdio.h>
#include <kernel/libk/stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
	// TODO: Add proper kernel panic.
	printf("kernel: panic: abort()\n");
	while (1) { }
	__builtin_unreachable();
}

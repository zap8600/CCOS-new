#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/string.h>

#include <kernel/tty.h>

unsigned char * uart = (unsigned char *)0x10000000; 

void terminal_initialize(void) {
	// init term
}

void terminal_putchar(char c) {
	*uart = c;
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

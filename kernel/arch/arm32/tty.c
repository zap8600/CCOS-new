#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/libk/string.h>

#include <kernel/tty.h>

unsigned char * uart = (unsigned char *)0x9000000;

void terminal_initialize(void) {
    // no need as far as i know
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
#include <stdint.h>

#include "gdt.h"
#include <kernel/string.h>
#include <kernel/stdio.h>

void init_gdt() {
	printf("No GDT set, kept for basic structure.\n");

	/*
    asm volatile (
		"mov %0, %%edi\n"
		"lgdt (%%edi)\n"
		"mov $0x10, %%ax\n"
		"mov %%ax, %%ds\n"
		"mov %%ax, %%es\n"
		"mov %%ax, %%ss\n"
		"mov $0x38, %%ax\n"
		"ltr %%ax\n"
		: : "r"(&gdtr)
	);
	*/
}
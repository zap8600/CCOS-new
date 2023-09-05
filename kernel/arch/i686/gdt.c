#include <stdint.h>

#include "gdt.h"
#include <kernel/string.h>

uint64_t gdt_entries[3];

struct GDTR{
	uint16_t limit;
    uint64_t address;
} __attribute__((packed));

void
create_descriptor(uint32_t base, uint32_t limit, uint16_t flag, int entry)
{
    uint64_t descriptor;
 
    // Create the high 32 bit segment
    descriptor  =  limit       & 0x000F0000;         // set limit bits 19:16
    descriptor |= (flag <<  8) & 0x00F0FF00;         // set type, p, dpl, s, g, d/b, l and avl fields
    descriptor |= (base >> 16) & 0x000000FF;         // set base bits 23:16
    descriptor |=  base        & 0xFF000000;         // set base bits 31:24
 
    // Shift by 32 to allow for low part of segment
    descriptor <<= 32;
 
    // Create the low 32 bit segment
    descriptor |= base  << 16;                       // set base bits 15:0
    descriptor |= limit  & 0x0000FFFF;               // set limit bits 15:0

	gdt_entries[entry] = descriptor << 32;
}

void init_gdt() {
	gdt_entries[0] = 0;
	create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0), 1);
    create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0), 2);

	struct GDTR gdtr = {
		.limit = 3 * sizeof(uint64_t) - 1,
		.address = (uintptr_t)&gdt_entries,
	};

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
}
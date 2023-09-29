#include <kernel/libk/stdio.h>
#include <kernel/int.h>
#include "io.h"
#include <stdint.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)
#define PIC_EOI		0x20		/* End-of-interrupt command code */

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

struct regs {
	uintptr_t ebp, edi, esi, edx, ecx, ebx, eax;

	uintptr_t int_no, err_code;

	uintptr_t eip, cs, eflags, esp, ss;
};

extern struct regs * _isr0(struct regs*);
extern struct regs * _isr1(struct regs*);
extern struct regs * _isr2(struct regs*);
extern struct regs * _isr3(struct regs*);
extern struct regs * _isr4(struct regs*);
extern struct regs * _isr5(struct regs*);
extern struct regs * _isr6(struct regs*);
extern struct regs * _isr7(struct regs*);
extern struct regs * _isr8(struct regs*);
extern struct regs * _isr9(struct regs*);
extern struct regs * _isr10(struct regs*);
extern struct regs * _isr11(struct regs*);
extern struct regs * _isr12(struct regs*);
extern struct regs * _isr13(struct regs*);
extern struct regs * _isr14(struct regs*);
extern struct regs * _isr15(struct regs*);
extern struct regs * _isr16(struct regs*);
extern struct regs * _isr17(struct regs*);
extern struct regs * _isr18(struct regs*);
extern struct regs * _isr19(struct regs*);
extern struct regs * _isr20(struct regs*);
extern struct regs * _isr21(struct regs*);
extern struct regs * _isr22(struct regs*);
extern struct regs * _isr23(struct regs*);
extern struct regs * _isr24(struct regs*);
extern struct regs * _isr25(struct regs*);
extern struct regs * _isr26(struct regs*);
extern struct regs * _isr27(struct regs*);
extern struct regs * _isr28(struct regs*);
extern struct regs * _isr29(struct regs*);
extern struct regs * _isr30(struct regs*);
extern struct regs * _isr31(struct regs*);

typedef struct regs * (*interrupt_handler_t)(struct regs *);

typedef struct
{
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;
   uint8_t zero;
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
} __attribute__((packed)) idt_entry_t;

struct idt_pointer
{
   uint16_t limit;
   uintptr_t base;
} __attribute__((packed));

typedef struct {
	uintptr_t ebp, edi, esi, edx, ecx, ebx, eax;

	uintptr_t int_no, err_code;

	uintptr_t eip, cs, eflags, esp, ss;
}registers_t;

static struct idt_pointer idtp;
static idt_entry_t idt[256];

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t *r) {
    printf("Received ISR. Exception: %s.\n", exception_messages[r->int_no]);
}

void idt_set_gate(int n, interrupt_handler_t handler)
{
    uintptr_t base = (uintptr_t)handler;
    idt[n].offset_1 = base & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_2 = (base >> 16) & 0xFFFF;
}

void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

void init_ints(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uintptr_t)&idt;
    idt_set_gate(0, _isr0);
    idt_set_gate(1, _isr1);
    idt_set_gate(2, _isr2);
    idt_set_gate(3, _isr3);
    idt_set_gate(4, _isr4);
    idt_set_gate(5, _isr5);
    idt_set_gate(6, _isr6);
    idt_set_gate(7, _isr7);
    idt_set_gate(8, _isr8);
    idt_set_gate(9, _isr9);
    idt_set_gate(10, _isr10);
    idt_set_gate(11, _isr11);
    idt_set_gate(12, _isr12);
    idt_set_gate(13, _isr13);
    idt_set_gate(14, _isr14);
    idt_set_gate(15, _isr15);
    idt_set_gate(16, _isr16);
    idt_set_gate(17, _isr17);
    idt_set_gate(18, _isr18);
    idt_set_gate(19, _isr19);
    idt_set_gate(20, _isr20);
    idt_set_gate(21, _isr21);
    idt_set_gate(22, _isr22);
    idt_set_gate(23, _isr23);
    idt_set_gate(24, _isr24);
    idt_set_gate(25, _isr25);
    idt_set_gate(26, _isr26);
    idt_set_gate(27, _isr27);
    idt_set_gate(28, _isr28);
    idt_set_gate(29, _isr29);
    idt_set_gate(30, _isr30);
    idt_set_gate(31, _isr31);

    PIC_remap(0x20, 0x28);

    asm volatile (
		"lidt (%0)"
		: : "m"(idtp)
	);
    __asm__ volatile ("sti");
}

void breakpoint(void) {
    __asm__ __volatile__("int $3");
}
# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
.global stack_top
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call gdt_load

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b


.align 4
gdt_base:
    // GDT Entry 0: Null Segment Descriptor
    .long 0x00000000
    .long 0x00000000
    // GDT Entry 1: Code Segment Descriptor (SEG_KCODE)
    .word 0xFFFF                            // limit  0:15
    .word 0x0000                            // base   0:15
    .byte 0x00                              // base  16:23
    .byte 0b10011010                        // present, iopl/0, code, execute/read
    .byte 0b11001111                        // 4 KB granularity, 32-bit selector; limit 16:19
    .byte 0x00                              // base  24:31
    // GDT Entry 2: Data Segment Descriptor (SEG_KDATA)
    .word 0xFFFF                            // limit  0:15
    .word 0x0000                            // base   0:15
    .byte 0x00                              // base  16:23
    .byte 0b10010010                        // present, iopl/0, data, read/write
    .byte 0b11001111                        // 4 KB granularity, 32-bit selector; limit 16:19
    .byte 0x00                              // base  24:31
gdt_ptr:
    .word (gdt_ptr - gdt_base - 1)
    .long gdt_base

.set SEG_KCODE, 1
.set SEG_KDATA, 2

gdt_load:
    lgdt gdt_ptr
    ljmp $(SEG_KCODE << 3), $fix_cs         // 0x0008 (code segment)
fix_cs:
    movw $(SEG_KDATA << 3), %ax             // 0x0010 (data segment)
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ret

.size _start, . - _start

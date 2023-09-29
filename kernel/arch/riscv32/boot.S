.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
.global stack_top
stack_top:

.section .text
.global _start
.align 4
_start:
	/* Setup stack */
	la sp, stack_top
	addi sp,sp,-16
	sw ra,12(sp)
	jal ra, kernel_main
1:	csrw mie, zero
	wfi
	j 1b
.size _start, . - _start

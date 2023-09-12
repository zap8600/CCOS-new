.section .init
.global _start
.align 4
_start:
	/* Setup stack */
	la sp, stack_top
	addi sp,sp,-16
	sw ra,12(sp)
	jal ra, kernel_main

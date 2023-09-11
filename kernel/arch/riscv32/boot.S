.section .init
.global _start
.align 4
_start:
	/* Setup stack */
	la sp, stack_top
	addi sp,sp,-16
	sw ra,12(sp)

	# a0 - frame address
    csrw mscratch, a0
  
    # Set MPP=0 (U-mode), MPIE=1, SPIE=0
    li t0, (0b11 << 11) | (1 << 7)
    csrw mstatus, t0

    # a1 - program counter
    csrw mepc, a1

    # a2 - SATP register
    csrw satp, a2
  
    # Enable external, timer and software interrupts from
    # M-mode and S-mode alike
    li t0, 0xAAA
    csrw mie, t0

    # Set interrupt handler
    la t0, interrupt_handler
    csrw mtvec, t0

	jal ra, kernel_main

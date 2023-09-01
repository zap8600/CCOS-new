.section .init
 
.option norvc
 
.type _start, @function
.global _start
_start:
	/* Setup stack */
	la sp, stack_top

	tail kernel_main

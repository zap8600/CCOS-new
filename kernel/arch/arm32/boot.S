.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
.global stack_top
stack_top:

.section .text
.global _start
_start:
    ldr sp, stack_top
    bl kernel_main
1:
    b 1b
.size _start, . - _start

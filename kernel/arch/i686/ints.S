.macro ISR_NOERR index
    .global _isr\index
    .type _isr\index, @function
    _isr\index:
        push $0x00
        push $\index
        jmp isr_common
.endm

.macro ISR_ERR index
    .global _isr\index
    .type _isr\index, @function
    _isr\index:
        push $\index
        jmp isr_common
.endm

ISR_NOERR 0
ISR_NOERR 1
//ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERR   8
ISR_NOERR 9
ISR_ERR   10
ISR_ERR   11
ISR_ERR   12
ISR_ERR   13
ISR_ERR   14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

.global _isr2
.type _isr2, @function
_isr2:
    cli
1:
    hlt
    jmp 1b

isr_common:
    push %edi
    push %esi
    push %ebp
    push %ebx
    push %edx
    push %ecx
    push %eax

    cld
    
    push %esp
    call isr_handler
    mov %esp, %eax

    push %edi
    push %esi
    push %ebp
    push %ebx
    push %edx
    push %ecx
    push %eax
    
    add $8, %esp
    iret
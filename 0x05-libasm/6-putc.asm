global asm_putc
section .text

asm_putc:
    push rbp
    mov rbp, rsp
    push rdi
    mov rax, 1 ;syscall number 1 is write
    mov rdi, 1 ;1st arg dest file discriptor 1 is stdout
    mov rsi, rsp ;2nd arg input data
    mov rdx, 1 ;3rd arg length of input data
    syscall
    mov rax, 1
    pop rdi
    mov rsp, rbp
    pop rbp
    ret

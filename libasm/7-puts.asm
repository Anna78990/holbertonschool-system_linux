global asm_puts
extern asm_strlen
section .text

asm_puts:
    push rbp
    mov rbp, rsp
    push rdi
    call asm_strlen
    mov rdx, rax ; length
    mov rax, 1
    mov rdi, 1
    mov rsi, [rsp] ; strings to write
    syscall
    mov rax, rdx
    pop rdi
    mov rsp, rbp
    pop rbp
    ret

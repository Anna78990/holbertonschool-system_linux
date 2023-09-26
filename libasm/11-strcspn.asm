section .text
global asm_strcspn

asm_strcspn:
    push rbp
    mov rbp, rsp
    push rcx
    xor rax, rax
    jmp start

loop:
    mov cl, byte [rsi + rax]
    test cl, cl
    jz found
    mov dl, byte [rdi + rax]
    test dl, dl
    jz found
    cmp cl, dl
    je found

    inc rax
    jmp loop

start:
    jmp loop

found:
    pop rcx
    sub rax, rcx
    mov rsp, rbp
    pop rbp
    ret


global asm_strcasecmp
section .text

asm_strcasecmp:
    push rbp
    mov rbp, rsp
    mov rcx, 0
compare:
    mov rax, 0
    mov rbx, 0
    mov al, byte [rdi + rcx]
    mov bl, byte [rsi + rcx]
    cmp al, bl
    je equal
    jl less
    jg greater
equal:
    cmp al, 0
    je exit
    inc rcx
    jmp compare
less:
    sub bl, 32
    cmp al, bl
    je equal
    jmp exit
greater:
    add bl, 32
    cmp al, bl
    je equal
    jmp exit
exit:
    mov bl, byte [rsi + rcx]
    sub bl, al
    mov al, bl
    mov rsp, rbp
    pop rbp
    ret

global asm_strncasecmp
section .text

asm_strncasecmp:
    push rbp
    mov rbp, rsp
    mov rcx, 0
compare:
    xor rax, rax
    xor rbx, rbx
    mov al, byte [rdi + rcx]
    mov bl, byte [rsi + rcx]
    cmp rcx, rdx
    je exit
    cmp al, bl
    je equal
    jl less
    jg greate
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
greate:
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

global asm_strchr
section .text

asm_strchr:
    push rbp
    mov rbp, rsp
    mov rcx, 0
search:
    mov al, byte [rdi + rcx]
    cmp al, sil
    je found
    test al, al
    jz null
    inc rcx
    jmp search
null:
    xor rax, rax
    jmp exit
found:
    lea rax, [rdi + rcx]
    jmp exit
exit:
    mov rsp, rbp
    pop rbp
    ret

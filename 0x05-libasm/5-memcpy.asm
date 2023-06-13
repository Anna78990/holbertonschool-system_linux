global asm_memcpy
section .text

asm_memcpy:
    push rbp
    mov rbp, rsp
    mov rcx, 0
copy:
    cmp rcx, rdx
    je end
    mov al, byte [rsi + rcx]
    mov byte [rdi + rcx], al
    inc rcx
    jmp copy
end:
    mov rax, rdi
    mov rsp, rbp
    pop rbp
    ret

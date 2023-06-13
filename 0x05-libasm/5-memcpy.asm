global asm_memcpy
section .text

asm_memcpy:
    push rbp
    mov rbp, rsp
    xor rcx, rcx

copy_loop:
    cmp rcx, rdx
    je end_memcpy

    mov al, byte [rsi + rcx]
    mov byte [rdi + rcx], al

    inc rcx
    jmp copy_loop

end_memcpy:
    mov rax, rdi
    mov rsp, rbp
    pop rbp
    ret

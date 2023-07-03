section .text
global asm_strspn

asm_strspn:
    push rbp
    mov rbp, rsp
    push rcx
    xor rax, rax
    jmp loop

loop:
    mov cl, byte [rsi + rax]
    test cl, cl
    jz end
    mov dl, byte [rdi + rax]
    test dl, dl
    jz end
    cmp cl, dl
    jne end
    inc rax
    jmp loop

end:
    ; Print the intermediate values
    push rax
    push rdi
    push rsi
    call print_values
    add rsp, 12

    pop rcx
    mov rsp, rbp
    pop rbp
    ret

print_values:
    ; Print the values stored in rax, rdi, rsi registers
    mov rdi, rax
    mov rax, 1
    mov rsi, format
    mov rdx, format_len
    syscall
    ret


section .data
format db "%zu, %zu, %zu", 10
format_len equ $ - format

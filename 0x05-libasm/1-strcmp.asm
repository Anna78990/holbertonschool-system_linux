global asm_strcmp
section .text

asm_strcmp:
            xor rax, rax
            mov rax, [rdi]
            cmp rax, [rsi]
            je equal
	    jl less
	    jg greater
equal:
	    cmp rax, 0
	    je exit
	    inc rdi
	    inc rsi
	    jmp asm_strcmp

less:
	    mov rax, -1
	    jmp exit
greater:
	    mov rax, 1
	    jmp exit
exit:
	    ret

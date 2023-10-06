section .text
global asm_strpbrk

asm_strpbrk:
	push rbp
	mov rbp, rsp
	mov rax, 0

	mov r10, rdi
	mov r11, rsi

search_loop:
	movzx r8, byte [r10]
	cmp r8b, 0
	jz end
	mov rdi, r11
	mov rsi, r8
	jmp strchr
_return:
	cmp rax, 0
	jnz found
	inc r10
	jmp search_loop

found:
	mov rax, r10

end:
	mov rsp, rbp
	pop rbp
	ret

strchr:
	push rbp
	mov rbp, rsp
	mov rax, 0

_loop:
	mov al, byte [rdi]
	cmp byte [rdi], sil
	jz _found
	cmp byte [rdi], 0
	jz _end
	inc rdi
	jmp _loop

_found:
	mov rax, rdi

_end:
	mov rsp, rbp
	pop rbp
	jmp _return

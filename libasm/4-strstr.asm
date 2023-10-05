global asm_strchr
section .text

asm_strstr:
	push rbp,
	mov rbp, rsp

	loop:
	mov rax, 0
	push rdi
	push rsi
	jmp _strstr
	strstr_return:
	pop rsi
	pop rdi
	test rax, rax
	jnz end
	inc rdi
	cmp BYTE [rdi], 0
	jz end
	jmp loop

	end:
	mov rsp, rbp
	pop rbp
	ret

_strstr:
	push rbp,
	mov rbp, rsp

	push rdi
	mov rax, 0

	strstr_loop:
	movzx edx, byte [rdi]
	movzx ecx, byte [rsi]
	test cl, cl
	jz found
	cmp dl, cl
	jnz not_found
	inc rdi
	inc rsi
	jmp strstr_loop
found:
	pop rax
	jmp strstr_end
not_found:
	pop rax
	mov rax, 0
	strstr_end:
	mov rsp, rbp
	pop rbp
	jmp strstr_return

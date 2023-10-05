global asm_strspn
section .text

asm_strspn:
	push rbp
	mov rbp, rsp
	mov rcx, 0

loop_strspn:
	cmp byte [rdi], 0
	jz strspn_end
	mov rax, 0
	push rsi
	push rdi
	mov rdi, rsi
	mov rsi, [rsp]
	movzx rsi, byte [rsi]
	jmp strchr
back:
	pop rdi
	pop rsi
	test rax, rax
	jz strspn_end
	inc rcx
	inc rdi
	jmp loop_strspn

strspn_end:
	mov rax, rcx
	mov rsp, rbp
	pop rbp
	ret

strchr:
	push rbp
	mov rbp, rsp
	mov rax, 0

strchr_loop:
	mov al, byte [rdi]
	cmp byte [rdi], sil
	jz found
	cmp byte [rdi], 0
	jz strchr_end
	inc rdi
	jmp strchr_loop

found:
	mov rax, rdi

strchr_end:
	mov rsp, rbp
	pop rbp
	jmp back

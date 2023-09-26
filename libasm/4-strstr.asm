global asm_strstr

section .text
	global asm_strstr

asm_strstr:
	push rbp
	mov rbp, rsp
	push rbx
	push rsi
	push rdi

	mov rdi, rdi ; haystack
	mov rsi, rsi ; needle

	cld ; Set the direction flag to forward

	; Check if either the haystack or needle is empty
	mov al, byte [rdi]
	or al, al
	jz .null_needle

	mov al, byte [rsi]
	or al, al
	jz .found

	; Loop through the haystack
.loop_haystack:
	mov rcx, rsi ; Save the needle pointer
	mov rbx, rdi ; Save the haystack pointer

	; Compare the current character in haystack with the first character of needle
	mov al, byte [rdi]
	or al, al
	jz .null_haystack

	cmp al, byte [rsi]
	jne .continue_haystack

	; Found a potential match, continue comparing
	mov rdx, rdi ; Save the current position in haystack
	inc rsi ; Move to the next character in needle
	inc rdi ; Move to the next character in haystack

	; Compare the remaining characters in needle
.loop_needle:
	mov al, byte [rdi]
	or al, al
	jz .found

	cmp al, byte [rsi]
	jne .continue_haystack

	inc rsi ; Move to the next character in needle
	inc rdi ; Move to the next character in haystack

	jmp .loop_needle

.continue_haystack:
	; Not a match, reset the pointers and continue searching
	mov rdi, rbx ; Restore haystack pointer
	mov rsi, rcx ; Restore needle pointer
	inc rdi ; Move to the next character in haystack
	jmp .loop_haystack

.null_needle:
	xor rax, rax ; Return NULL if needle is empty
	jmp .end

.null_haystack:
	xor rax, rax ; Return NULL if haystack is empty
	jmp .end

.found:
	mov rax, rdx ; Set the return value to the position of the match

.end:
	pop rdi
	pop rsi
	pop rbx
	mov rsp, rbp
	pop rbp
	ret

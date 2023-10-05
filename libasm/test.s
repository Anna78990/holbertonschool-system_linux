	.file	"test.c"
	.text
	.globl	my_strstr
	.type	my_strstr, @function
my_strstr:
.LFB6:
	.cfi_startproc
	endbr64
	movq	%rdi, -24(%rsp)
	movq	%rsi, -32(%rsp)
	movq	-32(%rsp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L4
	movq	-24(%rsp), %rax
	ret
.L9:
	movq	-24(%rsp), %rax
	movq	%rax, -16(%rsp)
	movq	-32(%rsp), %rax
	movq	%rax, -8(%rsp)
	jmp	.L5
.L7:
	addq	$1, -16(%rsp)
	addq	$1, -8(%rsp)
.L5:
	movq	-16(%rsp), %rax
	movzbl	(%rax), %edx
	movq	-8(%rsp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	jne	.L6
	movq	-8(%rsp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L7
.L6:
	movq	-8(%rsp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L8
	movq	-24(%rsp), %rax
	ret
.L8:
	addq	$1, -24(%rsp)
.L4:
	movq	-24(%rsp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L9
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE6:
	.size	my_strstr, .-my_strstr
	.section	.rodata
.LC0:
	.string	""
.LC1:
	.string	"Holberton Socool"
.LC2:
	.string	"%p\n"
.LC3:
	.string	"Holberton School"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	my_strstr
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC3, %esi
	movl	$.LC1, %edi
	call	my_strstr
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC1, %esi
	movl	$.LC1, %edi
	call	my_strstr
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:

	.file	"wc209.c"
	.text
	.section	.rodata
.LC0:
	.string	" there is some error"
	.align 8
.LC1:
	.string	"Error: line %d: unterminated comment\n"
.LC2:
	.string	"%d %d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$1, -20(%rbp)
	movl	$1, -16(%rbp)
	movl	$1, -32(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L27:
	cmpl	$10, -4(%rbp)
	jne	.L3
	addl	$1, -32(%rbp)
.L3:
	cmpl	$5, -20(%rbp)
	ja	.L4
	movl	-20(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L6(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L6(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L6:
	.long	.L5-.L6
	.long	.L7-.L6
	.long	.L8-.L6
	.long	.L9-.L6
	.long	.L10-.L6
	.long	.L11-.L6
	.text
.L5:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L12
	movl	$1, -20(%rbp)
	addl	$1, -24(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L12:
	cmpl	$47, -4(%rbp)
	jne	.L13
	movl	$2, -20(%rbp)
	addl	$1, -24(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L13:
	movl	$0, -20(%rbp)
	addl	$1, -24(%rbp)
	jmp	.L2
.L7:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	jne	.L14
	cmpl	$47, -4(%rbp)
	jne	.L15
	movl	$2, -20(%rbp)
	addl	$1, -28(%rbp)
	addl	$1, -24(%rbp)
	movl	$1, -16(%rbp)
	jmp	.L2
.L15:
	movl	$0, -20(%rbp)
	addl	$1, -28(%rbp)
	addl	$1, -24(%rbp)
	movl	$1, -16(%rbp)
	jmp	.L2
.L14:
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L8
	movl	$1, -20(%rbp)
	addl	$1, -24(%rbp)
	movl	$1, -16(%rbp)
	jmp	.L2
.L8:
	cmpl	$42, -4(%rbp)
	je	.L16
	call	__ctype_b_loc@PLT
	movq	(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L17
	movl	$1, -20(%rbp)
	addl	$1, -24(%rbp)
	movl	$2, -16(%rbp)
	jmp	.L2
.L17:
	cmpl	$47, -4(%rbp)
	jne	.L18
	movl	$2, -20(%rbp)
	addl	$1, -24(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L18:
	movl	$0, -20(%rbp)
	addl	$1, -24(%rbp)
	movl	$2, -16(%rbp)
	jmp	.L2
.L16:
	cmpl	$42, -4(%rbp)
	jne	.L9
	movl	$3, -20(%rbp)
	cmpl	$1, -16(%rbp)
	jne	.L19
	subl	$1, -28(%rbp)
.L19:
	subl	$1, -24(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	$1, -8(%rbp)
	movl	$2, -16(%rbp)
	jmp	.L2
.L9:
	cmpl	$10, -4(%rbp)
	jne	.L20
	addl	$1, -24(%rbp)
	jmp	.L2
.L20:
	cmpl	$42, -4(%rbp)
	je	.L21
	movl	$4, -20(%rbp)
	movl	$3, -16(%rbp)
	jmp	.L2
.L21:
	cmpl	$42, -4(%rbp)
	jne	.L10
	movl	$5, -20(%rbp)
	movl	$3, -16(%rbp)
	jmp	.L2
.L10:
	cmpl	$10, -4(%rbp)
	jne	.L22
	addl	$1, -24(%rbp)
	movl	$4, -16(%rbp)
	jmp	.L2
.L22:
	cmpl	$42, -4(%rbp)
	jne	.L23
	movl	$5, -20(%rbp)
	movl	$4, -16(%rbp)
	jmp	.L2
.L23:
	cmpl	$42, -4(%rbp)
	je	.L11
	movl	$4, -20(%rbp)
	movl	$4, -16(%rbp)
	jmp	.L2
.L11:
	cmpl	$10, -4(%rbp)
	jne	.L24
	addl	$1, -24(%rbp)
	movl	$4, -20(%rbp)
	movl	$5, -16(%rbp)
	jmp	.L2
.L24:
	cmpl	$42, -4(%rbp)
	jne	.L25
	movl	$5, -20(%rbp)
	jmp	.L2
.L25:
	cmpl	$47, -4(%rbp)
	je	.L26
	movl	$4, -20(%rbp)
	movl	$5, -16(%rbp)
	jmp	.L2
.L26:
	cmpl	$47, -4(%rbp)
	jne	.L4
	addl	$1, -24(%rbp)
	movl	$1, -20(%rbp)
	movl	$0, -8(%rbp)
	movl	$5, -16(%rbp)
	jmp	.L2
.L4:
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L2:
	call	getchar@PLT
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L27
	cmpl	$1, -8(%rbp)
	jne	.L28
	movq	stderr(%rip), %rax
	movl	-12(%rbp), %edx
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf@PLT
	movl	$1, %eax
	jmp	.L29
.L28:
	movl	-24(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
.L29:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

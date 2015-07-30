	.file	"str.c"
	.section	.rodata
.LC0:
	.string	"\nb=%s\nd=%s\n"
	.text
	.globl	deal
	.type	deal, @function
deal:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -88(%rbp)
	movabsq	$8319103319246205297, %rax
	movq	%rax, -80(%rbp)
	movabsq	$7017841267584492644, %rax
	movq	%rax, -72(%rbp)
	movabsq	$7234017283807671137, %rax
	movq	%rax, -64(%rbp)
	movabsq	$7234017283807667300, %rax
	movq	%rax, -56(%rbp)
	movabsq	$7234017283807667300, %rax
	movq	%rax, -48(%rbp)
	movabsq	$7234017283807667300, %rax
	movq	%rax, -40(%rbp)
	movabsq	$8174439530483704932, %rax
	movq	%rax, -32(%rbp)
	movabsq	$31931404416021105, %rax
	movq	%rax, -24(%rbp)
	leaq	-80(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	deal, .-deal
	.section	.rodata
.LC1:
	.string	"c=%s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	$7895160, -48(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	deal
	movq	%rax, -8(%rbp)
	movl	$4323, -12(%rbp)
	movl	$22, -16(%rbp)
	movl	$32, -20(%rbp)
	movl	$2, -24(%rbp)
	movl	$3, -28(%rbp)
	movl	$4, -32(%rbp)
	movl	$7, -36(%rbp)
	movl	$9, -40(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -44(%rbp)
	movl	-16(%rbp), %eax
	movl	-12(%rbp), %edx
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	addl	%eax, %edx
	movl	-32(%rbp), %eax
	addl	%eax, %edx
	movl	-36(%rbp), %eax
	addl	%eax, %edx
	movl	-40(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-9)"
	.section	.note.GNU-stack,"",@progbits

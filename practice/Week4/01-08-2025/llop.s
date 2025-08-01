	.file	"llop.cpp"
# GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -g0 -O0 -fno-asynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.globl	_Z3funv
	.type	_Z3funv, @function
_Z3funv:
.LFB1731:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$416, %rsp	#,
# llop.cpp:11: void fun(){
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp85
	movq	%rax, -8(%rbp)	# tmp85, D.49093
	xorl	%eax, %eax	# tmp85
# llop.cpp:12: int a[100]{1};
	leaq	-416(%rbp), %rdx	#, tmp82
	movl	$0, %eax	#, tmp83
	movl	$50, %ecx	#, tmp84
	movq	%rdx, %rdi	# tmp82, tmp82
	rep stosq
	movl	$1, -416(%rbp)	#, a[0]
# llop.cpp:13: }
	nop	
	movq	-8(%rbp), %rax	# D.49093, tmp86
	subq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp86
	je	.L2	#,
	call	__stack_chk_fail@PLT	#
.L2:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1731:
	.size	_Z3funv, .-_Z3funv
	.globl	main
	.type	main, @function
main:
.LFB1732:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
# llop.cpp:17:     a.a=10;
	movl	$10, -12(%rbp)	#, a.a
# llop.cpp:18:     a.b=45;
	movl	$45, -8(%rbp)	#, a.b
# llop.cpp:19:     a.c=25;
	movl	$25, -4(%rbp)	#, a.c
# llop.cpp:20:     fun();
	call	_Z3funv	#
# llop.cpp:23: }
	movl	$0, %eax	#, _7
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1732:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2227:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movl	%edi, -4(%rbp)	# __initialize_p, __initialize_p
	movl	%esi, -8(%rbp)	# __priority, __priority
# llop.cpp:23: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L7	#,
# llop.cpp:23: }
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L7	#,
# /usr/include/c++/11/iostream:74:   static ios_base::Init __ioinit;
	leaq	_ZStL8__ioinit(%rip), %rax	#, tmp82
	movq	%rax, %rdi	# tmp82,
	call	_ZNSt8ios_base4InitC1Ev@PLT	#
	leaq	__dso_handle(%rip), %rax	#, tmp83
	movq	%rax, %rdx	# tmp83,
	leaq	_ZStL8__ioinit(%rip), %rax	#, tmp84
	movq	%rax, %rsi	# tmp84,
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax	#, tmp86
	movq	%rax, %rdi	# tmp85,
	call	__cxa_atexit@PLT	#
.L7:
# llop.cpp:23: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2227:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z3funv, @function
_GLOBAL__sub_I__Z3funv:
.LFB2228:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# llop.cpp:23: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2228:
	.size	_GLOBAL__sub_I__Z3funv, .-_GLOBAL__sub_I__Z3funv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z3funv
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:

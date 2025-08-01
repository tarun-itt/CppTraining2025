	.file	"function.cpp"
# GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -g0 -O0 -fno-asynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN1AppEi,"axG",@progbits,_ZN1AppEi,comdat
	.align 2
	.weak	_ZN1AppEi
	.type	_ZN1AppEi, @function
_ZN1AppEi:
.LFB1731:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)	# this, this
	movl	%esi, -28(%rbp)	# k, k
# function.cpp:6:         int a =13;
	movl	$13, -4(%rbp)	#, a
# function.cpp:7:         a +=10;
	addl	$10, -4(%rbp)	#, a
# function.cpp:8:         return a;
	pxor	%xmm0, %xmm0	# _3
	cvtsi2sdl	-4(%rbp), %xmm0	# a, _3
	movq	%xmm0, %rax	# _3, <retval>
# function.cpp:9:     }
	movq	%rax, %xmm0	# <retval>,
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1731:
	.size	_ZN1AppEi, .-_ZN1AppEi
	.text
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
# function.cpp:12: int main(){
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp91
	movq	%rax, -8(%rbp)	# tmp91, D.49158
	xorl	%eax, %eax	# tmp91
# function.cpp:15:     std::cout<<a++;
	leaq	-9(%rbp), %rax	#, tmp86
	movl	$0, %esi	#,
	movq	%rax, %rdi	# tmp86,
	call	_ZN1AppEi	#
	movq	%xmm0, %rax	#, _1
	movq	%rax, %xmm0	# _1,
	leaq	_ZSt4cout(%rip), %rax	#, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZNSolsEd@PLT	#
# function.cpp:16:         std::cout<<a++;
	leaq	-9(%rbp), %rax	#, tmp88
	movl	$0, %esi	#,
	movq	%rax, %rdi	# tmp88,
	call	_ZN1AppEi	#
	movq	%xmm0, %rax	#, _2
	movq	%rax, %xmm0	# _2,
	leaq	_ZSt4cout(%rip), %rax	#, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZNSolsEd@PLT	#
# function.cpp:17:     return 0;
	movl	$0, %eax	#, _9
# function.cpp:18: }
	movq	-8(%rbp), %rdx	# D.49158, tmp92
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp92
	je	.L5	#,
	call	__stack_chk_fail@PLT	#
.L5:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1732:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2228:
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
# function.cpp:18: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L8	#,
# function.cpp:18: }
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L8	#,
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
.L8:
# function.cpp:18: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2228:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2229:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# function.cpp:18: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2229:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
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

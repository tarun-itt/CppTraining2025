	.file	"trial.cpp"
# GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -g0 -O0 -fno-asynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN1AC2Ev,"axG",@progbits,_ZN1AC5Ev,comdat
	.align 2
	.weak	_ZN1AC2Ev
	.type	_ZN1AC2Ev, @function
_ZN1AC2Ev:
.LFB1732:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# this, this
# trial.cpp:5:     A(){};
	movq	-8(%rbp), %rax	# this, tmp83
	movl	$234, (%rax)	#, this_3(D)->a
	movq	-8(%rbp), %rax	# this, tmp84
	movl	$30, 4(%rax)	#, this_3(D)->b
	movl	$900, %edx	#, d.0_1
	movq	-8(%rbp), %rax	# this, tmp85
	movl	%edx, 8(%rax)	# d.0_1, this_3(D)->sds
# trial.cpp:5:     A(){};
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1732:
	.size	_ZN1AC2Ev, .-_ZN1AC2Ev
	.weak	_ZN1AC1Ev
	.set	_ZN1AC1Ev,_ZN1AC2Ev
	.globl	_ZN1A1dE
	.section	.rodata
	.align 4
	.type	_ZN1A1dE, @object
	.size	_ZN1A1dE, 4
_ZN1A1dE:
	.long	900
	.globl	_ZN1A1cE
	.data
	.align 4
	.type	_ZN1A1cE, @object
	.size	_ZN1A1cE, 4
_ZN1A1cE:
	.long	7245
	.text
	.globl	main
	.type	main, @function
main:
.LFB1734:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$48, %rsp	#,
# trial.cpp:21: int main(){
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp86
	movq	%rax, -8(%rbp)	# tmp86, D.49150
	xorl	%eax, %eax	# tmp86
# trial.cpp:22:     A obj;
	leaq	-32(%rbp), %rax	#, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZN1AC1Ev	#
# trial.cpp:23:     int val = obj.d;
	movl	$900, -36(%rbp)	#, val
# trial.cpp:24:     B obj2;
	movl	$90, -20(%rbp)	#, obj2.b
	movq	$90, -16(%rbp)	#, obj2.a
# trial.cpp:25:     return 0;
	movl	$0, %eax	#, _6
# trial.cpp:26: }
	movq	-8(%rbp), %rdx	# D.49150, tmp87
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp87
	je	.L4	#,
	call	__stack_chk_fail@PLT	#
.L4:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1734:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2232:
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
# trial.cpp:26: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L7	#,
# trial.cpp:26: }
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
# trial.cpp:26: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2232:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__ZN1A1dE, @function
_GLOBAL__sub_I__ZN1A1dE:
.LFB2233:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# trial.cpp:26: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2233:
	.size	_GLOBAL__sub_I__ZN1A1dE, .-_GLOBAL__sub_I__ZN1A1dE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN1A1dE
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

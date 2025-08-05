	.file	"friend.cpp"
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
# friend.cpp:8:     A(){
	movq	-8(%rbp), %rax	# this, tmp82
	movl	$10, (%rax)	#, this_2(D)->a
	movq	-8(%rbp), %rax	# this, tmp83
	movl	$20, 4(%rax)	#, this_2(D)->b
# friend.cpp:10:     }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1732:
	.size	_ZN1AC2Ev, .-_ZN1AC2Ev
	.weak	_ZN1AC1Ev
	.set	_ZN1AC1Ev,_ZN1AC2Ev
	.section	.rodata
.LC0:
	.string	" "
	.section	.text._Z6access1A,"axG",@progbits,_Z6access1A,comdat
	.weak	_Z6access1A
	.type	_Z6access1A, @function
_Z6access1A:
.LFB1734:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# a, a
# friend.cpp:12:         std::cout<<a.a<<" "<<a.b;
	movl	-8(%rbp), %eax	# a.a, _1
	movl	%eax, %esi	# _1,
	leaq	_ZSt4cout(%rip), %rax	#, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_ZNSolsEi@PLT	#
	movq	%rax, %rdx	#, _2
	leaq	.LC0(%rip), %rax	#, tmp87
	movq	%rax, %rsi	# tmp87,
	movq	%rdx, %rdi	# _2,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _3
# friend.cpp:12:         std::cout<<a.a<<" "<<a.b;
	movl	-4(%rbp), %eax	# a.b, _4
	movl	%eax, %esi	# _4,
	movq	%rdx, %rdi	# _3,
	call	_ZNSolsEi@PLT	#
# friend.cpp:13:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1734:
	.size	_Z6access1A, .-_Z6access1A
	.text
	.globl	_Z7access21A
	.type	_Z7access21A, @function
_Z7access21A:
.LFB1735:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)	# a, a
# friend.cpp:19: }
	nop	
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1735:
	.size	_Z7access21A, .-_Z7access21A
	.globl	main
	.type	main, @function
main:
.LFB1736:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
# friend.cpp:20: int main(){
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp88
	movq	%rax, -8(%rbp)	# tmp88, D.49176
	xorl	%eax, %eax	# tmp88
# friend.cpp:21: A a;
	leaq	-16(%rbp), %rax	#, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZN1AC1Ev	#
# friend.cpp:22: access(a);
	movq	-16(%rbp), %rax	# a, tmp85
	movq	%rax, %rdi	# tmp85,
	call	_Z6access1A	#
# friend.cpp:23: access2(a);
	movq	-16(%rbp), %rax	# a, tmp86
	movq	%rax, %rdi	# tmp86,
	call	_Z7access21A	#
# friend.cpp:24: }
	movl	$0, %eax	#, _6
	movq	-8(%rbp), %rdx	# D.49176, tmp89
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp89
	je	.L6	#,
	call	__stack_chk_fail@PLT	#
.L6:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1736:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2234:
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
# friend.cpp:24: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L9	#,
# friend.cpp:24: }
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L9	#,
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
.L9:
# friend.cpp:24: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2234:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z7access21A, @function
_GLOBAL__sub_I__Z7access21A:
.LFB2235:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# friend.cpp:24: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2235:
	.size	_GLOBAL__sub_I__Z7access21A, .-_GLOBAL__sub_I__Z7access21A
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z7access21A
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

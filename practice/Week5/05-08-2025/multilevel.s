	.file	"multilevel.cpp"
# GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -g0 -O0 -fno-asynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"PIE called\n"
	.section	.text._ZN3PIEC2Ev,"axG",@progbits,_ZN3PIEC5Ev,comdat
	.align 2
	.weak	_ZN3PIEC2Ev
	.type	_ZN3PIEC2Ev, @function
_ZN3PIEC2Ev:
.LFB1732:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:7:     PIE(){
	leaq	16+_ZTV3PIE(%rip), %rdx	#, _1
	movq	-8(%rbp), %rax	# this, tmp83
	movq	%rdx, (%rax)	# _1, this_3(D)->_vptr.PIE
	movq	-8(%rbp), %rax	# this, tmp84
	movl	$1, 8(%rax)	#, this_3(D)->a
	movq	-8(%rbp), %rax	# this, tmp85
	movl	$2, 12(%rax)	#, this_3(D)->b
# multilevel.cpp:8:         std::cout<<"PIE called\n";
	leaq	.LC0(%rip), %rax	#, tmp86
	movq	%rax, %rsi	# tmp86,
	leaq	_ZSt4cout(%rip), %rax	#, tmp87
	movq	%rax, %rdi	# tmp87,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:9:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1732:
	.size	_ZN3PIEC2Ev, .-_ZN3PIEC2Ev
	.weak	_ZN3PIEC1Ev
	.set	_ZN3PIEC1Ev,_ZN3PIEC2Ev
	.section	.rodata
.LC1:
	.string	"Function of pie called\n"
	.section	.text._ZN3PIE6PIEfunEv,"axG",@progbits,_ZN3PIE6PIEfunEv,comdat
	.align 2
	.weak	_ZN3PIE6PIEfunEv
	.type	_ZN3PIE6PIEfunEv, @function
_ZN3PIE6PIEfunEv:
.LFB1734:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:12:         std::cout<<"Function of pie called\n";
	leaq	.LC1(%rip), %rax	#, tmp82
	movq	%rax, %rsi	# tmp82,
	leaq	_ZSt4cout(%rip), %rax	#, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:13:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1734:
	.size	_ZN3PIE6PIEfunEv, .-_ZN3PIE6PIEfunEv
	.section	.rodata
.LC2:
	.string	"Indo Iranian called\n"
	.section	.text._ZN11IndoIranianC2Ev,"axG",@progbits,_ZN11IndoIranianC5Ev,comdat
	.align 2
	.weak	_ZN11IndoIranianC2Ev
	.type	_ZN11IndoIranianC2Ev, @function
_ZN11IndoIranianC2Ev:
.LFB1736:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:20:     IndoIranian(){
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZN3PIEC2Ev	#
	leaq	16+_ZTV11IndoIranian(%rip), %rdx	#, _2
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, (%rax)	# _2, this_4(D)->D.44298._vptr.PIE
	movq	-8(%rbp), %rax	# this, tmp85
	movl	$3, 16(%rax)	#, this_4(D)->c
	movq	-8(%rbp), %rax	# this, tmp86
	movl	$4, 20(%rax)	#, this_4(D)->d
# multilevel.cpp:21:         std::cout<<"Indo Iranian called\n";
	leaq	.LC2(%rip), %rax	#, tmp87
	movq	%rax, %rsi	# tmp87,
	leaq	_ZSt4cout(%rip), %rax	#, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:22:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1736:
	.size	_ZN11IndoIranianC2Ev, .-_ZN11IndoIranianC2Ev
	.weak	_ZN11IndoIranianC1Ev
	.set	_ZN11IndoIranianC1Ev,_ZN11IndoIranianC2Ev
	.section	.rodata
.LC3:
	.string	"vedic snaskrit called\n"
	.section	.text._ZN13VedicSanskritC2Ev,"axG",@progbits,_ZN13VedicSanskritC5Ev,comdat
	.align 2
	.weak	_ZN13VedicSanskritC2Ev
	.type	_ZN13VedicSanskritC2Ev, @function
_ZN13VedicSanskritC2Ev:
.LFB1739:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:29:     VedicSanskrit(){
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZN11IndoIranianC2Ev	#
	leaq	16+_ZTV13VedicSanskrit(%rip), %rdx	#, _2
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, (%rax)	# _2, this_4(D)->D.44347.D.44298._vptr.PIE
	movq	-8(%rbp), %rax	# this, tmp85
	movl	$5, 24(%rax)	#, this_4(D)->e
	movq	-8(%rbp), %rax	# this, tmp86
	movl	$6, 28(%rax)	#, this_4(D)->f
# multilevel.cpp:30:         std::cout<<"vedic snaskrit called\n";
	leaq	.LC3(%rip), %rax	#, tmp87
	movq	%rax, %rsi	# tmp87,
	leaq	_ZSt4cout(%rip), %rax	#, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:31:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1739:
	.size	_ZN13VedicSanskritC2Ev, .-_ZN13VedicSanskritC2Ev
	.weak	_ZN13VedicSanskritC1Ev
	.set	_ZN13VedicSanskritC1Ev,_ZN13VedicSanskritC2Ev
	.section	.rodata
.LC4:
	.string	"Classical Sanskrit called\n"
	.section	.text._ZN17ClassicalSanskritC2Ev,"axG",@progbits,_ZN17ClassicalSanskritC5Ev,comdat
	.align 2
	.weak	_ZN17ClassicalSanskritC2Ev
	.type	_ZN17ClassicalSanskritC2Ev, @function
_ZN17ClassicalSanskritC2Ev:
.LFB1745:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:47:     ClassicalSanskrit(){
	movq	-8(%rbp), %rax	# this, _1
	movq	%rax, %rdi	# _1,
	call	_ZN13VedicSanskritC2Ev	#
	leaq	16+_ZTV17ClassicalSanskrit(%rip), %rdx	#, _2
	movq	-8(%rbp), %rax	# this, tmp84
	movq	%rdx, (%rax)	# _2, this_4(D)->D.44421.D.44347.D.44298._vptr.PIE
	movq	-8(%rbp), %rax	# this, tmp85
	movl	$9, 32(%rax)	#, this_4(D)->i
	movq	-8(%rbp), %rax	# this, tmp86
	movl	$10, 36(%rax)	#, this_4(D)->j
# multilevel.cpp:48:         std::cout<<"Classical Sanskrit called\n";
	leaq	.LC4(%rip), %rax	#, tmp87
	movq	%rax, %rsi	# tmp87,
	leaq	_ZSt4cout(%rip), %rax	#, tmp88
	movq	%rax, %rdi	# tmp88,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:49:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1745:
	.size	_ZN17ClassicalSanskritC2Ev, .-_ZN17ClassicalSanskritC2Ev
	.weak	_ZN17ClassicalSanskritC1Ev
	.set	_ZN17ClassicalSanskritC1Ev,_ZN17ClassicalSanskritC2Ev
	.section	.rodata
	.align 8
.LC5:
	.string	"Classica sanskrit version of pieFUn\n"
	.section	.text._ZN17ClassicalSanskrit6PIEfunEv,"axG",@progbits,_ZN17ClassicalSanskrit6PIEfunEv,comdat
	.align 2
	.weak	_ZN17ClassicalSanskrit6PIEfunEv
	.type	_ZN17ClassicalSanskrit6PIEfunEv, @function
_ZN17ClassicalSanskrit6PIEfunEv:
.LFB1747:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:51:         std::cout<<"Classica sanskrit version of pieFUn\n";
	leaq	.LC5(%rip), %rax	#, tmp82
	movq	%rax, %rsi	# tmp82,
	leaq	_ZSt4cout(%rip), %rax	#, tmp83
	movq	%rax, %rdi	# tmp83,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:52:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1747:
	.size	_ZN17ClassicalSanskrit6PIEfunEv, .-_ZN17ClassicalSanskrit6PIEfunEv
	.section	.rodata
.LC6:
	.string	"Proto dravidian called\n"
	.section	.text._ZN14protoDravidianC2Ev,"axG",@progbits,_ZN14protoDravidianC5Ev,comdat
	.align 2
	.weak	_ZN14protoDravidianC2Ev
	.type	_ZN14protoDravidianC2Ev, @function
_ZN14protoDravidianC2Ev:
.LFB1749:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:58:     protoDravidian(){
	movq	-8(%rbp), %rax	# this, tmp82
	movl	$11, (%rax)	#, this_2(D)->k
# multilevel.cpp:59:         std::cout<<"Proto dravidian called\n";
	leaq	.LC6(%rip), %rax	#, tmp83
	movq	%rax, %rsi	# tmp83,
	leaq	_ZSt4cout(%rip), %rax	#, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:60:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1749:
	.size	_ZN14protoDravidianC2Ev, .-_ZN14protoDravidianC2Ev
	.weak	_ZN14protoDravidianC1Ev
	.set	_ZN14protoDravidianC1Ev,_ZN14protoDravidianC2Ev
	.section	.rodata
.LC7:
	.string	"Telugu called\n"
	.section	.text._ZN6TeluguC2Ev,"axG",@progbits,_ZN6TeluguC5Ev,comdat
	.align 2
	.weak	_ZN6TeluguC2Ev
	.type	_ZN6TeluguC2Ev, @function
_ZN6TeluguC2Ev:
.LFB1752:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$16, %rsp	#,
	movq	%rdi, -8(%rbp)	# this, this
# multilevel.cpp:66:     Telugu(){
	movq	-8(%rbp), %rax	# this, tmp85
	addq	$40, %rax	#, _1
	movq	%rax, %rdi	# _1,
	call	_ZN14protoDravidianC2Ev	#
	movq	-8(%rbp), %rax	# this, _2
	movq	%rax, %rdi	# _2,
	call	_ZN17ClassicalSanskritC2Ev	#
	leaq	16+_ZTV6Telugu(%rip), %rdx	#, _3
	movq	-8(%rbp), %rax	# this, tmp86
	movq	%rdx, (%rax)	# _3, this_5(D)->D.44486.D.44421.D.44347.D.44298._vptr.PIE
	movq	-8(%rbp), %rax	# this, tmp87
	movl	$12, 44(%rax)	#, this_5(D)->l
# multilevel.cpp:67:         std::cout<<"Telugu called\n";
	leaq	.LC7(%rip), %rax	#, tmp88
	movq	%rax, %rsi	# tmp88,
	leaq	_ZSt4cout(%rip), %rax	#, tmp89
	movq	%rax, %rdi	# tmp89,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# multilevel.cpp:68:     }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1752:
	.size	_ZN6TeluguC2Ev, .-_ZN6TeluguC2Ev
	.weak	_ZN6TeluguC1Ev
	.set	_ZN6TeluguC1Ev,_ZN6TeluguC2Ev
	.text
	.globl	main
	.type	main, @function
main:
.LFB1754:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$64, %rsp	#,
# multilevel.cpp:72: int main(){
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp86
	movq	%rax, -8(%rbp)	# tmp86, D.49463
	xorl	%eax, %eax	# tmp86
# multilevel.cpp:76:     Telugu t;
	leaq	-64(%rbp), %rax	#, tmp84
	movq	%rax, %rdi	# tmp84,
	call	_ZN6TeluguC1Ev	#
# multilevel.cpp:77:     return 0;
	movl	$0, %eax	#, _3
# multilevel.cpp:78: }
	movq	-8(%rbp), %rdx	# D.49463, tmp87
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp87
	je	.L11	#,
	call	__stack_chk_fail@PLT	#
.L11:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1754:
	.size	main, .-main
	.weak	_ZTV6Telugu
	.section	.data.rel.ro.local._ZTV6Telugu,"awG",@progbits,_ZTV6Telugu,comdat
	.align 8
	.type	_ZTV6Telugu, @object
	.size	_ZTV6Telugu, 24
_ZTV6Telugu:
	.quad	0
	.quad	_ZTI6Telugu
	.quad	_ZN17ClassicalSanskrit6PIEfunEv
	.weak	_ZTV17ClassicalSanskrit
	.section	.data.rel.ro.local._ZTV17ClassicalSanskrit,"awG",@progbits,_ZTV17ClassicalSanskrit,comdat
	.align 8
	.type	_ZTV17ClassicalSanskrit, @object
	.size	_ZTV17ClassicalSanskrit, 24
_ZTV17ClassicalSanskrit:
	.quad	0
	.quad	_ZTI17ClassicalSanskrit
	.quad	_ZN17ClassicalSanskrit6PIEfunEv
	.weak	_ZTV13VedicSanskrit
	.section	.data.rel.ro.local._ZTV13VedicSanskrit,"awG",@progbits,_ZTV13VedicSanskrit,comdat
	.align 8
	.type	_ZTV13VedicSanskrit, @object
	.size	_ZTV13VedicSanskrit, 24
_ZTV13VedicSanskrit:
	.quad	0
	.quad	_ZTI13VedicSanskrit
	.quad	_ZN3PIE6PIEfunEv
	.weak	_ZTV11IndoIranian
	.section	.data.rel.ro.local._ZTV11IndoIranian,"awG",@progbits,_ZTV11IndoIranian,comdat
	.align 8
	.type	_ZTV11IndoIranian, @object
	.size	_ZTV11IndoIranian, 24
_ZTV11IndoIranian:
	.quad	0
	.quad	_ZTI11IndoIranian
	.quad	_ZN3PIE6PIEfunEv
	.weak	_ZTV3PIE
	.section	.data.rel.ro.local._ZTV3PIE,"awG",@progbits,_ZTV3PIE,comdat
	.align 8
	.type	_ZTV3PIE, @object
	.size	_ZTV3PIE, 24
_ZTV3PIE:
	.quad	0
	.quad	_ZTI3PIE
	.quad	_ZN3PIE6PIEfunEv
	.weak	_ZTI6Telugu
	.section	.data.rel.ro._ZTI6Telugu,"awG",@progbits,_ZTI6Telugu,comdat
	.align 8
	.type	_ZTI6Telugu, @object
	.size	_ZTI6Telugu, 56
_ZTI6Telugu:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
# <anonymous>:
	.quad	_ZTS6Telugu
# <anonymous>:
	.long	0
# <anonymous>:
	.long	2
# <anonymous>:
# <anonymous>:
	.quad	_ZTI14protoDravidian
# <anonymous>:
	.quad	10242
# <anonymous>:
	.quad	_ZTI17ClassicalSanskrit
# <anonymous>:
	.quad	2
	.weak	_ZTS6Telugu
	.section	.rodata._ZTS6Telugu,"aG",@progbits,_ZTS6Telugu,comdat
	.align 8
	.type	_ZTS6Telugu, @object
	.size	_ZTS6Telugu, 8
_ZTS6Telugu:
	.string	"6Telugu"
	.weak	_ZTI17ClassicalSanskrit
	.section	.data.rel.ro._ZTI17ClassicalSanskrit,"awG",@progbits,_ZTI17ClassicalSanskrit,comdat
	.align 8
	.type	_ZTI17ClassicalSanskrit, @object
	.size	_ZTI17ClassicalSanskrit, 24
_ZTI17ClassicalSanskrit:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
# <anonymous>:
	.quad	_ZTS17ClassicalSanskrit
# <anonymous>:
	.quad	_ZTI13VedicSanskrit
	.weak	_ZTS17ClassicalSanskrit
	.section	.rodata._ZTS17ClassicalSanskrit,"aG",@progbits,_ZTS17ClassicalSanskrit,comdat
	.align 16
	.type	_ZTS17ClassicalSanskrit, @object
	.size	_ZTS17ClassicalSanskrit, 20
_ZTS17ClassicalSanskrit:
	.string	"17ClassicalSanskrit"
	.weak	_ZTI13VedicSanskrit
	.section	.data.rel.ro._ZTI13VedicSanskrit,"awG",@progbits,_ZTI13VedicSanskrit,comdat
	.align 8
	.type	_ZTI13VedicSanskrit, @object
	.size	_ZTI13VedicSanskrit, 24
_ZTI13VedicSanskrit:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
# <anonymous>:
	.quad	_ZTS13VedicSanskrit
# <anonymous>:
	.quad	_ZTI11IndoIranian
	.weak	_ZTS13VedicSanskrit
	.section	.rodata._ZTS13VedicSanskrit,"aG",@progbits,_ZTS13VedicSanskrit,comdat
	.align 16
	.type	_ZTS13VedicSanskrit, @object
	.size	_ZTS13VedicSanskrit, 16
_ZTS13VedicSanskrit:
	.string	"13VedicSanskrit"
	.weak	_ZTI11IndoIranian
	.section	.data.rel.ro._ZTI11IndoIranian,"awG",@progbits,_ZTI11IndoIranian,comdat
	.align 8
	.type	_ZTI11IndoIranian, @object
	.size	_ZTI11IndoIranian, 24
_ZTI11IndoIranian:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
# <anonymous>:
	.quad	_ZTS11IndoIranian
# <anonymous>:
	.quad	_ZTI3PIE
	.weak	_ZTS11IndoIranian
	.section	.rodata._ZTS11IndoIranian,"aG",@progbits,_ZTS11IndoIranian,comdat
	.align 8
	.type	_ZTS11IndoIranian, @object
	.size	_ZTS11IndoIranian, 14
_ZTS11IndoIranian:
	.string	"11IndoIranian"
	.weak	_ZTI3PIE
	.section	.data.rel.ro._ZTI3PIE,"awG",@progbits,_ZTI3PIE,comdat
	.align 8
	.type	_ZTI3PIE, @object
	.size	_ZTI3PIE, 16
_ZTI3PIE:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
# <anonymous>:
	.quad	_ZTS3PIE
	.weak	_ZTS3PIE
	.section	.rodata._ZTS3PIE,"aG",@progbits,_ZTS3PIE,comdat
	.type	_ZTS3PIE, @object
	.size	_ZTS3PIE, 5
_ZTS3PIE:
	.string	"3PIE"
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2252:
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
# multilevel.cpp:78: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L14	#,
# multilevel.cpp:78: }
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L14	#,
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
.L14:
# multilevel.cpp:78: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2252:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.weak	_ZTI14protoDravidian
	.section	.data.rel.ro._ZTI14protoDravidian,"awG",@progbits,_ZTI14protoDravidian,comdat
	.align 8
	.type	_ZTI14protoDravidian, @object
	.size	_ZTI14protoDravidian, 16
_ZTI14protoDravidian:
# <anonymous>:
# <anonymous>:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
# <anonymous>:
	.quad	_ZTS14protoDravidian
	.weak	_ZTS14protoDravidian
	.section	.rodata._ZTS14protoDravidian,"aG",@progbits,_ZTS14protoDravidian,comdat
	.align 16
	.type	_ZTS14protoDravidian, @object
	.size	_ZTS14protoDravidian, 17
_ZTS14protoDravidian:
	.string	"14protoDravidian"
	.text
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2253:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# multilevel.cpp:78: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2253:
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

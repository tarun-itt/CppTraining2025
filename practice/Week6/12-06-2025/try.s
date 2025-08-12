	.file	"try.cpp"
# GNU C++17 (Ubuntu 11.4.0-1ubuntu1~22.04) version 11.4.0 (x86_64-linux-gnu)
#	compiled by GNU C version 11.4.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version isl-0.24-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -g0 -O0 -fno-asynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
	.align 8
.LC0:
	.string	"Number must be greater than zero!"
.LC1:
	.string	"Processing number: "
	.text
	.globl	_Z13processNumberi
	.type	_Z13processNumberi, @function
_Z13processNumberi:
.LFB1731:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1731
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%r12	#
	pushq	%rbx	#
	subq	$16, %rsp	#,
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -20(%rbp)	# num, num
# try.cpp:6:     if (num <= 0) {
	cmpl	$0, -20(%rbp)	#, num
	jg	.L2	#,
# try.cpp:7:         throw std::invalid_argument("Number must be greater than zero!");
	movl	$16, %edi	#,
	call	__cxa_allocate_exception@PLT	#
	movq	%rax, %rbx	# tmp86, _11
# try.cpp:7:         throw std::invalid_argument("Number must be greater than zero!");
	leaq	.LC0(%rip), %rax	#, tmp87
	movq	%rax, %rsi	# tmp87,
	movq	%rbx, %rdi	# _11,
.LEHB0:
	call	_ZNSt16invalid_argumentC1EPKc@PLT	#
.LEHE0:
# try.cpp:7:         throw std::invalid_argument("Number must be greater than zero!");
	movq	_ZNSt16invalid_argumentD1Ev@GOTPCREL(%rip), %rax	#, tmp89
	movq	%rax, %rdx	# tmp88,
	leaq	_ZTISt16invalid_argument(%rip), %rax	#, tmp90
	movq	%rax, %rsi	# tmp90,
	movq	%rbx, %rdi	# _11,
.LEHB1:
	call	__cxa_throw@PLT	#
.L2:
# try.cpp:9:     std::cout << "Processing number: " << num << std::endl;
	leaq	.LC1(%rip), %rax	#, tmp91
	movq	%rax, %rsi	# tmp91,
	leaq	_ZSt4cout(%rip), %rax	#, tmp92
	movq	%rax, %rdi	# tmp92,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rdx	#, _1
# try.cpp:9:     std::cout << "Processing number: " << num << std::endl;
	movl	-20(%rbp), %eax	# num, tmp93
	movl	%eax, %esi	# tmp93,
	movq	%rdx, %rdi	# _1,
	call	_ZNSolsEi@PLT	#
# try.cpp:9:     std::cout << "Processing number: " << num << std::endl;
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx	#, tmp95
	movq	%rdx, %rsi	# tmp94,
	movq	%rax, %rdi	# _2,
	call	_ZNSolsEPFRSoS_E@PLT	#
# try.cpp:10: }
	jmp	.L5	#
.L4:
	endbr64	
# try.cpp:7:         throw std::invalid_argument("Number must be greater than zero!");
	movq	%rax, %r12	#, tmp96
	movq	%rbx, %rdi	# _11,
	call	__cxa_free_exception@PLT	#
	movq	%r12, %rax	# tmp96, D.49155
	movq	%rax, %rdi	# D.49155,
	call	_Unwind_Resume@PLT	#
.LEHE1:
.L5:
# try.cpp:10: }
	addq	$16, %rsp	#,
	popq	%rbx	#
	popq	%r12	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1731:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1731:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1731-.LLSDACSB1731
.LLSDACSB1731:
	.uleb128 .LEHB0-.LFB1731
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L4-.LFB1731
	.uleb128 0
	.uleb128 .LEHB1-.LFB1731
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE1731:
	.text
	.size	_Z13processNumberi, .-_Z13processNumberi
	.section	.rodata
.LC2:
	.string	"Enter a positive number: "
.LC3:
	.string	"Error: "
.LC4:
	.string	"An unknown error occurred!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1732:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1732
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	pushq	%rbx	#
	subq	$40, %rsp	#,
	.cfi_offset 3, -24
# try.cpp:12: int main() {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp118
	movq	%rax, -24(%rbp)	# tmp118, D.49161
	xorl	%eax, %eax	# tmp118
# try.cpp:16:         std::cout << "Enter a positive number: ";
	leaq	.LC2(%rip), %rax	#, tmp100
	movq	%rax, %rsi	# tmp100,
	leaq	_ZSt4cout(%rip), %rax	#, tmp101
	movq	%rax, %rdi	# tmp101,
.LEHB2:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# try.cpp:17:         std::cin >> number;
	leaq	-36(%rbp), %rax	#, tmp102
	movq	%rax, %rsi	# tmp102,
	leaq	_ZSt3cin(%rip), %rax	#, tmp103
	movq	%rax, %rdi	# tmp103,
	call	_ZNSirsERi@PLT	#
# try.cpp:19:         processNumber(number);
	movl	-36(%rbp), %eax	# number, number.0_1
	movl	%eax, %edi	# number.0_1,
	call	_Z13processNumberi	#
.LEHE2:
.L10:
# try.cpp:27:     return 0;
	movl	$0, %eax	#, _40
# try.cpp:28: }
	movq	-24(%rbp), %rdx	# D.49161, tmp119
	subq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp119
	je	.L13	#,
	jmp	.L17	#
.L14:
	endbr64	
# try.cpp:21:     } catch (const std::invalid_argument& e) {
	cmpq	$1, %rdx	#, D.49158
	jne	.L9	#,
# try.cpp:21:     } catch (const std::invalid_argument& e) {
	movq	%rax, %rdi	# _2,
	call	__cxa_begin_catch@PLT	#
	movq	%rax, -32(%rbp)	# _30, e
# try.cpp:22:         std::cerr << "Error: " << e.what() << std::endl;
	leaq	.LC3(%rip), %rax	#, tmp107
	movq	%rax, %rsi	# tmp107,
	leaq	_ZSt4cerr(%rip), %rax	#, tmp108
	movq	%rax, %rdi	# tmp108,
.LEHB3:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
	movq	%rax, %rbx	#, _3
# try.cpp:22:         std::cerr << "Error: " << e.what() << std::endl;
	movq	-32(%rbp), %rax	# e, tmp109
	movq	(%rax), %rax	# e_31->D.33220.D.33059._vptr.exception, _5
	addq	$16, %rax	#, _6
	movq	(%rax), %rdx	# *_6, _7
# try.cpp:22:         std::cerr << "Error: " << e.what() << std::endl;
	movq	-32(%rbp), %rax	# e, _8
	movq	%rax, %rdi	# _8,
	call	*%rdx	# _7
	movq	%rax, %rsi	# _9,
	movq	%rbx, %rdi	# _3,
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# try.cpp:22:         std::cerr << "Error: " << e.what() << std::endl;
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx	#, tmp111
	movq	%rdx, %rsi	# tmp110,
	movq	%rax, %rdi	# _10,
	call	_ZNSolsEPFRSoS_E@PLT	#
.LEHE3:
# try.cpp:23:     } catch (...) {
	call	__cxa_end_catch@PLT	#
	jmp	.L10	#
.L9:
# try.cpp:23:     } catch (...) {
	movq	%rax, %rdi	# _11,
	call	__cxa_begin_catch@PLT	#
# try.cpp:24:         std::cerr << "An unknown error occurred!" << std::endl;
	leaq	.LC4(%rip), %rax	#, tmp112
	movq	%rax, %rsi	# tmp112,
	leaq	_ZSt4cerr(%rip), %rax	#, tmp113
	movq	%rax, %rdi	# tmp113,
.LEHB4:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT	#
# try.cpp:24:         std::cerr << "An unknown error occurred!" << std::endl;
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rdx	#, tmp115
	movq	%rdx, %rsi	# tmp114,
	movq	%rax, %rdi	# _12,
	call	_ZNSolsEPFRSoS_E@PLT	#
.LEHE4:
.LEHB5:
# try.cpp:25:     }
	call	__cxa_end_catch@PLT	#
	jmp	.L10	#
.L15:
	endbr64	
# try.cpp:23:     } catch (...) {
	movq	%rax, %rbx	#, tmp116
	call	__cxa_end_catch@PLT	#
	movq	%rbx, %rax	# tmp116, D.49159
	movq	%rax, %rdi	# D.49159,
	call	_Unwind_Resume@PLT	#
.LEHE5:
.L16:
	endbr64	
# try.cpp:25:     }
	movq	%rax, %rbx	#, tmp117
	call	__cxa_end_catch@PLT	#
	movq	%rbx, %rax	# tmp117, D.49160
	movq	%rax, %rdi	# D.49160,
.LEHB6:
	call	_Unwind_Resume@PLT	#
.LEHE6:
.L17:
# try.cpp:28: }
	call	__stack_chk_fail@PLT	#
.L13:
	movq	-8(%rbp), %rbx	#,
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1732:
	.section	.gcc_except_table
	.align 4
.LLSDA1732:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT1732-.LLSDATTD1732
.LLSDATTD1732:
	.byte	0x1
	.uleb128 .LLSDACSE1732-.LLSDACSB1732
.LLSDACSB1732:
	.uleb128 .LEHB2-.LFB1732
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L14-.LFB1732
	.uleb128 0x3
	.uleb128 .LEHB3-.LFB1732
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L15-.LFB1732
	.uleb128 0
	.uleb128 .LEHB4-.LFB1732
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L16-.LFB1732
	.uleb128 0
	.uleb128 .LEHB5-.LFB1732
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB1732
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE1732:
	.byte	0x2
	.byte	0
	.byte	0x1
	.byte	0x7d
	.align 4
	.long	0

	.long	DW.ref._ZTISt16invalid_argument-.
.LLSDATT1732:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2235:
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
# try.cpp:28: }
	cmpl	$1, -4(%rbp)	#, __initialize_p
	jne	.L20	#,
# try.cpp:28: }
	cmpl	$65535, -8(%rbp)	#, __priority
	jne	.L20	#,
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
.L20:
# try.cpp:28: }
	nop	
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2235:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z13processNumberi, @function
_GLOBAL__sub_I__Z13processNumberi:
.LFB2236:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
# try.cpp:28: }
	movl	$65535, %esi	#,
	movl	$1, %edi	#,
	call	_Z41__static_initialization_and_destruction_0ii	#
	popq	%rbp	#
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2236:
	.size	_GLOBAL__sub_I__Z13processNumberi, .-_GLOBAL__sub_I__Z13processNumberi
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z13processNumberi
	.hidden	DW.ref._ZTISt16invalid_argument
	.weak	DW.ref._ZTISt16invalid_argument
	.section	.data.rel.local.DW.ref._ZTISt16invalid_argument,"awG",@progbits,DW.ref._ZTISt16invalid_argument,comdat
	.align 8
	.type	DW.ref._ZTISt16invalid_argument, @object
	.size	DW.ref._ZTISt16invalid_argument, 8
DW.ref._ZTISt16invalid_argument:
	.quad	_ZTISt16invalid_argument
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
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

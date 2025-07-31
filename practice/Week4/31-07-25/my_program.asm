
compiled:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 82 2f 00 00    	push   0x2f82(%rip)        # 3fa8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 83 2f 00 00 	bnd jmp *0x2f83(%rip)        # 3fb0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    105f:	90                   	nop

Disassembly of section .plt.got:

0000000000001060 <__cxa_finalize@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 65 2f 00 00 	bnd jmp *0x2f65(%rip)        # 3fd0 <__cxa_finalize@GLIBC_2.2.5>
    106b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001070 <__cxa_atexit@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 3d 2f 00 00 	bnd jmp *0x2f3d(%rip)        # 3fb8 <__cxa_atexit@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001080 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	f2 ff 25 35 2f 00 00 	bnd jmp *0x2f35(%rip)        # 3fc0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@GLIBCXX_3.4>
    108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001090 <_ZNSt8ios_base4InitC1Ev@plt>:
    1090:	f3 0f 1e fa          	endbr64 
    1094:	f2 ff 25 2d 2f 00 00 	bnd jmp *0x2f2d(%rip)        # 3fc8 <_ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4>
    109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000010a0 <_start>:
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	31 ed                	xor    %ebp,%ebp
    10a6:	49 89 d1             	mov    %rdx,%r9
    10a9:	5e                   	pop    %rsi
    10aa:	48 89 e2             	mov    %rsp,%rdx
    10ad:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10b1:	50                   	push   %rax
    10b2:	54                   	push   %rsp
    10b3:	45 31 c0             	xor    %r8d,%r8d
    10b6:	31 c9                	xor    %ecx,%ecx
    10b8:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 1189 <main>
    10bf:	ff 15 13 2f 00 00    	call   *0x2f13(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    10c5:	f4                   	hlt    
    10c6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10cd:	00 00 00 

00000000000010d0 <deregister_tm_clones>:
    10d0:	48 8d 3d 39 2f 00 00 	lea    0x2f39(%rip),%rdi        # 4010 <__TMC_END__>
    10d7:	48 8d 05 32 2f 00 00 	lea    0x2f32(%rip),%rax        # 4010 <__TMC_END__>
    10de:	48 39 f8             	cmp    %rdi,%rax
    10e1:	74 15                	je     10f8 <deregister_tm_clones+0x28>
    10e3:	48 8b 05 f6 2e 00 00 	mov    0x2ef6(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10ea:	48 85 c0             	test   %rax,%rax
    10ed:	74 09                	je     10f8 <deregister_tm_clones+0x28>
    10ef:	ff e0                	jmp    *%rax
    10f1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <register_tm_clones>:
    1100:	48 8d 3d 09 2f 00 00 	lea    0x2f09(%rip),%rdi        # 4010 <__TMC_END__>
    1107:	48 8d 35 02 2f 00 00 	lea    0x2f02(%rip),%rsi        # 4010 <__TMC_END__>
    110e:	48 29 fe             	sub    %rdi,%rsi
    1111:	48 89 f0             	mov    %rsi,%rax
    1114:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1118:	48 c1 f8 03          	sar    $0x3,%rax
    111c:	48 01 c6             	add    %rax,%rsi
    111f:	48 d1 fe             	sar    %rsi
    1122:	74 14                	je     1138 <register_tm_clones+0x38>
    1124:	48 8b 05 c5 2e 00 00 	mov    0x2ec5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    112b:	48 85 c0             	test   %rax,%rax
    112e:	74 08                	je     1138 <register_tm_clones+0x38>
    1130:	ff e0                	jmp    *%rax
    1132:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <__do_global_dtors_aux>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	80 3d 05 30 00 00 00 	cmpb   $0x0,0x3005(%rip)        # 4150 <completed.0>
    114b:	75 2b                	jne    1178 <__do_global_dtors_aux+0x38>
    114d:	55                   	push   %rbp
    114e:	48 83 3d 7a 2e 00 00 	cmpq   $0x0,0x2e7a(%rip)        # 3fd0 <__cxa_finalize@GLIBC_2.2.5>
    1155:	00 
    1156:	48 89 e5             	mov    %rsp,%rbp
    1159:	74 0c                	je     1167 <__do_global_dtors_aux+0x27>
    115b:	48 8b 3d a6 2e 00 00 	mov    0x2ea6(%rip),%rdi        # 4008 <__dso_handle>
    1162:	e8 f9 fe ff ff       	call   1060 <__cxa_finalize@plt>
    1167:	e8 64 ff ff ff       	call   10d0 <deregister_tm_clones>
    116c:	c6 05 dd 2f 00 00 01 	movb   $0x1,0x2fdd(%rip)        # 4150 <completed.0>
    1173:	5d                   	pop    %rbp
    1174:	c3                   	ret    
    1175:	0f 1f 00             	nopl   (%rax)
    1178:	c3                   	ret    
    1179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001180 <frame_dummy>:
    1180:	f3 0f 1e fa          	endbr64 
    1184:	e9 77 ff ff ff       	jmp    1100 <register_tm_clones>

0000000000001189 <main>:
    1189:	f3 0f 1e fa          	endbr64 
    118d:	55                   	push   %rbp
    118e:	48 89 e5             	mov    %rsp,%rbp
    1191:	e8 7b 00 00 00       	call   1211 <_Z5greetv>
    1196:	e8 9a 00 00 00       	call   1235 <_Z14secondFileFuncv>
    119b:	b8 00 00 00 00       	mov    $0x0,%eax
    11a0:	5d                   	pop    %rbp
    11a1:	c3                   	ret    

00000000000011a2 <_Z41__static_initialization_and_destruction_0ii>:
    11a2:	f3 0f 1e fa          	endbr64 
    11a6:	55                   	push   %rbp
    11a7:	48 89 e5             	mov    %rsp,%rbp
    11aa:	48 83 ec 10          	sub    $0x10,%rsp
    11ae:	89 7d fc             	mov    %edi,-0x4(%rbp)
    11b1:	89 75 f8             	mov    %esi,-0x8(%rbp)
    11b4:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    11b8:	75 3b                	jne    11f5 <_Z41__static_initialization_and_destruction_0ii+0x53>
    11ba:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    11c1:	75 32                	jne    11f5 <_Z41__static_initialization_and_destruction_0ii+0x53>
    11c3:	48 8d 05 87 2f 00 00 	lea    0x2f87(%rip),%rax        # 4151 <_ZStL8__ioinit>
    11ca:	48 89 c7             	mov    %rax,%rdi
    11cd:	e8 be fe ff ff       	call   1090 <_ZNSt8ios_base4InitC1Ev@plt>
    11d2:	48 8d 05 2f 2e 00 00 	lea    0x2e2f(%rip),%rax        # 4008 <__dso_handle>
    11d9:	48 89 c2             	mov    %rax,%rdx
    11dc:	48 8d 05 6e 2f 00 00 	lea    0x2f6e(%rip),%rax        # 4151 <_ZStL8__ioinit>
    11e3:	48 89 c6             	mov    %rax,%rsi
    11e6:	48 8b 05 0b 2e 00 00 	mov    0x2e0b(%rip),%rax        # 3ff8 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
    11ed:	48 89 c7             	mov    %rax,%rdi
    11f0:	e8 7b fe ff ff       	call   1070 <__cxa_atexit@plt>
    11f5:	90                   	nop
    11f6:	c9                   	leave  
    11f7:	c3                   	ret    

00000000000011f8 <_GLOBAL__sub_I_main>:
    11f8:	f3 0f 1e fa          	endbr64 
    11fc:	55                   	push   %rbp
    11fd:	48 89 e5             	mov    %rsp,%rbp
    1200:	be ff ff 00 00       	mov    $0xffff,%esi
    1205:	bf 01 00 00 00       	mov    $0x1,%edi
    120a:	e8 93 ff ff ff       	call   11a2 <_Z41__static_initialization_and_destruction_0ii>
    120f:	5d                   	pop    %rbp
    1210:	c3                   	ret    

0000000000001211 <_Z5greetv>:
    1211:	f3 0f 1e fa          	endbr64 
    1215:	55                   	push   %rbp
    1216:	48 89 e5             	mov    %rsp,%rbp
    1219:	48 8d 05 e4 0d 00 00 	lea    0xde4(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1220:	48 89 c6             	mov    %rax,%rsi
    1223:	48 8d 05 16 2e 00 00 	lea    0x2e16(%rip),%rax        # 4040 <_ZSt4cout@GLIBCXX_3.4>
    122a:	48 89 c7             	mov    %rax,%rdi
    122d:	e8 4e fe ff ff       	call   1080 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    1232:	90                   	nop
    1233:	5d                   	pop    %rbp
    1234:	c3                   	ret    

0000000000001235 <_Z14secondFileFuncv>:
    1235:	f3 0f 1e fa          	endbr64 
    1239:	55                   	push   %rbp
    123a:	48 89 e5             	mov    %rsp,%rbp
    123d:	e8 cf ff ff ff       	call   1211 <_Z5greetv>
    1242:	90                   	nop
    1243:	5d                   	pop    %rbp
    1244:	c3                   	ret    

0000000000001245 <_Z41__static_initialization_and_destruction_0ii>:
    1245:	f3 0f 1e fa          	endbr64 
    1249:	55                   	push   %rbp
    124a:	48 89 e5             	mov    %rsp,%rbp
    124d:	48 83 ec 10          	sub    $0x10,%rsp
    1251:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1254:	89 75 f8             	mov    %esi,-0x8(%rbp)
    1257:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    125b:	75 3b                	jne    1298 <_Z41__static_initialization_and_destruction_0ii+0x53>
    125d:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    1264:	75 32                	jne    1298 <_Z41__static_initialization_and_destruction_0ii+0x53>
    1266:	48 8d 05 e5 2e 00 00 	lea    0x2ee5(%rip),%rax        # 4152 <_ZStL8__ioinit>
    126d:	48 89 c7             	mov    %rax,%rdi
    1270:	e8 1b fe ff ff       	call   1090 <_ZNSt8ios_base4InitC1Ev@plt>
    1275:	48 8d 05 8c 2d 00 00 	lea    0x2d8c(%rip),%rax        # 4008 <__dso_handle>
    127c:	48 89 c2             	mov    %rax,%rdx
    127f:	48 8d 05 cc 2e 00 00 	lea    0x2ecc(%rip),%rax        # 4152 <_ZStL8__ioinit>
    1286:	48 89 c6             	mov    %rax,%rsi
    1289:	48 8b 05 68 2d 00 00 	mov    0x2d68(%rip),%rax        # 3ff8 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
    1290:	48 89 c7             	mov    %rax,%rdi
    1293:	e8 d8 fd ff ff       	call   1070 <__cxa_atexit@plt>
    1298:	90                   	nop
    1299:	c9                   	leave  
    129a:	c3                   	ret    

000000000000129b <_GLOBAL__sub_I__Z14secondFileFuncv>:
    129b:	f3 0f 1e fa          	endbr64 
    129f:	55                   	push   %rbp
    12a0:	48 89 e5             	mov    %rsp,%rbp
    12a3:	be ff ff 00 00       	mov    $0xffff,%esi
    12a8:	bf 01 00 00 00       	mov    $0x1,%edi
    12ad:	e8 93 ff ff ff       	call   1245 <_Z41__static_initialization_and_destruction_0ii>
    12b2:	5d                   	pop    %rbp
    12b3:	c3                   	ret    

Disassembly of section .fini:

00000000000012b4 <_fini>:
    12b4:	f3 0f 1e fa          	endbr64 
    12b8:	48 83 ec 08          	sub    $0x8,%rsp
    12bc:	48 83 c4 08          	add    $0x8,%rsp
    12c0:	c3                   	ret    

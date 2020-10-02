
helloworld1:     file format elf32-i386


Disassembly of section .init:

00001000 <_init>:
    1000:	53                   	push   %ebx
    1001:	83 ec 08             	sub    $0x8,%esp
    1004:	e8 97 00 00 00       	call   10a0 <__x86.get_pc_thunk.bx>
    1009:	81 c3 f7 2f 00 00    	add    $0x2ff7,%ebx
    100f:	8b 83 f4 ff ff ff    	mov    -0xc(%ebx),%eax
    1015:	85 c0                	test   %eax,%eax
    1017:	74 02                	je     101b <_init+0x1b>
    1019:	ff d0                	call   *%eax
    101b:	83 c4 08             	add    $0x8,%esp
    101e:	5b                   	pop    %ebx
    101f:	c3                   	ret    

Disassembly of section .plt:

00001020 <.plt>:
    1020:	ff b3 04 00 00 00    	pushl  0x4(%ebx)
    1026:	ff a3 08 00 00 00    	jmp    *0x8(%ebx)
    102c:	00 00                	add    %al,(%eax)
	...

00001030 <printf@plt>:
    1030:	ff a3 0c 00 00 00    	jmp    *0xc(%ebx)
    1036:	68 00 00 00 00       	push   $0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <.plt>

00001040 <__libc_start_main@plt>:
    1040:	ff a3 10 00 00 00    	jmp    *0x10(%ebx)
    1046:	68 08 00 00 00       	push   $0x8
    104b:	e9 d0 ff ff ff       	jmp    1020 <.plt>

Disassembly of section .plt.got:

00001050 <__cxa_finalize@plt>:
    1050:	ff a3 f0 ff ff ff    	jmp    *-0x10(%ebx)
    1056:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00001060 <_start>:
    1060:	31 ed                	xor    %ebp,%ebp
    1062:	5e                   	pop    %esi
    1063:	89 e1                	mov    %esp,%ecx
    1065:	83 e4 f0             	and    $0xfffffff0,%esp
    1068:	50                   	push   %eax
    1069:	54                   	push   %esp
    106a:	52                   	push   %edx
    106b:	e8 22 00 00 00       	call   1092 <_start+0x32>
    1070:	81 c3 90 2f 00 00    	add    $0x2f90,%ebx
    1076:	8d 83 40 d2 ff ff    	lea    -0x2dc0(%ebx),%eax
    107c:	50                   	push   %eax
    107d:	8d 83 e0 d1 ff ff    	lea    -0x2e20(%ebx),%eax
    1083:	50                   	push   %eax
    1084:	51                   	push   %ecx
    1085:	56                   	push   %esi
    1086:	ff b3 f8 ff ff ff    	pushl  -0x8(%ebx)
    108c:	e8 af ff ff ff       	call   1040 <__libc_start_main@plt>
    1091:	f4                   	hlt    
    1092:	8b 1c 24             	mov    (%esp),%ebx
    1095:	c3                   	ret    
    1096:	66 90                	xchg   %ax,%ax
    1098:	66 90                	xchg   %ax,%ax
    109a:	66 90                	xchg   %ax,%ax
    109c:	66 90                	xchg   %ax,%ax
    109e:	66 90                	xchg   %ax,%ax

000010a0 <__x86.get_pc_thunk.bx>:
    10a0:	8b 1c 24             	mov    (%esp),%ebx
    10a3:	c3                   	ret    
    10a4:	66 90                	xchg   %ax,%ax
    10a6:	66 90                	xchg   %ax,%ax
    10a8:	66 90                	xchg   %ax,%ax
    10aa:	66 90                	xchg   %ax,%ax
    10ac:	66 90                	xchg   %ax,%ax
    10ae:	66 90                	xchg   %ax,%ax

000010b0 <deregister_tm_clones>:
    10b0:	e8 e0 00 00 00       	call   1195 <__x86.get_pc_thunk.dx>
    10b5:	81 c2 4b 2f 00 00    	add    $0x2f4b,%edx
    10bb:	8d 8a 1c 00 00 00    	lea    0x1c(%edx),%ecx
    10c1:	8d 82 1c 00 00 00    	lea    0x1c(%edx),%eax
    10c7:	39 c8                	cmp    %ecx,%eax
    10c9:	74 1d                	je     10e8 <deregister_tm_clones+0x38>
    10cb:	8b 82 ec ff ff ff    	mov    -0x14(%edx),%eax
    10d1:	85 c0                	test   %eax,%eax
    10d3:	74 13                	je     10e8 <deregister_tm_clones+0x38>
    10d5:	55                   	push   %ebp
    10d6:	89 e5                	mov    %esp,%ebp
    10d8:	83 ec 14             	sub    $0x14,%esp
    10db:	51                   	push   %ecx
    10dc:	ff d0                	call   *%eax
    10de:	83 c4 10             	add    $0x10,%esp
    10e1:	c9                   	leave  
    10e2:	c3                   	ret    
    10e3:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    10e7:	90                   	nop
    10e8:	c3                   	ret    
    10e9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

000010f0 <register_tm_clones>:
    10f0:	e8 a0 00 00 00       	call   1195 <__x86.get_pc_thunk.dx>
    10f5:	81 c2 0b 2f 00 00    	add    $0x2f0b,%edx
    10fb:	55                   	push   %ebp
    10fc:	89 e5                	mov    %esp,%ebp
    10fe:	53                   	push   %ebx
    10ff:	8d 8a 1c 00 00 00    	lea    0x1c(%edx),%ecx
    1105:	8d 82 1c 00 00 00    	lea    0x1c(%edx),%eax
    110b:	83 ec 04             	sub    $0x4,%esp
    110e:	29 c8                	sub    %ecx,%eax
    1110:	c1 f8 02             	sar    $0x2,%eax
    1113:	89 c3                	mov    %eax,%ebx
    1115:	c1 eb 1f             	shr    $0x1f,%ebx
    1118:	01 d8                	add    %ebx,%eax
    111a:	d1 f8                	sar    %eax
    111c:	74 14                	je     1132 <register_tm_clones+0x42>
    111e:	8b 92 fc ff ff ff    	mov    -0x4(%edx),%edx
    1124:	85 d2                	test   %edx,%edx
    1126:	74 0a                	je     1132 <register_tm_clones+0x42>
    1128:	83 ec 08             	sub    $0x8,%esp
    112b:	50                   	push   %eax
    112c:	51                   	push   %ecx
    112d:	ff d2                	call   *%edx
    112f:	83 c4 10             	add    $0x10,%esp
    1132:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    1135:	c9                   	leave  
    1136:	c3                   	ret    
    1137:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    113e:	66 90                	xchg   %ax,%ax

00001140 <__do_global_dtors_aux>:
    1140:	55                   	push   %ebp
    1141:	89 e5                	mov    %esp,%ebp
    1143:	53                   	push   %ebx
    1144:	e8 57 ff ff ff       	call   10a0 <__x86.get_pc_thunk.bx>
    1149:	81 c3 b7 2e 00 00    	add    $0x2eb7,%ebx
    114f:	83 ec 04             	sub    $0x4,%esp
    1152:	80 bb 1c 00 00 00 00 	cmpb   $0x0,0x1c(%ebx)
    1159:	75 27                	jne    1182 <__do_global_dtors_aux+0x42>
    115b:	8b 83 f0 ff ff ff    	mov    -0x10(%ebx),%eax
    1161:	85 c0                	test   %eax,%eax
    1163:	74 11                	je     1176 <__do_global_dtors_aux+0x36>
    1165:	83 ec 0c             	sub    $0xc,%esp
    1168:	ff b3 18 00 00 00    	pushl  0x18(%ebx)
    116e:	e8 dd fe ff ff       	call   1050 <__cxa_finalize@plt>
    1173:	83 c4 10             	add    $0x10,%esp
    1176:	e8 35 ff ff ff       	call   10b0 <deregister_tm_clones>
    117b:	c6 83 1c 00 00 00 01 	movb   $0x1,0x1c(%ebx)
    1182:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    1185:	c9                   	leave  
    1186:	c3                   	ret    
    1187:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    118e:	66 90                	xchg   %ax,%ax

00001190 <frame_dummy>:
    1190:	e9 5b ff ff ff       	jmp    10f0 <register_tm_clones>

00001195 <__x86.get_pc_thunk.dx>:
    1195:	8b 14 24             	mov    (%esp),%edx
    1198:	c3                   	ret    

00001199 <main>:
    1199:	8d 4c 24 04          	lea    0x4(%esp),%ecx
    119d:	83 e4 f0             	and    $0xfffffff0,%esp
    11a0:	ff 71 fc             	pushl  -0x4(%ecx)
    11a3:	55                   	push   %ebp
    11a4:	89 e5                	mov    %esp,%ebp
    11a6:	53                   	push   %ebx
    11a7:	51                   	push   %ecx
    11a8:	e8 28 00 00 00       	call   11d5 <__x86.get_pc_thunk.ax>
    11ad:	05 53 2e 00 00       	add    $0x2e53,%eax
    11b2:	83 ec 0c             	sub    $0xc,%esp
    11b5:	8d 90 08 e0 ff ff    	lea    -0x1ff8(%eax),%edx
    11bb:	52                   	push   %edx
    11bc:	89 c3                	mov    %eax,%ebx
    11be:	e8 6d fe ff ff       	call   1030 <printf@plt>
    11c3:	83 c4 10             	add    $0x10,%esp
    11c6:	b8 00 00 00 00       	mov    $0x0,%eax
    11cb:	8d 65 f8             	lea    -0x8(%ebp),%esp
    11ce:	59                   	pop    %ecx
    11cf:	5b                   	pop    %ebx
    11d0:	5d                   	pop    %ebp
    11d1:	8d 61 fc             	lea    -0x4(%ecx),%esp
    11d4:	c3                   	ret    

000011d5 <__x86.get_pc_thunk.ax>:
    11d5:	8b 04 24             	mov    (%esp),%eax
    11d8:	c3                   	ret    
    11d9:	66 90                	xchg   %ax,%ax
    11db:	66 90                	xchg   %ax,%ax
    11dd:	66 90                	xchg   %ax,%ax
    11df:	90                   	nop

000011e0 <__libc_csu_init>:
    11e0:	55                   	push   %ebp
    11e1:	57                   	push   %edi
    11e2:	56                   	push   %esi
    11e3:	53                   	push   %ebx
    11e4:	e8 b7 fe ff ff       	call   10a0 <__x86.get_pc_thunk.bx>
    11e9:	81 c3 17 2e 00 00    	add    $0x2e17,%ebx
    11ef:	83 ec 0c             	sub    $0xc,%esp
    11f2:	8b 6c 24 28          	mov    0x28(%esp),%ebp
    11f6:	e8 05 fe ff ff       	call   1000 <_init>
    11fb:	8d b3 f8 fe ff ff    	lea    -0x108(%ebx),%esi
    1201:	8d 83 f4 fe ff ff    	lea    -0x10c(%ebx),%eax
    1207:	29 c6                	sub    %eax,%esi
    1209:	c1 fe 02             	sar    $0x2,%esi
    120c:	74 1f                	je     122d <__libc_csu_init+0x4d>
    120e:	31 ff                	xor    %edi,%edi
    1210:	83 ec 04             	sub    $0x4,%esp
    1213:	55                   	push   %ebp
    1214:	ff 74 24 2c          	pushl  0x2c(%esp)
    1218:	ff 74 24 2c          	pushl  0x2c(%esp)
    121c:	ff 94 bb f4 fe ff ff 	call   *-0x10c(%ebx,%edi,4)
    1223:	83 c7 01             	add    $0x1,%edi
    1226:	83 c4 10             	add    $0x10,%esp
    1229:	39 fe                	cmp    %edi,%esi
    122b:	75 e3                	jne    1210 <__libc_csu_init+0x30>
    122d:	83 c4 0c             	add    $0xc,%esp
    1230:	5b                   	pop    %ebx
    1231:	5e                   	pop    %esi
    1232:	5f                   	pop    %edi
    1233:	5d                   	pop    %ebp
    1234:	c3                   	ret    
    1235:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    123c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00001240 <__libc_csu_fini>:
    1240:	c3                   	ret    

Disassembly of section .fini:

00001244 <_fini>:
    1244:	53                   	push   %ebx
    1245:	83 ec 08             	sub    $0x8,%esp
    1248:	e8 53 fe ff ff       	call   10a0 <__x86.get_pc_thunk.bx>
    124d:	81 c3 b3 2d 00 00    	add    $0x2db3,%ebx
    1253:	83 c4 08             	add    $0x8,%esp
    1256:	5b                   	pop    %ebx
    1257:	c3                   	ret    


temp:     file format elf32-i386


Disassembly of section .init:

00001000 <_init>:
    1000:	53                   	push   %ebx
    1001:	83 ec 08             	sub    $0x8,%esp
    1004:	e8 87 00 00 00       	call   1090 <__x86.get_pc_thunk.bx>
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

00001030 <__libc_start_main@plt>:
    1030:	ff a3 0c 00 00 00    	jmp    *0xc(%ebx)
    1036:	68 00 00 00 00       	push   $0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <.plt>

Disassembly of section .plt.got:

00001040 <__cxa_finalize@plt>:
    1040:	ff a3 f0 ff ff ff    	jmp    *-0x10(%ebx)
    1046:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00001050 <_start>:
    1050:	31 ed                	xor    %ebp,%ebp
    1052:	5e                   	pop    %esi
    1053:	89 e1                	mov    %esp,%ecx
    1055:	83 e4 f0             	and    $0xfffffff0,%esp
    1058:	50                   	push   %eax
    1059:	54                   	push   %esp
    105a:	52                   	push   %edx
    105b:	e8 22 00 00 00       	call   1082 <_start+0x32>
    1060:	81 c3 a0 2f 00 00    	add    $0x2fa0,%ebx
    1066:	8d 83 10 d2 ff ff    	lea    -0x2df0(%ebx),%eax
    106c:	50                   	push   %eax
    106d:	8d 83 b0 d1 ff ff    	lea    -0x2e50(%ebx),%eax
    1073:	50                   	push   %eax
    1074:	51                   	push   %ecx
    1075:	56                   	push   %esi
    1076:	ff b3 f8 ff ff ff    	pushl  -0x8(%ebx)
    107c:	e8 af ff ff ff       	call   1030 <__libc_start_main@plt>
    1081:	f4                   	hlt    
    1082:	8b 1c 24             	mov    (%esp),%ebx
    1085:	c3                   	ret    
    1086:	66 90                	xchg   %ax,%ax
    1088:	66 90                	xchg   %ax,%ax
    108a:	66 90                	xchg   %ax,%ax
    108c:	66 90                	xchg   %ax,%ax
    108e:	66 90                	xchg   %ax,%ax

00001090 <__x86.get_pc_thunk.bx>:
    1090:	8b 1c 24             	mov    (%esp),%ebx
    1093:	c3                   	ret    
    1094:	66 90                	xchg   %ax,%ax
    1096:	66 90                	xchg   %ax,%ax
    1098:	66 90                	xchg   %ax,%ax
    109a:	66 90                	xchg   %ax,%ax
    109c:	66 90                	xchg   %ax,%ax
    109e:	66 90                	xchg   %ax,%ax

000010a0 <deregister_tm_clones>:
    10a0:	e8 e0 00 00 00       	call   1185 <__x86.get_pc_thunk.dx>
    10a5:	81 c2 5b 2f 00 00    	add    $0x2f5b,%edx
    10ab:	8d 8a 18 00 00 00    	lea    0x18(%edx),%ecx
    10b1:	8d 82 18 00 00 00    	lea    0x18(%edx),%eax
    10b7:	39 c8                	cmp    %ecx,%eax
    10b9:	74 1d                	je     10d8 <deregister_tm_clones+0x38>
    10bb:	8b 82 ec ff ff ff    	mov    -0x14(%edx),%eax
    10c1:	85 c0                	test   %eax,%eax
    10c3:	74 13                	je     10d8 <deregister_tm_clones+0x38>
    10c5:	55                   	push   %ebp
    10c6:	89 e5                	mov    %esp,%ebp
    10c8:	83 ec 14             	sub    $0x14,%esp
    10cb:	51                   	push   %ecx
    10cc:	ff d0                	call   *%eax
    10ce:	83 c4 10             	add    $0x10,%esp
    10d1:	c9                   	leave  
    10d2:	c3                   	ret    
    10d3:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
    10d7:	90                   	nop
    10d8:	c3                   	ret    
    10d9:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

000010e0 <register_tm_clones>:
    10e0:	e8 a0 00 00 00       	call   1185 <__x86.get_pc_thunk.dx>
    10e5:	81 c2 1b 2f 00 00    	add    $0x2f1b,%edx
    10eb:	55                   	push   %ebp
    10ec:	89 e5                	mov    %esp,%ebp
    10ee:	53                   	push   %ebx
    10ef:	8d 8a 18 00 00 00    	lea    0x18(%edx),%ecx
    10f5:	8d 82 18 00 00 00    	lea    0x18(%edx),%eax
    10fb:	83 ec 04             	sub    $0x4,%esp
    10fe:	29 c8                	sub    %ecx,%eax
    1100:	c1 f8 02             	sar    $0x2,%eax
    1103:	89 c3                	mov    %eax,%ebx
    1105:	c1 eb 1f             	shr    $0x1f,%ebx
    1108:	01 d8                	add    %ebx,%eax
    110a:	d1 f8                	sar    %eax
    110c:	74 14                	je     1122 <register_tm_clones+0x42>
    110e:	8b 92 fc ff ff ff    	mov    -0x4(%edx),%edx
    1114:	85 d2                	test   %edx,%edx
    1116:	74 0a                	je     1122 <register_tm_clones+0x42>
    1118:	83 ec 08             	sub    $0x8,%esp
    111b:	50                   	push   %eax
    111c:	51                   	push   %ecx
    111d:	ff d2                	call   *%edx
    111f:	83 c4 10             	add    $0x10,%esp
    1122:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    1125:	c9                   	leave  
    1126:	c3                   	ret    
    1127:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    112e:	66 90                	xchg   %ax,%ax

00001130 <__do_global_dtors_aux>:
    1130:	55                   	push   %ebp
    1131:	89 e5                	mov    %esp,%ebp
    1133:	53                   	push   %ebx
    1134:	e8 57 ff ff ff       	call   1090 <__x86.get_pc_thunk.bx>
    1139:	81 c3 c7 2e 00 00    	add    $0x2ec7,%ebx
    113f:	83 ec 04             	sub    $0x4,%esp
    1142:	80 bb 18 00 00 00 00 	cmpb   $0x0,0x18(%ebx)
    1149:	75 27                	jne    1172 <__do_global_dtors_aux+0x42>
    114b:	8b 83 f0 ff ff ff    	mov    -0x10(%ebx),%eax
    1151:	85 c0                	test   %eax,%eax
    1153:	74 11                	je     1166 <__do_global_dtors_aux+0x36>
    1155:	83 ec 0c             	sub    $0xc,%esp
    1158:	ff b3 14 00 00 00    	pushl  0x14(%ebx)
    115e:	e8 dd fe ff ff       	call   1040 <__cxa_finalize@plt>
    1163:	83 c4 10             	add    $0x10,%esp
    1166:	e8 35 ff ff ff       	call   10a0 <deregister_tm_clones>
    116b:	c6 83 18 00 00 00 01 	movb   $0x1,0x18(%ebx)
    1172:	8b 5d fc             	mov    -0x4(%ebp),%ebx
    1175:	c9                   	leave  
    1176:	c3                   	ret    
    1177:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    117e:	66 90                	xchg   %ax,%ax

00001180 <frame_dummy>:
    1180:	e9 5b ff ff ff       	jmp    10e0 <register_tm_clones>

00001185 <__x86.get_pc_thunk.dx>:
    1185:	8b 14 24             	mov    (%esp),%edx
    1188:	c3                   	ret    

00001189 <main>:
    1189:	55                   	push   %ebp
    118a:	89 e5                	mov    %esp,%ebp
    118c:	83 ec 10             	sub    $0x10,%esp
    118f:	c7 45 fc 03 00 00 00 	movl   $0x3,-0x4(%ebp)
    1196:	c7 45 f8 02 00 00 00 	movl   $0x2,-0x8(%ebp)
    119d:	8b 45 fc             	mov    -0x4(%ebp),%eax
    11a0:	99                   	cltd   
    11a1:	f7 7d f8             	idivl  -0x8(%ebp)
    11a4:	89 45 f4             	mov    %eax,-0xc(%ebp)
    11a7:	b8 00 00 00 00       	mov    $0x0,%eax
    11ac:	c9                   	leave  
    11ad:	c3                   	ret    
    11ae:	66 90                	xchg   %ax,%ax

000011b0 <__libc_csu_init>:
    11b0:	55                   	push   %ebp
    11b1:	57                   	push   %edi
    11b2:	56                   	push   %esi
    11b3:	53                   	push   %ebx
    11b4:	e8 d7 fe ff ff       	call   1090 <__x86.get_pc_thunk.bx>
    11b9:	81 c3 47 2e 00 00    	add    $0x2e47,%ebx
    11bf:	83 ec 0c             	sub    $0xc,%esp
    11c2:	8b 6c 24 28          	mov    0x28(%esp),%ebp
    11c6:	e8 35 fe ff ff       	call   1000 <_init>
    11cb:	8d b3 f8 fe ff ff    	lea    -0x108(%ebx),%esi
    11d1:	8d 83 f4 fe ff ff    	lea    -0x10c(%ebx),%eax
    11d7:	29 c6                	sub    %eax,%esi
    11d9:	c1 fe 02             	sar    $0x2,%esi
    11dc:	74 1f                	je     11fd <__libc_csu_init+0x4d>
    11de:	31 ff                	xor    %edi,%edi
    11e0:	83 ec 04             	sub    $0x4,%esp
    11e3:	55                   	push   %ebp
    11e4:	ff 74 24 2c          	pushl  0x2c(%esp)
    11e8:	ff 74 24 2c          	pushl  0x2c(%esp)
    11ec:	ff 94 bb f4 fe ff ff 	call   *-0x10c(%ebx,%edi,4)
    11f3:	83 c7 01             	add    $0x1,%edi
    11f6:	83 c4 10             	add    $0x10,%esp
    11f9:	39 fe                	cmp    %edi,%esi
    11fb:	75 e3                	jne    11e0 <__libc_csu_init+0x30>
    11fd:	83 c4 0c             	add    $0xc,%esp
    1200:	5b                   	pop    %ebx
    1201:	5e                   	pop    %esi
    1202:	5f                   	pop    %edi
    1203:	5d                   	pop    %ebp
    1204:	c3                   	ret    
    1205:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
    120c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00001210 <__libc_csu_fini>:
    1210:	c3                   	ret    

Disassembly of section .fini:

00001214 <_fini>:
    1214:	53                   	push   %ebx
    1215:	83 ec 08             	sub    $0x8,%esp
    1218:	e8 73 fe ff ff       	call   1090 <__x86.get_pc_thunk.bx>
    121d:	81 c3 e3 2d 00 00    	add    $0x2de3,%ebx
    1223:	83 c4 08             	add    $0x8,%esp
    1226:	5b                   	pop    %ebx
    1227:	c3                   	ret    

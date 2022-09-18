	.data
	.comm	_Statbuf,32
	.comm	_Null,1
	.comm	_Error,128
	.data
_Sccsid:
	.byte	8:64
	.byte	8:40
	.byte	8:35
	.byte	8:41
	.byte	8:115
	.byte	8:101
	.byte	8:116
	.byte	8:117
	.byte	8:112
	.byte	8:9
	.byte	8:50
	.byte	8:46
	.byte	8:50
	.byte	0
	.byte	0
	.byte	0
	.text
	.align	1
	.globl	_setup
_setup:
	.word	.R1
	subl2	$.F1,sp
	movl	4(ap),r11
	movl	$1,-4(fp)
	.data	1
L39:
	.byte	0x73,0x65,0x74,0x75,0x70,0x20,0x70,0x6b
	.byte	0x74,0x3d,0x25,0x78,0x20,0x73,0x65,0x72
	.byte	0x69,0x61,0x6c,0x3d,0x25,0x64,0xa,0x0
	.text
	pushl	8(ap)
	pushl	r11
	pushl	$L39
	pushl	$__iob+32
	calls	$4,_fprintf
	movl	592(r11),r0
	ashl	$3,8(ap),r1
	addl2	r1,r0
	cvtlb	$1,(r0)
	movl	1636(r11),r0
	movl	20(r0),r10
L42:
	tstl	r10
	jeql	L41
	movl	592(r11),r0
	ashl	$3,r10,r1
	addl2	r1,r0
	movl	r0,r9
	.data	1
L43:
	.byte	0x25,0x64,0x20,0x25,0x64,0x20,0x25,0x64
	.byte	0xa,0x0
	.text
	pushl	4(r9)
	cvtbl	1(r9),-(sp)
	cvtbl	(r9),-(sp)
	pushl	$L43
	pushl	$__iob+32
	calls	$5,_fprintf
	tstb	(r9)
	jeql	L44
	cmpl	r10,$1
	jeql	L45
	movl	1636(r11),r0
	mull3	$28,r10,r1
	addl2	r1,r0
	tstl	20(r0)
	jneq	L45
	pushl	r11
	calls	$1,_fmterr
L45:
	movl	592(r11),r0
	movl	1636(r11),r1
	mull3	$28,r10,r2
	addl2	r2,r1
	ashl	$3,20(r1),r1
	addl2	r1,r0
	cvtlb	$1,(r0)
	movl	1636(r11),r0
	mull3	$28,r10,r1
	addl2	r1,r0
	cmpl	24(r0),564(r11)
	jleq	L47
	pushl	$4
	pushl	$-1
	pushl	r9
	calls	$3,_condset
	jbr  	L49
L47:
	.data	1
L50:
	.byte	0x6e,0x6f,0x20,0x63,0x75,0x74,0x6f,0x66
	.byte	0x66,0xa,0x0
	.text
	pushl	$L50
	pushl	$__iob+32
	calls	$2,_fprintf
	tstl	-4(fp)
	jeql	L51
	.data	1
L52:
	.byte	0x25,0x78,0x20,0x25,0x78,0x20,0x25,0x64
	.byte	0xa,0x0
	.text
	pushl	$16
	addl3	$528,r11,r0
	pushl	r0
	movl	1636(r11),r0
	mull3	$28,r10,r1
	addl2	r1,r0
	pushl	r0
	pushl	$L52
	pushl	$__iob+32
	calls	$5,_fprintf
	pushl	$16
	addl3	$528,r11,r0
	pushl	r0
	movl	1636(r11),r0
	mull3	$28,r10,r1
	addl2	r1,r0
	pushl	r0
	calls	$3,_move
L51:
	clrl	-4(fp)
	.data	1
L54:
	.byte	0x61,0x20,0x25,0x64,0x20,0x25,0x64,0x20
	.byte	0x25,0x64,0xa,0x0
	.text
	pushl	4(r9)
	cvtbl	1(r9),-(sp)
	cvtbl	(r9),-(sp)
	pushl	$L54
	pushl	$__iob+32
	calls	$5,_fprintf
	pushl	$0
	pushl	$1
	pushl	r9
	calls	$3,_condset
	.data	1
L55:
	.byte	0x62,0x20,0x25,0x64,0x20,0x25,0x64,0x20
	.byte	0x25,0x64,0xa,0x0
	.text
	pushl	4(r9)
	cvtbl	1(r9),-(sp)
	cvtbl	(r9),-(sp)
	pushl	$L55
	pushl	$__iob+32
	calls	$5,_fprintf
L49:
	jbr  	L56
L44:
	pushl	$0
	pushl	$-1
	pushl	r9
	calls	$3,_condset
L56:
	.data	1
L57:
	.byte	0x63,0x20,0x25,0x64,0x20,0x25,0x64,0x20
	.byte	0x25,0x64,0xa,0x0
	.text
	pushl	4(r9)
	cvtbl	1(r9),-(sp)
	cvtbl	(r9),-(sp)
	pushl	$L57
	pushl	$__iob+32
	calls	$5,_fprintf
	cmpb	1(r9),$1
	jneq	L58
halt
	movl	1636(r11),r0
	mull3	$28,r10,r1
	addl2	r1,r0
	addl2	$16,r0
	pushl	r0
	pushl	592(r11)
	calls	$2,_ixgsetu
L58:
L40:
	decl	r10
	jbr  	L42
L41:
L37:
	ret
	.set	.R1,0xe00
	.set	.F1,4
	.data
	.text
	.align	1
	.globl	_ixgsetu
_ixgsetu:
	.word	.R2
	subl2	$.F2,sp
	movl	8(ap),r10
L63:
	movl	r10,r9
	movl	(r9),r10
	jeql	L62
	cvtbl	4(r10),r0
	jbr  	L65
L66:
	movl	$1,-8(fp)
	movl	$1,-12(fp)
	jbr  	L64
L67:
	mnegl	$1,-8(fp)
	movl	$2,-12(fp)
	jbr  	L64
L68:
	clrl	-8(fp)
	cvtbl	$64,-12(fp)
	jbr  	L64
L65:
	cmpl	r0,$103
	jeql	L68
	cmpl	r0,$105
	jeql	L66
	cmpl	r0,$120
	jeql	L67
L64:
	addl3	$8,r10,r0
	movl	r0,r11
	.data	1
L69:
	.byte	0x69,0x78,0x67,0x73,0x65,0x74,0x75,0x70
	.byte	0x20,0x6e,0x3d,0x25,0x64,0xa,0x0
	.text
	cvtbl	5(r10),-(sp)
	pushl	$L69
	pushl	$__iob+32
	calls	$3,_fprintf
	cvtbl	5(r10),-4(fp)
L72:
	tstl	-4(fp)
	jeql	L71
	pushl	-12(fp)
	pushl	-8(fp)
	movl	4(ap),r0
	ashl	$3,(r11)+,r1
	addl2	r1,r0
	pushl	r0
	calls	$3,_condset
L70:
	decl	-4(fp)
	jbr  	L72
L71:
L61:
	jbr  	L63
L62:
L60:
	ret
	.set	.R2,0xe00
	.set	.F2,12
	.data
	.text
	.align	1
	.globl	_condset
_condset:
	.word	.R3
	subl2	$.F3,sp
	movl	4(ap),r11
	.data	1
L74:
	.byte	0x63,0x6f,0x6e,0x64,0x73,0x65,0x74,0x20
	.byte	0x25,0x78,0x20,0x25,0x64,0x20,0x25,0x64
	.byte	0xa,0x0
	.text
	pushl	12(ap)
	pushl	8(ap)
	pushl	r11
	pushl	$L74
	pushl	$__iob+32
	calls	$5,_fprintf
	tstl	8(ap)
	jneq	L75
	bisl2	12(ap),4(r11)
	jbr  	L76
L75:
	tstb	1(r11)
	jneq	L77
	cvtlb	8(ap),1(r11)
	bisl2	12(ap),4(r11)
L77:
L76:
L73:
	ret
	.set	.R3,0x800
	.set	.F3,0
	.data

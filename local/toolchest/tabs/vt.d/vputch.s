	.file	"vputch.c"
	.data
	.align	4
_Latest_:
	.space	4
	.text
	.align	4
	.globl	_vputch
_vputch:
	.word	.R1
	jbr 	.L138
.L139:
	extzv	$7,$9,4(ap),r0
	cmpl	r0,_Latest_
	jeql	.L140
	extzv	$7,$9,4(ap),_Latest_
	ashl	$7,_Latest_,r0
	pushl	r0
	calls	$1,_vidattr
.L140:
	extzv	$0,$7,4(ap),r0
	tstl	r0
	jeql	.L142
	decl	__iob+16
	jlss	.L9999
	extzv	$0,$7,4(ap),r0
	movzbl	r0,r0
	movl	__iob+20,r1
	incl	__iob+20
	cvtlb	r0,(r1)
	jbr     .L9998
.L9999:
	pushl	$__iob+16
	extzv	$0,$7,4(ap),r0
	movzbl	r0,r0
	pushl	r0
	calls	$2,__flsbuf
.L9998:
.L142:
	ret#0
	.set	.R1,0x0
.L138:
	jbr 	.L139
	.data

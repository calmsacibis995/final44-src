h31771
s 00034/00000/00000
d D 5.1 90/06/25 14:58:15 bostic 1 0
c date and time created 90/06/25 14:58:15 by bostic
e
u
U
t
T
I 1
LL0:
	.data
	.text
	.align	1
	.globl	_main
_main:
	.word	L12
	jbr 	L14
L15:
	movw	$65535,-54(fp)
	movzwl	-54(fp),r0
	cmpw	r0,$65535
	jneq	L16
	.data	1
L18:
	.ascii	"ok\12\0"
	.text
	pushl	$L18
	callf	$8,_printf
	jbr 	L19
L16:
	.data	1
L20:
	.ascii	"nope\12\0"
	.text
	pushl	$L20
	callf	$8,_printf
L19:
	ret#2
	.set	L12,0x0
L14:
	subl3	$56,fp,sp
	jbr 	L15
	.data
E 1

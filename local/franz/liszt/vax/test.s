	.globl	F00015	#(fcn lambda foo)
F00015:
	.word	0x5c0
	movab	linker,r8
	movl	r7,r10
L00016:
	subl2	r6,r7	#(foo should-have-exactly 0 args)
	cmpl	r7,$0
	jeql	L00017
	movl	r10,r7	#(arg error for fcn foo min 0 max 0)
	pushl	$1
	pushl	0(r8)
	calls	$2,_wnaerr
L00017:
	clrl	(r6)+	#(begin-fcn-body)
	#(calling print)
	#(from nil to stack)
	movl	8(r8),*4(r8)	#(from (quote b) to a)
	movl	*4(r8),(r6)+	#(from a to stack)
	movl	8(r8),*4(r8)	#(from (quote b) to a)
	movl	16(r8),*12(r8)	#(from (quote d) to c)
	movl	*12(r8),(r6)+	#(from c to stack)
	movab	-12(r6),r7
	calls	$0,*trantb+0
	movl	r7,r6
	ret
bind_org:
	.set linker_size,	5
	.set trans_size,	1
	.long	0
	.long -1
lit_org:
.asciz "foo"
.asciz "a"
.asciz "b"
.asciz "c"
.asciz "d"
.asciz "print"
.asciz "foo"
lit_end:
.data # this is just for documentation 
.asciz "@(#)Compiled by Liszt vax version 8.39a on Thu Oct 18 12:21:42 1984"
.asciz "$Header: decl.l,v 1.8 83/08/28 17:13:00 layer Exp $"
.asciz "$Header: array.l,v 1.7 83/08/28 17:12:39 layer Exp $"
.asciz "$Header: vector.l,v 1.11 83/11/22 10:13:48 jkf Exp $"
.asciz "$Header: datab.l,v 1.5 83/08/28 17:14:27 layer Exp $"
.asciz "$Header: expr.l,v 1.12 83/09/06 21:46:46 layer Exp $"
.asciz "$Header: io.l,v 1.16 83/12/06 15:50:22 sklower Exp $"
.asciz "$Header: funa.l,v 1.11 83/08/28 17:14:35 layer Exp $"
.asciz "$Header: funb.l,v 1.12 83/08/28 17:14:58 layer Exp $"
.asciz "$Header: func.l,v 1.12 83/08/28 17:12:47 layer Exp $"
.asciz "$Header: tlev.l,v 1.16 84/01/13 15:06:43 jkf Exp $"
.asciz "$Header: instr.l,v 1.7 84/01/05 18:40:55 jkf Exp $"
.asciz "$Header: fixnum.l,v 1.14 83/08/28 17:13:38 layer Exp $"
.asciz "$Header: util.l,v 1.14 83/08/28 17:13:11 layer Exp $"

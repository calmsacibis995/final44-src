	.globl	F00015	#(fcn lambda glerg)
F00015:
	.word	0x5c0
	movab	linker,r8
	movl	r7,r10
L00016:
	subl2	r6,r7
	cmpl	r7,$-4
	jeql	L00017
	movl	r10,r7
	pushl	$1002
	pushl	0(r8)
	callf	$12,_wnaerr
L00017:
	shar	$9,0(r10),r0
	cvtbl	_typetable+1[r0],r0
	shal	$2,r0,r0
	movl	_tynames+4[r0],r0
	movl	0(r0),r0
	ret
bind_org:
	.set linker_size,	1
	.set trans_size,	0
	.long	0
	.long -1
lit_org:
.asciz "glerg"
.asciz "glerg"
lit_end:
.data # this is just for documentation 
.asciz "@(#)Compiled by Liszt CCI tahoe version 8.39a on Sun Jan 11 19:40:24 1987"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/decl.l,v 1.3 86/12/04 19:47:33 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/array.l,v 1.1 86/10/20 09:46:53 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/vector.l,v 1.5 86/12/14 14:47:22 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/datab.l,v 1.1 86/10/20 09:50:52 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/expr.l,v 1.7 86/11/16 19:03:51 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/io.l,v 1.11 86/12/17 21:07:46 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/funa.l,v 1.6 86/12/16 09:06:29 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/funb.l,v 1.4 86/12/13 11:58:33 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/func.l,v 1.5 87/01/11 19:29:18 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/tlev.l,v 1.5 86/12/16 17:15:24 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/instr.l,v 1.10 86/12/13 12:00:55 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/fixnum.l,v 1.5 86/12/14 15:38:30 housel Exp $"
.asciz "$Header: /b/users/housel/lisp/liszt/RCS/util.l,v 1.4 86/12/08 09:29:34 housel Exp $"

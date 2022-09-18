.globl	F00014	#(fcn lambda test)
F00014:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	0(r10),r6
L00015:
movl	0(r8),(r6)+	#(calling print)
	#(from (quote (this is a test list)) to stack)
movab	-4(r6),r7
calls	$0,*trantb+0
movl	r7,r6
ret
bind_org:
.set linker_size,	1
.set trans_size,	1
.long	0
.long -1
lit_org:
.asciz "(this is a test list)"
.asciz "print"
.asciz "test"
lit_end:
.data  # this is just for documentation 
.asciz "@(#)Compiled by Liszt version 8.16 on Sat Nov 13 21:03:54 1982"
.asciz "@(#)decl.l	1.19 10/27/82"
.asciz "@(#)array.l	1.2	10/6/82"
.asciz "@(#)datab.l	1.6	10/19/82"
.asciz "@(#)expr.l	1.9	10/19/82"
.asciz "@(#)io.l	1.6 10/9/82"
.asciz "@(#)funa.l	1.5	10/19/82"
.asciz "@(#)funb.l	1.13	10/27/82"
.asciz "@(#)func.l	1.6	10/18/82"
.asciz "%W%	%Z%"
.asciz "@(#)fixnum.l	1.7	10/6/82"
.asciz "@(#)util.l	1.4	10/19/82"

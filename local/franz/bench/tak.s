.globl	F00007	#(fcn lambda benchmark)
F00007:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	8(r10),r6
L00008:
clrl	*0(r8)	#(from nil to count)
movl	0(r10),(r6)+	#(beginning do)
	#(from n to stack)
L00009:
tstl	*8(r10)	#(beginning not)
jneq	L00010
ashl	$-9,8(r10),r0	#(beginning not)
cmpb	_typetable+1[r0],$9
jeql	L00010
clrl	r0	#(from nil to reg)
jbr	L00011
L00010:
clrl	(r6)+	#(from nil to stack)
movl	*0(r8),(r6)+	#(from count to stack)
jsb	_qcons
movl	r0,*0(r8)	#(from reg to count)
cmpl	8(r10),$1024
jleq	L00013
cmpl	8(r10),$9212
jleq	L00014
L00013:
movl	8(r10),r0	#(from x to reg)
jsb	_qoneminus
movl	r0,8(r10)	#(from reg to x)
jbr	L00015
L00014:
subl3	$4,8(r10),8(r10)
L00015:
jbr	L00009
L00011:
subl2	$4,r6	#(calling ptime)
movab	0(r6),r7
calls	$0,*trantb+0
movl	r7,r6
movl	r0,*4(r8)	#(from reg to begin)
movl	*0(r8),(r6)+	#(beginning do)
	#(from count to stack)
L00016:
tstl	8(r10)	#(beginning not)
jneq	L00017
clrl	r0	#(from nil to reg)
jbr	L00018
L00017:
tstl	4(r10)	#(beginning cond)
	#(beginning not)
jneq	L00020
movl	$5192,(r6)+	#(calling tak)
	#(from (fixnum 18) to stack)
movl	$5168,(r6)+	#(from (fixnum 12) to stack)
movl	$5144,(r6)+	#(from (fixnum 6) to stack)
movab	-12(r6),r7
calls	$0,*trantb+8
movl	r7,r6
jbr	L00019
L00020:
movl	$5192,(r6)+	#(calling takf)
	#(from (fixnum 18) to stack)
movl	$5168,(r6)+	#(from (fixnum 12) to stack)
movl	$5144,(r6)+	#(from (fixnum 6) to stack)
movab	-12(r6),r7
calls	$0,*trantb+16
movl	r7,r6
L00019:
movl	*8(r10),8(r10)	#(fromspec (* 8 r10) to y)
jbr	L00016
L00018:
subl2	$4,r6	#(calling ptime)
movab	0(r6),r7
calls	$0,*trantb+0
movl	r7,r6
movl	r0,*8(r8)	#(from reg to end)
movl	12(r8),(r6)+	#(calling print)
	#(from (quote begin ) to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movl	*4(r8),(r6)+	#(calling print)
	#(from begin to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movab	0(r6),r7	#(calling terpr)
calls	$0,*trantb+32
movl	r7,r6
movl	16(r8),(r6)+	#(calling print)
	#(from (quote end ) to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movl	*8(r8),(r6)+	#(calling print)
	#(from end to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movab	0(r6),r7	#(calling terpr)
calls	$0,*trantb+32
movl	r7,r6
movl	20(r8),(r6)+	#(calling print)
	#(from (quote runs ) to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movl	0(r10),(r6)+	#(calling print)
	#(from n to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movab	0(r6),r7	#(calling terpr)
calls	$0,*trantb+32
movl	r7,r6
movl	24(r8),(r6)+	#(calling print)
	#(from (quote avg ) to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movl	*8(r8),r0	#(calling print)
	#(calling quotient)
	#(calling diff)
	#(from end to reg)
movl	4(r0),(r6)+	#(fromspec (4 r0) to stack)
movl	*4(r8),r0	#(from begin to reg)
movl	4(r0),(r6)+	#(fromspec (4 r0) to stack)
movab	-8(r6),r7
calls	$0,*trantb+40
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
movl	28(r8),(r6)+	#(calling times)
	#(from (quote 60.0) to stack)
movl	0(r10),(r6)+	#(from n to stack)
movab	-8(r6),r7
calls	$0,*trantb+48
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
movab	-8(r6),r7
calls	$0,*trantb+56
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
movab	-4(r6),r7
calls	$0,*trantb+24
movl	r7,r6
movab	0(r6),r7	#(calling terpr)
calls	$0,*trantb+32
movl	r7,r6
ret
.globl	F00021	#(fcn lambda tak)
F00021:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	12(r10),r6
L00022:
cmpl	*0(r10),*4(r10)	#(beginning cond)
jleq	L00024
cmpl	0(r10),$1024	#(calling tak)
	#(tail merging)
	#(calling tak)
jleq	L00025
cmpl	0(r10),$9212
jleq	L00026
L00025:
movl	0(r10),r0	#(from x to reg)
jsb	_qoneminus
movl	r0,(r6)+	#(from reg to stack)
jbr	L00027
L00026:
subl3	$4,0(r10),(r6)+
L00027:
movl	4(r10),(r6)+	#(from y to stack)
movl	8(r10),(r6)+	#(from z to stack)
movab	-12(r6),r7
calls	$0,*trantb+8
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
cmpl	4(r10),$1024	#(calling tak)
jleq	L00028
cmpl	4(r10),$9212
jleq	L00029
L00028:
movl	4(r10),r0	#(from y to reg)
jsb	_qoneminus
movl	r0,(r6)+	#(from reg to stack)
jbr	L00030
L00029:
subl3	$4,4(r10),(r6)+
L00030:
movl	8(r10),(r6)+	#(from z to stack)
movl	0(r10),(r6)+	#(from x to stack)
movab	-12(r6),r7
calls	$0,*trantb+8
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
cmpl	8(r10),$1024	#(calling tak)
jleq	L00031
cmpl	8(r10),$9212
jleq	L00032
L00031:
movl	8(r10),r0	#(from z to reg)
jsb	_qoneminus
movl	r0,(r6)+	#(from reg to stack)
jbr	L00033
L00032:
subl3	$4,8(r10),(r6)+
L00033:
movl	0(r10),(r6)+	#(from x to stack)
movl	4(r10),(r6)+	#(from y to stack)
movab	-12(r6),r7
calls	$0,*trantb+8
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
movl	-12(r6),0(r10)
movl	-8(r6),4(r10)
movl	-4(r6),8(r10)
movab	12(r10),r6
jbr	L00022
# jbr	L00023
L00024:
movl	8(r10),r0	#(from z to reg)
L00023:
ret
.globl	F00034	#(fcn lambda takf)
F00034:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	12(r10),r6
L00035:
movl	32(r8),r0	#(calling takfsub)
	#(from (quote takfsub) to r0)
movl	8(r0),(r6)+
movl	0(r10),(r6)+	#(from x to stack)
movl	4(r10),(r6)+	#(from y to stack)
movl	8(r10),(r6)+	#(from z to stack)
movab	-16(r6),r7
calls	$0,*trantb+64
movl	r7,r6
ret
.globl	F00036	#(fcn lambda takfsub)
F00036:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	16(r10),r6
L00037:
cmpl	*8(r10),*4(r10)	#(beginning cond)
	#(beginning not)
jlss	L00039
movl	12(r10),r0	#(from z to reg)
jbr	L00038
L00039:
movl	0(r10),(r6)+	#(calling 1)
	#(from f to stack)
movl	0(r10),(r6)+	#(from f to stack)
movl	0(r10),(r6)+	#(calling 1)
	#(from f to stack)
movl	0(r10),(r6)+	#(from f to stack)
cmpl	4(r10),$1024
jleq	L00040
cmpl	4(r10),$9212
jleq	L00041
L00040:
movl	4(r10),r0	#(from x to reg)
jsb	_qoneminus
movl	r0,(r6)+	#(from reg to stack)
jbr	L00042
L00041:
subl3	$4,4(r10),(r6)+
L00042:
movl	8(r10),(r6)+	#(from y to stack)
movl	12(r10),(r6)+	#(from z to stack)
movab	-16(r6),r7
movl	*-4(r7),r0
calls	$0,(r0)
movab	-4(r7),r6
movl	r0,(r6)+	#(from reg to stack)
movl	0(r10),(r6)+	#(calling 1)
	#(from f to stack)
movl	0(r10),(r6)+	#(from f to stack)
cmpl	8(r10),$1024
jleq	L00043
cmpl	8(r10),$9212
jleq	L00044
L00043:
movl	8(r10),r0	#(from y to reg)
jsb	_qoneminus
movl	r0,(r6)+	#(from reg to stack)
jbr	L00045
L00044:
subl3	$4,8(r10),(r6)+
L00045:
movl	12(r10),(r6)+	#(from z to stack)
movl	4(r10),(r6)+	#(from x to stack)
movab	-16(r6),r7
movl	*-4(r7),r0
calls	$0,(r0)
movab	-4(r7),r6
movl	r0,(r6)+	#(from reg to stack)
movab	-12(r6),r7
movl	*-4(r7),r0
calls	$0,(r0)
movab	-4(r7),r6
L00038:
ret
bind_org:
.set linker_size,	9
.set trans_size,	9
.long	0
.long	0
.long	0
.long	99
.long	0
.long -1
lit_org:
.asciz "count"
.asciz "begin"
.asciz "end"
.asciz "\"begin \""
.asciz "\"end \""
.asciz "\"runs \""
.asciz "\"avg \""
.asciz "60.0"
.asciz "takfsub"
.asciz "ptime"
.asciz "tak"
.asciz "takf"
.asciz "print"
.asciz "terpr"
.asciz "diff"
.asciz "times"
.asciz "quotient"
.asciz "takfsub"
.asciz "benchmark"
.asciz "tak"
.asciz "takf"
.ascii "(quote (defun takfsub (f x y z) (cond ((not (<& y x)) z) (t "
.ascii "(funcall f f (funcall f f (\\1- x) y z) (funcall f f (\\1- y) "
.asciz "z x))))))"
.asciz "takfsub"
lit_end:
.data  # this is just for documentation 
.asciz "@(#)Compiled by Lisp Compiler 8.0 on Wed Feb 24 08:01:50 1982"
.asciz "@(#)decl.l	1.6	2/17/82"
.asciz "@(#)array.l	1.1	9/25/81"
.asciz "@(#)datab.l	1.1	9/25/81"
.asciz "@(#)expr.l	1.1	9/25/81"
.asciz "@(#)io.l	1.1	9/25/81"
.asciz "@(#)funa.l	1.3	2/10/82"
.asciz "%W%	%G%"
.asciz "@(#)func.l	1.2	2/10/82"
.asciz "@(#)tlev.l	1.5	2/17/82"
.asciz "@(#)fixnum.l	1.6	10/21/81"
.asciz "@(#)util.l	1.2	10/7/81"

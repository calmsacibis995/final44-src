.globl	F00013	#(fcn lambda PrepareTest)
F00013:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	4(r10),r6
L00014:
clrq	(r6)+
movl	$5120,8(r10)	#(from (fixnum 0) to i)
clrl	4(r10)	#(from nil to list)
L00015:
cmpl	*0(r10),*8(r10)	#(beginning cond)
jgeq	L00018
movl	4(r10),r0	#(from list to reg)
jbr	L00016
# jbr	L00017
L00018:
clrl	r0	#(from nil to reg)
L00017:
cmpl	8(r10),$9208
jleq	L00019
movl	8(r10),r0	#(from i to reg)
jsb	_qoneplus
movl	r0,8(r10)	#(from reg to i)
jbr	L00020
L00019:
addl3	$4,8(r10),8(r10)
L00020:
clrl	(r6)+	#(from nil to stack)
movl	4(r10),(r6)+	#(from list to stack)
jsb	_qcons
movl	r0,4(r10)	#(from reg to list)
jbr	L00015
# clrl	r0	#(from nil to reg)
L00016:
ret
.globl	F00021	#(fcn lambda RealEmptyTest)
F00021:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	0(r10),r6
L00022:
clrq	(r6)+
movl	*0(r8),0(r10)	#(from TestList to l1)
L00023:
movl	*0(r8),4(r10)	#(from TestList to l2)
L00024:
movl	*4(r10),4(r10)	#(beginning cond)
	#(beginning not)
	#(fromspec (* 4 r10) to l2)
jneq	L00027
movl	*0(r10),0(r10)	#(beginning cond)
	#(beginning not)
	#(fromspec (* 0 r10) to l1)
jneq	L00029
clrl	r0	#(from nil to reg)
jbr	L00025
# jbr	L00028
L00029:
jbr	L00023
L00028:
jbr	L00026
L00027:
jbr	L00024
L00026:
clrl	r0	#(from nil to reg)
L00025:
ret
.globl	F00030	#(fcn lambda RealEmptyTest2)
F00030:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	0(r10),r6
L00031:
clrq	(r6)+
movl	*4(r8),0(r10)	#(from TestList2 to l1)
L00032:
movl	*4(r8),4(r10)	#(from TestList2 to l2)
L00033:
movl	*4(r10),r4	#(beginning cond)
	#(beginning not)
	#(fromspec (* 4 r10) to r4)
movl	0(r4),4(r10)	#(fromspec (0 r4) to l2)
jneq	L00036
movl	*0(r10),r3	#(beginning cond)
	#(beginning not)
	#(fromspec (* 0 r10) to r3)
movl	0(r3),0(r10)	#(fromspec (0 r3) to l1)
jneq	L00038
clrl	r0	#(from nil to reg)
jbr	L00034
# jbr	L00037
L00038:
jbr	L00032
L00037:
jbr	L00035
L00036:
jbr	L00033
L00035:
clrl	r0	#(from nil to reg)
L00034:
ret
.globl	F00039	#(fcn lambda time)
F00039:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	0(r10),r6
L00040:
clrl	(r6)+
movab	0(r6),r7	#(calling ptime)
calls	$0,*trantb+0
movl	r7,r6
movl	r0,0(r10)	#(from reg to time)
movl	0(r10),r4	#(list expression)
	#(fromspec (0 r10) to r4)
movl	4(r4),r0	#(fromspec (4 r4) to reg)
movl	0(r0),r5	#(fromspec (0 r0) to r5)
mull3	$17,r5,r5
moval	*$5120[r5],r0
subl3	$1024,r5,r1
blssu	L00042
jsb	_qnewint
L00042:
movl	r0,(r6)+	#(from reg to stack)
movl	*0(r10),r4	#(fromspec (* 0 r10) to r4)
movl	4(r4),r0	#(fromspec (4 r4) to reg)
movl	0(r0),r5	#(fromspec (0 r0) to r5)
mull3	$17,r5,r5
moval	*$5120[r5],r0
subl3	$1024,r5,r1
blssu	L00043
jsb	_qnewint
L00043:
movl	r0,(r6)+	#(from reg to stack)
clrl	(r6)+
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
jbr	L00041
# clrl	r0	#(from nil to reg)
L00041:
ret
.globl	F00045	#(fcn lambda benchmark)
F00045:
.word	0x5c0
movab	linker,r8
movl	r7,r10
movab	0(r10),r6
L00046:
movl	8(r8),(r6)+	#(calling princ)
	#(from (quote RealEmptyTest 1000000 ) to stack)
movab	-4(r6),r7
calls	$0,*trantb+8
movl	r7,r6
clrq	(r6)+	#(calling princ)
clrq	(r6)+
movab	0(r6),r7	#(calling time)
calls	$0,*trantb+16
movl	r7,r6
movl	r0,0(r10)	#(from reg to start)
movab	0(r6),r7	#(calling RealEmptyTest)
calls	$0,*trantb+24
movl	r7,r6
movab	0(r6),r7	#(calling time)
calls	$0,*trantb+16
movl	r7,r6
movl	r0,4(r10)	#(from reg to end)
movl	4(r10),r4	#(calling difference)
	#(fromspec (4 r10) to r4)
movl	4(r4),(r6)+	#(fromspec (4 r4) to stack)
movl	0(r10),r3	#(fromspec (0 r10) to r3)
movl	4(r3),(r6)+	#(fromspec (4 r3) to stack)
movab	-8(r6),r7
calls	$0,*trantb+32
movl	r7,r6
movl	r0,12(r10)	#(from reg to totaltime)
movl	*4(r10),r4	#(calling difference)
	#(fromspec (* 4 r10) to r4)
movl	4(r4),(r6)+	#(fromspec (4 r4) to stack)
movl	*0(r10),r3	#(fromspec (* 0 r10) to r3)
movl	4(r3),(r6)+	#(fromspec (4 r3) to stack)
movab	-8(r6),r7
calls	$0,*trantb+32
movl	r7,r6
movl	r0,8(r10)	#(from reg to gctime)
movl	12(r8),(r6)+	#(list expression)
	#(from (quote run) to stack)
movl	12(r10),(r6)+	#(calling difference)
	#(from totaltime to stack)
movl	8(r10),(r6)+	#(from gctime to stack)
movab	-8(r6),r7
calls	$0,*trantb+32
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
movl	16(r8),(r6)+	#(from (quote gc) to stack)
movl	8(r10),(r6)+	#(from gctime to stack)
movl	20(r8),(r6)+	#(from (quote total) to stack)
movl	12(r10),(r6)+	#(from totaltime to stack)
clrl	(r6)+
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
jbr	L00047
# clrl	r0	#(from nil to reg)
L00047:
subl2	$16,r6	#(from reg to stack)
movl	r0,(r6)+
movab	-4(r6),r7
calls	$0,*trantb+8
movl	r7,r6
movab	0(r6),r7	#(calling terpr)
calls	$0,*trantb+40
movl	r7,r6
movl	24(r8),(r6)+	#(calling princ)
	#(from (quote RealEmptyTest2 1000000 ) to stack)
movab	-4(r6),r7
calls	$0,*trantb+8
movl	r7,r6
clrq	(r6)+	#(calling princ)
clrq	(r6)+
movab	0(r6),r7	#(calling time)
calls	$0,*trantb+16
movl	r7,r6
movl	r0,0(r10)	#(from reg to start)
movab	0(r6),r7	#(calling RealEmptyTest2)
calls	$0,*trantb+48
movl	r7,r6
movab	0(r6),r7	#(calling time)
calls	$0,*trantb+16
movl	r7,r6
movl	r0,4(r10)	#(from reg to end)
movl	4(r10),r4	#(calling difference)
	#(fromspec (4 r10) to r4)
movl	4(r4),(r6)+	#(fromspec (4 r4) to stack)
movl	0(r10),r3	#(fromspec (0 r10) to r3)
movl	4(r3),(r6)+	#(fromspec (4 r3) to stack)
movab	-8(r6),r7
calls	$0,*trantb+32
movl	r7,r6
movl	r0,12(r10)	#(from reg to totaltime)
movl	*4(r10),r4	#(calling difference)
	#(fromspec (* 4 r10) to r4)
movl	4(r4),(r6)+	#(fromspec (4 r4) to stack)
movl	*0(r10),r3	#(fromspec (* 0 r10) to r3)
movl	4(r3),(r6)+	#(fromspec (4 r3) to stack)
movab	-8(r6),r7
calls	$0,*trantb+32
movl	r7,r6
movl	r0,8(r10)	#(from reg to gctime)
movl	12(r8),(r6)+	#(list expression)
	#(from (quote run) to stack)
movl	12(r10),(r6)+	#(calling difference)
	#(from totaltime to stack)
movl	8(r10),(r6)+	#(from gctime to stack)
movab	-8(r6),r7
calls	$0,*trantb+32
movl	r7,r6
movl	r0,(r6)+	#(from reg to stack)
movl	16(r8),(r6)+	#(from (quote gc) to stack)
movl	8(r10),(r6)+	#(from gctime to stack)
movl	20(r8),(r6)+	#(from (quote total) to stack)
movl	12(r10),(r6)+	#(from totaltime to stack)
clrl	(r6)+
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
movl	r0,(r6)+	#(from reg to stack)
jsb	_qcons
jbr	L00048
# clrl	r0	#(from nil to reg)
L00048:
subl2	$16,r6	#(from reg to stack)
movl	r0,(r6)+
movab	-4(r6),r7
calls	$0,*trantb+8
movl	r7,r6
movab	0(r6),r7	#(calling terpr)
calls	$0,*trantb+40
movl	r7,r6
ret
bind_org:
.set linker_size,	7
.set trans_size,	7
.long	0
.long	0
.long	0
.long	0
.long	99
.long	99
.long	0
.long	99
.long -1
lit_org:
.asciz "TestList"
.asciz "TestList2"
.asciz "\"RealEmptyTest 1000000 \""
.asciz "run"
.asciz "gc"
.asciz "total"
.asciz "\"RealEmptyTest2 1000000 \""
.asciz "ptime"
.asciz "princ"
.asciz "time"
.asciz "RealEmptyTest"
.asciz "difference"
.asciz "terpr"
.asciz "RealEmptyTest2"
.asciz "PrepareTest"
.asciz "RealEmptyTest"
.asciz "RealEmptyTest2"
.asciz "time"
.asciz "(setq TestList (PrepareTest 1000))"
.asciz "(setq TestList2 (PrepareTest 2000))"
.asciz "benchmark"
.asciz "(sstatus translink t)"
lit_end:
.data  # this is just for documentation 
.asciz "@(#)Compiled by Lisp Compiler 8.0 on Sun Feb 28 11:24:12 1982"
.asciz "@(#)decl.l	1.7	2/25/82"
.asciz "@(#)array.l	1.1	9/25/81"
.asciz "@(#)datab.l	1.1	9/25/81"
.asciz "@(#)expr.l	1.1	9/25/81"
.asciz "@(#)io.l	1.1	9/25/81"
.asciz "@(#)funa.l	1.3	2/10/82"
.asciz "@(#)funb.l	1.3	2/25/82"
.asciz "@(#)func.l	1.2	2/10/82"
.asciz "@(#)tlev.l	1.5	2/17/82"
.asciz "@(#)fixnum.l	1.6	10/21/81"
.asciz "@(#)util.l	1.2	10/7/81"

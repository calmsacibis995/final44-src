	.globl	F00015	|(fcn lambda compare)
F00015:
	link	a6,#-L00017
	tstb	sp@(-132)
	moveml	#L00018,a6@(-L00017)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(12),a2
L00016:
	movl	a4@(4),d6
	cmpl	a4@(8),d6
	jeq	L00020
	movl	a3@,a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a4@,a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(4),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a4@(4),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(8),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a4@(8),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00019
L00020:
	movl	a3@(12),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a4@,a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+16,a5
	jbsr	a5@
	movl	d3,a2
L00019:
	subl	#12,a2
	moveml	a6@(-L00017),#L00018
	unlk	a6
	rts
L00018 = 14528
L00017 = 20
	.globl	F00021	|(fcn lambda test)
F00021:
	link	a6,#-L00023
	tstb	sp@(-132)
	moveml	#L00024,a6@(-L00023)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@,a2
L00022:
	lea	a2@,a5	|(calling progdotest)
	movl	a5,d3
	movl	trantb+24,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling catchthrowtest)
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	moveml	a6@(-L00023),#L00024
	unlk	a6
	rts
L00024 = 14464
L00023 = 16
	.globl	F00025	|(fcn lambda progdotest)
F00025:
	link	a6,#-L00027
	tstb	sp@(-132)
	moveml	#L00028,a6@(-L00027)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@,a2
L00026:
	movl	a3@(16),a5
	movl	#_nilatom+0x1400+16,a5@
	movl	a3@(20),a2@+	|(calling compare)
	movl	d7,a2@+
	movl	d7,a2@+
	movl	_bnp,a1
	movl	a3@(16),a5
	movl	a5@,a1@+
	movl	a3@(16),a1@+
	movl	a3@(16),a5
	movl	d7,a5@
	movl	a1,_bnp
	movl	a3@(16),a5
	movl	#_nilatom+0x1400+12,a5@
	movl	#_nilatom+0x1400+16,a4@(8)
	movl	a3@(24),a2@+	|(calling compare)
	movl	#_nilatom+0x1400+12,a2@+
	movl	a3@(16),a5
	movl	a5@,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d0
L00029:
	movl	_bnp,a1
	movl	a1@(-4),a5
	movl	a1@(-8),a5@
	movl	a1,_bnp
	subql	#8,_bnp
	subql	#4,a2
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(28),a2@+	|(calling compare)
	movl	#_nilatom+0x1400+16,a2@+
	movl	a3@(16),a5
	movl	a5@,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(32),a2@+	|(calling compare)
	movl	#_nilatom+0x1400+220,a2@+
	movl	#_nilatom+0x1400+4,a2@+	|(beginning do)
	movl	#_nilatom+0x1400+0,a2@+
	movl	_bnp,a1
	movl	a3@(16),a5
	movl	a5@,a1@+
	movl	a3@(16),a1@+
	movl	a3@(16),a5
	movl	a4@(8),a5@
	movl	a1,_bnp
L00030:
	movl	a3@(16),a5
	movl	a5@,d6
	cmpl	#_nilatom+0x1400+44,d6
	jne	L00031
	movl	a4@(12),d0
	jra	L00032
L00031:
	movl	a3@(16),a5	|(calling add1)
	movl	a5@,a2@+
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a3@(16),a5	|(calling add)
	movl	a5@,a2@+
	movl	a4@(12),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a4@(12)
	movl	a3@(16),a5
	movl	a2@-,a5@
	jra	L00030
L00032:
	movl	_bnp,a1
	movl	a1@(-4),a5
	movl	a1@(-8),a5@
	movl	a1,_bnp
	subql	#8,_bnp
	subql	#8,a2
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a2@+	|(calling compare)
	movl	#_nilatom+0x1400+16,a2@+
	movl	a3@(40),a2@+	|(beginning do)
	movl	#_nilatom+0x1400+0,a2@+
L00033:
	movl	d7,d6
	cmpl	d7,d6
	jeq	L00034
	movl	d7,d0
	jra	L00035
L00034:
	cmpl	a4@(8),d7
	jne	L00037
	movl	a4@(12),d0
	jra	L00035
|	jra	L00036
L00037:
	movl	d7,d0
L00036:
	movl	a4@(8),a5
	movl	a5@,a2@+
	movl	a4@(12),d6
	cmpl	#_nilatom+0x1400+4088,d6
	jle	L00038
	movl	a4@(12),a0
	jbsr	_qoneplus
	movl	d0,a4@(12)
	jra	L00039
L00038:
	movl	a4@(12),d0
	addql	#4,d0
	movl	d0,a4@(12)
L00039:
	movl	a2@-,a4@(8)
	jra	L00033
L00035:
	subql	#8,a2
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	moveml	a6@(-L00027),#L00028
	unlk	a6
	rts
L00028 = 14528
L00027 = 20
	.globl	F00040	|(fcn lambda catchthrowtest)
F00040:
	link	a6,#-L00042
	tstb	sp@(-132)
	moveml	#L00043,a6@(-L00042)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@,a2
L00041:
	movl	a3@(44),a2@+	|(calling compare)
	movl	#_nilatom+0x1400+16,a2@+
	movl	a3@(48),d0
	movl	d7,sp@-
	movl	d0,sp@-
	movl	#2,sp@-
	jbsr	_qpushframe
	movl	d0,_errp
	tstl	_retval
	jeq	L00045
	movl	_lispretval,d0
	jra	L00044
L00045:
	movl	a3@(16),a5
	movl	#_nilatom+0x1400+16,a5@
	movl	#_nilatom+0x1400+20,a2@+	|(calling add)
	movl	#_nilatom+0x1400+16,a2@+
	movl	#_nilatom+0x1400+8,a2@+
	movl	#_nilatom+0x1400+4,a2@+
	lea	a2@(-16),a5
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(16),a5
	movl	a5@,d0
L00044:
	movl	_errp,a5
	movl	a5@(12),_errp
	movl	a5,sp
	addl	#32,sp
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(52),a2@+	|(calling compare)
	movl	a3@(56),a2@+
	movl	a3@(60),d0
	movl	d7,sp@-
	movl	d0,sp@-
	movl	#2,sp@-
	jbsr	_qpushframe
	movl	d0,_errp
	tstl	_retval
	jeq	L00047
	movl	_lispretval,d0
	jra	L00046
L00047:
	movl	a3@(16),a5
	movl	#_nilatom+0x1400+16,a5@
	movl	#_nilatom+0x1400+20,a2@+	|(calling add)
	movl	#_nilatom+0x1400+16,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(56),sp@-
	movl	a3@(60),sp@-
	movl	#3,sp@-
	jbsr	_Inonlocalgo
	movl	a3@(16),a5
	movl	a5@,d0
L00046:
	movl	_errp,a5
	movl	a5@(12),_errp
	movl	a5,sp
	addl	#32,sp
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(16),a5
	movl	a3@(64),a5@
	movl	a3@(68),a2@+	|(calling compare)
	movl	a3@(16),a5
	movl	a5@,a2@+
	movl	a3@(72),a5
	movl	a5@,d0
	movl	d0,sp@-
	movl	a3@(76),sp@-
	movl	#2,sp@-
	jbsr	_qpushframe
	movl	d0,_errp
	tstl	_retval
	jeq	L00049
	movl	_lispretval,d0
	jra	L00048
L00049:
	movl	#_nilatom+0x1400+12,a2@+	|(calling add)
	movl	#_nilatom+0x1400+16,a2@+
	movl	#_nilatom+0x1400+20,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(16),a5
	movl	a5@,d0
	movl	d0,a2@+
	movl	d7,a2@+
	jbsr	_qcons
L00048:
	movl	_errp,a5
	movl	a5@(12),_errp
	movl	a5,sp
	addl	#32,sp
	movl	d0,a0
	movl	a0@(4),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(80),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(84),a2@+	|(calling compare)
	movl	d7,a2@+
	movl	a3@(72),a5
	movl	a5@,d0
	movl	d0,sp@-
	movl	a3@(76),sp@-
	movl	#2,sp@-
	jbsr	_qpushframe
	movl	d0,_errp
	tstl	_retval
	jeq	L00051
	movl	_lispretval,d0
	jra	L00050
L00051:
	movl	a3@(88),a5
	movl	a3@(92),a5@
	movl	#_nilatom+0x1400+12,a2@+	|(calling add)
	movl	#_nilatom+0x1400+16,a2@+
	movl	a3@(96),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(100),d0
	jra	L00052
|	movl	d7,d0
L00052:
	movl	d0,a2@+
	movl	d7,a2@+
	jbsr	_qcons
L00050:
	movl	_errp,a5
	movl	a5@(12),_errp
	movl	a5,sp
	addl	#32,sp
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(104),a2@+	|(calling compare)
	movl	d7,a2@+
	movl	d7,d0
	movl	d0,sp@-
	movl	a3@(76),sp@-
	movl	#2,sp@-
	jbsr	_qpushframe
	movl	d0,_errp
	tstl	_retval
	jeq	L00054
	movl	_lispretval,d0
	jra	L00053
L00054:
	movl	#_nilatom+0x1400+12,a2@+	|(calling xxx)
	movl	a3@(108),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+64,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d0
L00055:
	movl	d0,a2@+
	movl	d7,a2@+
	jbsr	_qcons
L00053:
	movl	_errp,a5
	movl	a5@(12),_errp
	movl	a5,sp
	addl	#32,sp
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	moveml	a6@(-L00042),#L00043
	unlk	a6
	rts
L00043 = 14464
L00042 = 16
bind_org:
	linker_size = 	28
	trans_size = 	9
	.long	99
	.long	0
	.long	0
	.long	0
	.long	0
	.long -1
lit_org:
.asciz "\"error found, test \""
.asciz "\"value expected: \""
.asciz "\"value got: \""
.asciz "\"OK: \""
.asciz "x"
.asciz "\"prog not returning\""
.asciz "\"local binding in prog\""
.asciz "\"variable being un shallow bound\""
.asciz "\"do loop  simple add\""
.asciz "\"do with return\""
.asciz "(a b c d)"
.asciz "\"catch not being thrown\""
.asciz "tg"
.asciz "\"catch being thrown\""
.asciz "foobar"
.asciz "tg2"
.asciz "(a b c)"
.asciz "\"errset not taken\""
.asciz "t"
.asciz "ER%all"
.asciz "\"expect add error message \""
.asciz "\"errset being taken, with message\""
.asciz "xxx"
.asciz "234234"
.asciz "a"
.asciz "2342340"
.asciz "\"errset being taken, no message\""
.asciz "yyy"
.asciz "msg-print"
.asciz "terpr"
.asciz "drain"
.asciz "progdotest"
.asciz "catchthrowtest"
.asciz "compare"
.asciz "add1"
.asciz "add"
.asciz "xxx"
.ascii "(setq fcn-in-test2.l \"test2.l compiled by Liszt 68000 versio"
.asciz "n 8.35 on Fri Aug 19 13:13:16 1983\")"
.asciz "compare"
.asciz "test"
.asciz "progdotest"
.asciz "catchthrowtest"
lit_end:
.data | this is just for documentation 
.asciz "@(#)Compiled by Liszt 68000 version 8.35 on Fri Aug 19 13:13:28 1983"
.asciz "$Header: /na/franz/liszt/RCS/decl.l,v 1.7 83/08/12 02:46:50 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/array.l,v 1.6 83/08/12 02:46:23 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/vector.l,v 1.6 83/08/14 01:49:52 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/datab.l,v 1.4 83/08/12 02:46:43 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/expr.l,v 1.8 83/08/17 00:10:49 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/io.l,v 1.12 83/08/14 01:49:17 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/funa.l,v 1.9 83/08/15 19:23:28 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/funb.l,v 1.7 83/08/14 19:32:33 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/func.l,v 1.9 83/08/14 01:48:27 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/tlev.l,v 1.10 83/08/12 02:48:48 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/instr.l,v 1.3 83/08/15 19:25:49 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/fixnum.l,v 1.10 83/08/15 19:21:20 layer Exp $"
.asciz "$Header: /na/franz/liszt/RCS/util.l,v 1.11 83/08/17 00:09:26 layer Exp $"

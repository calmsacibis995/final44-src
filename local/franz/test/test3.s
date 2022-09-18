	.globl	F00015	|(fcn lambda test)
F00015:
	link	a6,#-L00017
	tstb	sp@(-132)
	moveml	#L00018,a6@(-L00017)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@,a2
L00016:
	movl	a3@,a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(4),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(8),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(12),a2@+	|(calling copy)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+16,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a3@(20),a0
	movl	a3@(16),a0@(4)
	movl	a0,d0
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00025
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+24,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00026
	jra	L00023
L00025:
	subql	#8,a2
L00026:
	movl	a3@(24),a2@+	|(calling copy)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+16,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a3@(32),a0
	movl	a3@(28),a0@
	movl	a0,d0
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00027
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+24,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00028
	jra	L00023
L00027:
	subql	#8,a2
L00028:
	movl	a3@(36),d0
	jra	L00022
L00023:
	movl	d7,d0
L00022:
	movl	d7,d6
	cmpl	d0,d6
	jne	L00021
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00020
L00021:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
L00020:
	movl	a3@,a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(48),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(8),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	#_nilatom+0x1400+400,a2@+
	movl	#_nilatom+0x1400+400,a2@+	|(calling tloop)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00032
	movl	a3@(36),d0
	jra	L00031
L00032:
	movl	d7,d0
L00031:
	movl	d7,d6
	cmpl	d0,d6
	jne	L00030
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00029
L00030:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
L00029:
	movl	d7,d0
L00019:
	moveml	a6@(-L00017),#L00018
	unlk	a6
	rts
L00018 = 14528
L00017 = 20
	.globl	F00033	|(fcn lambda tloop)
F00033:
	link	a6,#-L00035
	tstb	sp@(-132)
	moveml	#L00036,a6@(-L00035)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(4),a2
L00034:
	movl	d7,a2@+
	movl	#_nilatom+0x1400+4,a4@(4)
L00037:
	movl	a4@(4),d6
	cmpl	a4@,d6
	jne	L00040
	movl	a4@(4),d0
	jra	L00038
|	jra	L00039
L00040:
	movl	a4@(4),a2@+	|(calling add1)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a4@(4)
	jra	L00037
L00039:
	movl	d7,d0
L00038:
	subql	#8,a2
	moveml	a6@(-L00035),#L00036
	unlk	a6
	rts
L00036 = 14528
L00035 = 20
bind_org:
	linker_size = 	13
	trans_size = 	8
	.long	99
	.long	0
	.long	0
	.long -1
lit_org:
.asciz "\"Testing \""
.asciz "\"rplac[ad]\""
.asciz "\"...\""
.asciz "(replaced-element 2 3 4 5 6 7 8)"
.asciz "replaced-element"
.asciz "(1 2 3 4 5 6 7 8)"
.asciz "(1 replaced-element)"
.asciz "(replaced-element)"
.asciz "(1 2 3 4 5 6 7 8)"
.asciz "t"
.asciz "\"failed -- breaking.\""
.asciz "\"done.\""
.asciz "\"loops and go\""
.asciz "msg-print"
.asciz "drain"
.asciz "copy"
.asciz "equal"
.asciz "terpr"
.asciz "*break"
.asciz "tloop"
.asciz "add1"
.ascii "(setq fcn-in-test3.l \"test3.l compiled by Liszt 68000 versio"
.asciz "n 8.35 on Fri Aug 19 13:13:33 1983\")"
.asciz "test"
.asciz "tloop"
lit_end:
.data | this is just for documentation 
.asciz "@(#)Compiled by Liszt 68000 version 8.35 on Fri Aug 19 13:13:41 1983"
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

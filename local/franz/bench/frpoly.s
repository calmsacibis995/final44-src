	.globl	F00020	|(fcn lambda pcoefadd)
F00020:
	link	a6,#-L00022
	tstb	sp@(-132)
	moveml	#L00023,a6@(-L00022)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(12),a2
L00021:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00025
	movl	a4@(4),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00025
	movl	a4@(8),d0
	jra	L00024
L00025:
	movl	a4@,a2@+
	movl	a4@(4),a2@+
	movl	a4@(8),a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
L00024:
	subl	#12,a2
	moveml	a6@(-L00022),#L00023
	unlk	a6
	rts
L00023 = 15488
L00022 = 20
	.globl	F00029	|(fcn lambda pcplus)
F00029:
	link	a6,#-L00031
	tstb	sp@(-132)
	moveml	#L00032,a6@(-L00031)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00030:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00034
	movl	a4@(4),a2@+	|(calling plus)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+8,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00033
L00034:
	movl	a4@(4),a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@,a2@+	|(calling pcplus1)
	movl	a4@(4),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+16,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
L00033:
	subql	#8,a2
	moveml	a6@(-L00031),#L00032
	unlk	a6
	rts
L00032 = 15488
L00031 = 20
	.globl	F00037	|(fcn lambda pcplus1)
F00037:
	link	a6,#-L00039
	tstb	sp@(-132)
	moveml	#L00040,a6@(-L00039)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00038:
	cmpl	a4@(4),d7
	jne	L00042
	movl	a4@,d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00044
	movl	a4@,a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00044
	movl	d7,d0
	jra	L00043
L00044:
	movl	#_nilatom+0x1400+0,a2@+
	movl	a4@,a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
L00043:
	jra	L00041
L00042:
	movl	a4@(4),a1
	movl	a1@(4),a2@+
	movl	a4@(8),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00049
	movl	a4@(8),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	jra	L00052
L00049:
	movl	d7,d0
L00052:
	subql	#4,a2
	cmpl	d0,d7
	jeq	L00048
	movl	#_nilatom+0x1400+0,a2@+	|(calling pcoefadd)
	movl	a4@,a2@+	|(calling pplus)
	movl	a4@(4),a5
	movl	a5@,a1
	movl	a1@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+32,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	d7,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+40,a5
	jbsr	a5@
	lea	a2@(-12),a2
	jra	L00041
L00048:
	movl	a4@(4),a1
	movl	a1@(4),a2@+
	movl	a4@(4),a5
	movl	a5@,a0
	movl	a0@(4),a2@+
	movl	a4@,a2@+	|(calling pcplus1)
	movl	a4@(4),a5
	movl	a5@,a1
	movl	a1@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+16,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
L00041:
	subql	#8,a2
	moveml	a6@(-L00039),#L00040
	unlk	a6
	rts
L00040 = 15488
L00039 = 20
	.globl	F00053	|(fcn lambda pctimes)
F00053:
	link	a6,#-L00055
	tstb	sp@(-132)
	moveml	#L00056,a6@(-L00055)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00054:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00058
	movl	a4@,a2@+	|(calling times)
	movl	a4@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+48,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00057
L00058:
	movl	a4@(4),a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@,a2@+	|(calling pctimes1)
	movl	a4@(4),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+56,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
L00057:
	subql	#8,a2
	moveml	a6@(-L00055),#L00056
	unlk	a6
	rts
L00056 = 15488
L00055 = 20
	.globl	F00061	|(fcn lambda pctimes1)
F00061:
	link	a6,#-L00063
	tstb	sp@(-132)
	moveml	#L00064,a6@(-L00063)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00062:
	cmpl	a4@(4),d7
	jne	L00066
	movl	d7,d0
	jra	L00065
L00066:
	movl	a4@(4),a1	|(calling pcoefadd)
	movl	a1@(4),a2@+
	movl	a4@,a2@+	|(calling ptimes)
	movl	a4@(4),a5
	movl	a5@,a0
	movl	a0@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a4@,a2@+	|(calling pctimes1)
	movl	a4@(4),a5
	movl	a5@,a1
	movl	a1@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+56,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+40,a5
	jbsr	a5@
	lea	a2@(-12),a2
L00065:
	subql	#8,a2
	moveml	a6@(-L00063),#L00064
	unlk	a6
	rts
L00064 = 15488
L00063 = 20
	.globl	F00067	|(fcn lambda pplus)
F00067:
	link	a6,#-L00069
	tstb	sp@(-132)
	moveml	#L00070,a6@(-L00069)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00068:
	movl	a4@,d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00072
	movl	a4@,a2@+	|(calling pcplus)
	movl	a4@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+72,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00071
L00072:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00075
	movl	a4@(4),a2@+	|(calling pcplus)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+72,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00071
L00075:
	movl	a4@,a1
	movl	a1@(4),a2@+
	movl	a4@(4),a0
	movl	a0@(4),d0
	movl	a2@-,d1
	cmpl	d0,d1
	jne	L00078
	movl	a4@,a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@(4),a5	|(calling pplus1)
	movl	a5@,a2@+
	movl	a4@,a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+80,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00071
L00078:
	movl	a4@,a0
	movl	a0@(4),a2@+
	movl	a3@,a2@+
	jbsr	_qget
	movl	d0,a0
	movl	a0@,a2@+
	movl	a4@(4),a1
	movl	a1@(4),a2@+
	movl	a3@,a2@+
	jbsr	_qget
	movl	d0,a0
	movl	a0@,d0
	movl	a2@-,d1
	cmpl	d0,d1
	jle	L00079
	movl	a4@,a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@(4),a2@+	|(calling pcplus1)
	movl	a4@,a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+16,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00071
L00079:
	movl	a4@(4),a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@,a2@+	|(calling pcplus1)
	movl	a4@(4),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+16,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
L00071:
	subql	#8,a2
	moveml	a6@(-L00069),#L00070
	unlk	a6
	rts
L00070 = 15488
L00069 = 20
	.globl	F00080	|(fcn lambda pplus1)
F00080:
	link	a6,#-L00082
	tstb	sp@(-132)
	moveml	#L00083,a6@(-L00082)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00081:
	cmpl	a4@,d7
	jne	L00085
	movl	a4@(4),d0
	jra	L00084
L00085:
	cmpl	a4@(4),d7
	jne	L00086
	movl	a4@,d0
	jra	L00084
L00086:
	movl	a4@,a1
	movl	a1@(4),a0
	movl	a0@,a2@+
	movl	a4@(4),a0
	movl	a0@(4),a0
	movl	a0@,d0
	movl	a2@-,d1
	cmpl	d0,d1
	jne	L00087
	movl	a4@,a1	|(calling pcoefadd)
	movl	a1@(4),a2@+
	movl	a4@,a5	|(calling pplus)
	movl	a5@,a0
	movl	a0@(4),a2@+
	movl	a4@(4),a5
	movl	a5@,a1
	movl	a1@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+32,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a4@,a5	|(calling pplus1)
	movl	a5@,a1
	movl	a1@,a2@+
	movl	a4@(4),a5
	movl	a5@,a0
	movl	a0@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+80,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+40,a5
	jbsr	a5@
	lea	a2@(-12),a2
	jra	L00084
L00087:
	movl	a4@,a0
	movl	a0@(4),a0
	movl	a0@,a2@+
	movl	a4@(4),a0
	movl	a0@(4),a0
	movl	a0@,d0
	movl	a2@-,d1
	cmpl	d0,d1
	jle	L00088
	movl	a4@,a1
	movl	a1@(4),a2@+
	movl	a4@,a5
	movl	a5@,a0
	movl	a0@(4),a2@+
	movl	a4@,a5	|(calling pplus1)
	movl	a5@,a1
	movl	a1@,a2@+
	movl	a4@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+80,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	jra	L00084
L00088:
	movl	a4@(4),a1
	movl	a1@(4),a2@+
	movl	a4@(4),a5
	movl	a5@,a0
	movl	a0@(4),a2@+
	movl	a4@,a2@+	|(calling pplus1)
	movl	a4@(4),a5
	movl	a5@,a1
	movl	a1@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+80,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
L00084:
	subql	#8,a2
	moveml	a6@(-L00082),#L00083
	unlk	a6
	rts
L00083 = 15488
L00082 = 20
	.globl	F00089	|(fcn lambda psimp)
F00089:
	link	a6,#-L00091
	tstb	sp@(-132)
	moveml	#L00092,a6@(-L00091)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00090:
	cmpl	a4@(4),d7
	jne	L00094
	movl	#_nilatom+0x1400+0,d0
	jra	L00093
L00094:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00095
	movl	a4@(4),d0
	jra	L00093
L00095:
	movl	a4@(4),a1	|(calling zerop)
	movl	a1@(4),a2@+
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00098
	movl	a4@(4),a5
	movl	a5@,a1
	movl	a1@(4),d0
	jra	L00093
L00098:
	movl	a4@,a2@+
	movl	a4@(4),a2@+
	jbsr	_qcons
L00093:
	subql	#8,a2
	moveml	a6@(-L00091),#L00092
	unlk	a6
	rts
L00092 = 15488
L00091 = 20
	.globl	F00099	|(fcn lambda ptimes)
F00099:
	link	a6,#-L00101
	tstb	sp@(-132)
	moveml	#L00102,a6@(-L00101)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00100:
	movl	a4@,d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00106
	movl	a4@,a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jne	L00105
L00106:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00104
	movl	a4@(4),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00104
L00105:
	movl	#_nilatom+0x1400+0,d0
	jra	L00103
L00104:
	movl	a4@,d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00112
	movl	a4@,a2@+	|(calling pctimes)
	movl	a4@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+88,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00103
L00112:
	movl	a4@(4),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#1783,d0
	jeq	L00115
	movl	a4@(4),a2@+	|(calling pctimes)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+88,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00103
L00115:
	movl	a4@,a1
	movl	a1@(4),a2@+
	movl	a4@(4),a0
	movl	a0@(4),d0
	movl	a2@-,d1
	cmpl	d0,d1
	jne	L00118
	movl	a4@,a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@,a5	|(calling ptimes1)
	movl	a5@,a2@+
	movl	a4@(4),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+96,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00103
L00118:
	movl	a4@,a0
	movl	a0@(4),a2@+
	movl	a3@,a2@+
	jbsr	_qget
	movl	d0,a0
	movl	a0@,a2@+
	movl	a4@(4),a1
	movl	a1@(4),a2@+
	movl	a3@,a2@+
	jbsr	_qget
	movl	d0,a0
	movl	a0@,d0
	movl	a2@-,d1
	cmpl	d0,d1
	jle	L00119
	movl	a4@,a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@(4),a2@+	|(calling pctimes1)
	movl	a4@,a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+56,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
	jra	L00103
L00119:
	movl	a4@(4),a1	|(calling psimp)
	movl	a1@(4),a2@+
	movl	a4@,a2@+	|(calling pctimes1)
	movl	a4@(4),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+56,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+24,a5
	jbsr	a5@
	lea	a2@(-8),a2
L00103:
	subql	#8,a2
	moveml	a6@(-L00101),#L00102
	unlk	a6
	rts
L00102 = 15488
L00101 = 20
	.globl	F00120	|(fcn lambda ptimes1)
F00120:
	link	a6,#-L00122
	tstb	sp@(-132)
	moveml	#L00123,a6@(-L00122)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00121:
	movl	_bnp,a1
	movl	a3@(4),a5
	movl	a5@,a1@+
	movl	a3@(4),a1@+
	movl	a3@(4),a5
	movl	a4@,a5@
	movl	a1,_bnp
	movl	_bnp,a1
	movl	a3@(8),a5
	movl	a5@,a1@+
	movl	a3@(8),a1@+
	movl	a3@(8),a5
	movl	d7,a5@
	movl	a3@(12),a5
	movl	a5@,a1@+
	movl	a3@(12),a1@+
	movl	a3@(12),a5
	movl	d7,a5@
	movl	a1,_bnp
	movl	a4@(4),a2@+	|(calling ptimes2)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+104,a5
	jbsr	a5@
	lea	a2@(-4),a2
	movl	a3@(12),a5
	movl	d0,a5@
	movl	a3@(12),a5
	movl	a5@,d6
	movl	a3@(8),a5
	movl	d6,a5@
L00124:
	movl	a3@(4),a5
	movl	a5@,a0
	movl	a0@,a5
	movl	a5@,d6
	movl	a3@(4),a5
	movl	d6,a5@
	movl	a3@(4),a5
	cmpl	a5@,d7
	jne	L00127
	movl	a3@(12),a5
	movl	a5@,d0
	jra	L00125
| 	jra	L00126
L00127:
	movl	d7,d0
L00126:
	movl	a4@(4),a2@+	|(calling ptimes3)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+112,a5
	jbsr	a5@
	lea	a2@(-4),a2
	jra	L00124
| 	movl	d7,d0
L00125:
	movl	_bnp,a1
	movl	a1@(-4),a5
	movl	a1@(-8),a5@
	movl	a1@(-12),a5
	movl	a1@(-16),a5@
	movl	a1,_bnp
	subl	#16,_bnp
	movl	_bnp,a1
	movl	a1@(-4),a5
	movl	a1@(-8),a5@
	movl	a1,_bnp
	subql	#8,_bnp
	subql	#8,a2
	moveml	a6@(-L00122),#L00123
	unlk	a6
	rts
L00123 = 15552
L00122 = 24
	.globl	F00128	|(fcn lambda ptimes2)
F00128:
	link	a6,#-L00130
	tstb	sp@(-132)
	moveml	#L00131,a6@(-L00130)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(4),a2
L00129:
	cmpl	a4@,d7
	jne	L00133
	movl	d7,d0
	jra	L00132
L00133:
	movl	a3@(4),a5	|(calling pcoefadd)
	|(calling plus)
	movl	a5@,a0
	movl	a0@(4),a2@+
	movl	a4@,a1
	movl	a1@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+8,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a3@(4),a5	|(calling ptimes)
	movl	a5@,a0
	movl	a0@,a1
	movl	a1@(4),a2@+
	movl	a4@,a5
	movl	a5@,a0
	movl	a0@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a4@,a5	|(calling ptimes2)
	movl	a5@,a1
	movl	a1@,a2@+
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+104,a5
	jbsr	a5@
	lea	a2@(-4),a2
	movl	d0,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+40,a5
	jbsr	a5@
	lea	a2@(-12),a2
L00132:
	subql	#4,a2
	moveml	a6@(-L00130),#L00131
	unlk	a6
	rts
L00131 = 15488
L00130 = 20
	.globl	F00134	|(fcn lambda ptimes3)
F00134:
	link	a6,#-L00136
	tstb	sp@(-132)
	moveml	#L00137,a6@(-L00136)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(4),a2
L00135:
	movl	d7,a2@+
	movl	d7,a2@+
	movl	d7,a2@+
L00138:
	cmpl	a4@,d7
	jne	L00146
	movl	d7,d0
	jra	L00144
| 	jra	L00145
L00146:
	movl	d7,d0
L00145:
	movl	a3@(4),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	d2,sp@-
	movl	a4@,a1
	movl	a1@(4),a0
	movl	a0@,d2
	movl	sp@+,d0
	addl	d2,d0
	movl	d0,d2
	movl	d2,d0
	asll	#2,d0
	addl	#_nilatom+0x1400,d0
	movl	d2,d1
	subl	#1024,d1
	jcs	L00147
	movl	a2,_np
	movl	a2,_lbot
	jbsr	_qnewint
L00147:
	movl	d0,a4@(4)
	movl	a4@,a5	|(calling ptimes)
	movl	a5@,a1
	movl	a1@(4),a2@+
	movl	a3@(4),a5
	movl	a5@,a0
	movl	a0@,a0
	movl	a0@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@(12)
	movl	a4@(12),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00149
	movl	a4@(12),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00149
	movl	a4@,a5
	movl	a5@,a1
	movl	a1@,a4@
	jra	L00138
| 	jra	L00148
L00149:
	movl	a3@(8),a5
	cmpl	a5@,d7
	jeq	L00154
	movl	a4@(4),a5
	movl	a5@,a2@+
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d0
	movl	a2@-,d1
	cmpl	d0,d1
	jle	L00153
L00154:
	movl	a3@(12),a5	|(calling pplus1)
	movl	a5@,a2@+
	movl	a4@(4),a2@+
	movl	a4@(12),a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+80,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(8),a5
	movl	d0,a5@
	movl	a3@(8),a5
	movl	a5@,d6
	movl	a3@(12),a5
	movl	d6,a5@
	movl	a4@,a5
	movl	a5@,a1
	movl	a1@,a4@
	jra	L00138
| 	jra	L00148
L00153:
	movl	a4@(4),a5
	movl	a5@,a2@+
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d0
	movl	a2@-,d1
	cmpl	d0,d1
	jne	L00155
	movl	a4@(12),a2@+	|(calling pplus)
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a1
	movl	a1@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+32,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@(12)
	movl	a4@(12),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00157
	movl	a4@(12),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00157
	movl	a3@(12),a5	|(calling pdiffer1)
	movl	a5@,a2@+
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@(4),a2@+
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a1
	movl	a1@(4),a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+120,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(8),a5
	movl	d0,a5@
	movl	a3@(8),a5
	movl	a5@,d6
	movl	a3@(12),a5
	movl	d6,a5@
	jra	L00156
L00157:
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a0
	movl	a4@(12),a0@(4)
	movl	a0,d0
L00156:
	movl	a4@,a5
	movl	a5@,a1
	movl	a1@,a4@
	jra	L00138
| 	jra	L00148
L00155:
	movl	d7,d0
L00148:
L00139:
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a5
	cmpl	a5@,d7
	jeq	L00162
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a5
	movl	a5@,a1
	movl	a1@(4),a0
	movl	a0@,d0
	movl	a4@(4),a5
	cmpl	a5@,d0
	jle	L00162
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a5
	movl	a5@,d6
	movl	a3@(8),a5
	movl	d6,a5@
	jra	L00139
| 	jra	L00161
L00162:
	movl	d7,d0
L00161:
	movl	a3@(8),a5
	movl	a5@,a0
	movl	a0@,a4@(8)
L00140:
	movl	a4@(8),a5
	cmpl	a5@,d7
	jeq	L00166
	movl	a4@(8),a5	|(calling lessp)
	movl	a5@,a1
	movl	a1@(4),a2@+
	movl	a4@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+128,a5
	jbsr	a5@
	lea	a2@(-8),a2
	cmpl	d0,d7
	jeq	L00165
L00166:
	movl	a4@(8),a2@+
	movl	a4@(4),a2@+
	movl	a4@(12),a2@+
	movl	a4@(8),a5
	movl	a5@,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,d1
	movl	a2@-,a0
	movl	d1,a0@
	movl	a0,d0
	jra	L00141
| 	jra	L00164
L00165:
	movl	d7,d0
L00164:
	movl	a4@(8),a5	|(calling pplus)
	movl	a5@,a1
	movl	a1@,a0
	movl	a0@(4),a2@+
	movl	a4@(12),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+32,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@(12)
	movl	a4@(12),a2@+
	movl	a4@(16),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	moveq	#1,d1
	asll	d0,d1
	movl	d1,d0
	andw	#532,d0
	jeq	L00169
	movl	a4@(16),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	jra	L00172
L00169:
	movl	d7,d0
L00172:
	subql	#4,a2
	cmpl	d0,d7
	jeq	L00168
	movl	a4@(8),a2@+
	movl	a4@(8),a5
	movl	a5@,a1
	movl	a1@,a5
	movl	a5@,d1
	movl	a2@-,a0
	movl	d1,a0@
	movl	a0,d0
	jra	L00142
| 	jra	L00167
L00168:
	movl	a4@(8),a5
	movl	a5@,a1
	movl	a1@,a0
	movl	a4@(12),a0@(4)
	movl	a0,d0
L00167:
L00141:
	movl	a4@(8),a5
	movl	a5@,a1
	movl	a1@,a4@(8)
L00142:
	movl	a4@,a5
	movl	a5@,a1
	movl	a1@,a4@
	cmpl	a4@,d7
	jne	L00174
	movl	d7,d0
	jra	L00144
| 	jra	L00173
L00174:
	movl	d7,d0
L00173:
	movl	a3@(4),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	d2,sp@-
	movl	a4@,a1
	movl	a1@(4),a0
	movl	a0@,d2
	movl	sp@+,d0
	addl	d2,d0
	movl	d0,d2
	movl	d2,d0
	asll	#2,d0
	addl	#_nilatom+0x1400,d0
	movl	d2,d1
	subl	#1024,d1
	jcs	L00175
	movl	a2,_np
	movl	a2,_lbot
	jbsr	_qnewint
L00175:
	movl	d0,a4@(4)
	movl	a4@,a5	|(calling ptimes)
	movl	a5@,a1
	movl	a1@(4),a2@+
	movl	a3@(4),a5
	movl	a5@,a0
	movl	a0@,a0
	movl	a0@(4),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@(12)
L00143:
	movl	a4@(8),a5
	cmpl	a5@,d7
	jeq	L00177
	movl	a4@(8),a5
	movl	a5@,a1
	movl	a1@(4),a0
	movl	a0@,d0
	movl	a4@(4),a5
	cmpl	a5@,d0
	jle	L00177
	movl	a4@(8),a5
	movl	a5@,a1
	movl	a1@,a4@(8)
	jra	L00143
| 	jra	L00176
L00177:
	movl	d7,d0
L00176:
	jra	L00140
| 	movl	d7,d0
L00144:
	subl	#16,a2
	moveml	a6@(-L00136),#L00137
	unlk	a6
	rts
L00137 = 15552
L00136 = 24
	.globl	F00179	|(fcn lambda pexptsq)
F00179:
	link	a6,#-L00181
	tstb	sp@(-132)
	moveml	#L00182,a6@(-L00181)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00180:
	movl	a4@(4),a2@+	|(beginning do)
	|(calling quotient)
	movl	#_nilatom+0x1400+8,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+136,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a4@(4),a2@+	|(calling oddp)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+144,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00186
	movl	a4@,d0
	jra	L00185
L00186:
	movl	#_nilatom+0x1400+4,d0
L00185:
	movl	d0,a2@+
L00183:
	movl	a4@(8),a2@+	|(calling zerop)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+0,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00184
	movl	a4@(12),d0
	jra	L00187
L00184:
	movl	a4@,a2@+	|(calling ptimes)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@
	movl	a4@(8),a2@+	|(calling oddp)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+144,a5
	jbsr	a5@
	lea	a2@(-4),a2
	cmpl	d0,d7
	jeq	L00188
	movl	a4@(12),a2@+	|(calling ptimes)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@(12)
L00188:
	movl	a4@(8),a2@+	|(calling quotient)
	movl	#_nilatom+0x1400+8,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+136,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a4@(8)
	jra	L00183
L00187:
	subl	#16,a2
	moveml	a6@(-L00181),#L00182
	unlk	a6
	rts
L00182 = 15488
L00181 = 20
	.globl	F00189	|(fcn lambda setup)
F00189:
	link	a6,#-L00191
	tstb	sp@(-132)
	moveml	#L00192,a6@(-L00191)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@,a2
L00190:
	movl	a3@(16),a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+4,a2@+
	movl	a3@,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+152,a5
	jbsr	a5@
	lea	a2@(-12),a2
	movl	a3@(20),a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+8,a2@+
	movl	a3@,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+152,a5
	jbsr	a5@
	lea	a2@(-12),a2
	movl	a3@(24),a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+12,a2@+
	movl	a3@,a2@+
	lea	a2@(-12),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+152,a5
	jbsr	a5@
	lea	a2@(-12),a2
	movl	a3@(32),a2@+	|(calling pplus)
	movl	a3@(36),a2@+	|(calling pplus)
	movl	a3@(40),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+32,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+32,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(28),a5
	movl	d0,a5@
	movl	a3@(28),a5	|(calling ptimes)
	movl	a5@,a2@+
	movl	a3@(48),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(44),a5
	movl	d0,a5@
	movl	a3@(28),a5	|(calling ptimes)
	movl	a5@,a2@+
	movl	a3@(56),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+64,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(52),a5
	movl	d0,a5@
	movl	a3@(52),a5
	movl	a5@,d0
	moveml	a6@(-L00191),#L00192
	unlk	a6
	rts
L00192 = 15488
L00191 = 20
	.globl	F00193	|(fcn lambda bench)
F00193:
	link	a6,#-L00195
	tstb	sp@(-132)
	moveml	#L00196,a6@(-L00195)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(4),a2
L00194:
	lea	a2@,a5	|(calling ptime)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+160,a5
	jbsr	a5@
	lea	a2@,a2
	movl	a3@(60),a5
	movl	d0,a5@
	movl	a3@(28),a5	|(calling pexptsq)
	movl	a5@,a2@+
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+168,a5
	jbsr	a5@
	lea	a2@(-8),a2
	lea	a2@,a5	|(calling ptime)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+160,a5
	jbsr	a5@
	lea	a2@,a2
	movl	a3@(64),a5
	movl	d0,a5@
	movl	a3@(44),a5	|(calling pexptsq)
	movl	a5@,a2@+
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+168,a5
	jbsr	a5@
	lea	a2@(-8),a2
	lea	a2@,a5	|(calling ptime)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+160,a5
	jbsr	a5@
	lea	a2@,a2
	movl	a3@(68),a5
	movl	d0,a5@
	movl	a3@(52),a5	|(calling pexptsq)
	movl	a5@,a2@+
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+168,a5
	jbsr	a5@
	lea	a2@(-8),a2
	lea	a2@,a5	|(calling ptime)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+160,a5
	jbsr	a5@
	lea	a2@,a2
	movl	a3@(72),a5
	movl	d0,a5@
	movl	a3@(76),a2@+
	movl	a4@,a2@+
	movl	a3@(60),a5	|(calling b1)
	movl	a5@,a2@+
	movl	a3@(64),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+176,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a3@(64),a5	|(calling b1)
	movl	a5@,a2@+
	movl	a3@(68),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+176,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a3@(68),a5	|(calling b1)
	movl	a5@,a2@+
	movl	a3@(72),a5
	movl	a5@,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+176,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	subql	#4,a2
	moveml	a6@(-L00195),#L00196
	unlk	a6
	rts
L00196 = 15488
L00195 = 20
	.globl	F00197	|(fcn lambda b1)
F00197:
	link	a6,#-L00199
	tstb	sp@(-132)
	moveml	#L00200,a6@(-L00199)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@(8),a2
L00198:
	movl	_bnp,a1
	movl	a3@(60),a5
	movl	a5@,a1@+
	movl	a3@(60),a1@+
	movl	a3@(60),a5
	movl	a4@,a5@
	movl	a1,_bnp
	movl	a3@(80),a2@+
	movl	a4@(4),a1	|(calling quotient)
	movl	a1@(4),a0
	movl	a0@,d2
	movl	d2,sp@-
	movl	a3@(60),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	sp@+,d0
	subl	d2,d0
	movl	d0,d2
	movl	d2,d0
	asll	#2,d0
	addl	#_nilatom+0x1400,d0
	movl	d2,d1
	subl	#1024,d1
	jcs	L00201
	movl	a2,_np
	movl	a2,_lbot
	jbsr	_qnewint
L00201:
	movl	d0,a2@+
	movl	a4@(8),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+136,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a4@(4),a5	|(calling quotient)
	movl	a5@,a1
	movl	a1@(4),a0
	movl	a0@,d2
	movl	d2,sp@-
	movl	a3@(60),a5
	movl	a5@,a0
	movl	a0@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	sp@+,d0
	subl	d2,d0
	movl	d0,d2
	movl	d2,d0
	asll	#2,d0
	addl	#_nilatom+0x1400,d0
	movl	d2,d1
	subl	#1024,d1
	jcs	L00202
	movl	a2,_np
	movl	a2,_lbot
	jbsr	_qnewint
L00202:
	movl	d0,a2@+
	movl	a4@(8),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+136,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	a4@(4),a1	|(calling quotient)
	movl	a1@(4),a0
	movl	a0@,d2
	movl	d2,sp@-
	movl	a3@(60),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	sp@+,d0
	subl	d2,d0
	movl	d0,d2
	movl	d2,sp@-
	movl	a4@(4),a5
	movl	a5@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	d2,sp@-
	movl	a3@(60),a5
	movl	a5@,a0
	movl	a0@,a0
	movl	a0@(4),a0
	movl	a0@,d2
	movl	sp@+,d0
	subl	d2,d0
	movl	d0,d2
	movl	sp@+,d0
	subl	d2,d0
	movl	d0,d2
	movl	d2,d0
	asll	#2,d0
	addl	#_nilatom+0x1400,d0
	movl	d2,d1
	subl	#1024,d1
	jcs	L00203
	movl	a2,_np
	movl	a2,_lbot
	jbsr	_qnewint
L00203:
	movl	d0,a2@+
	movl	a4@(8),a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+136,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	d0,a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	subql	#4,a2
	movl	_bnp,a1
	movl	a1@(-4),a5
	movl	a1@(-8),a5@
	movl	a1,_bnp
	subql	#8,_bnp
	subql	#8,a2
	moveml	a6@(-L00199),#L00200
	unlk	a6
	rts
L00200 = 15488
L00199 = 20
	.globl	F00204	|(fcn lambda frp-bench)
F00204:
	link	a6,#-L00206
	tstb	sp@(-132)
	moveml	#L00207,a6@(-L00206)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	_lbot,a4
	lea	a4@,a2
L00205:
	movl	a3@(84),a5
	movl	a3@(88),a5@
	movl	a3@(92),a2@+	|(calling allocate)
	movl	#_nilatom+0x1400+2000,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+184,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(96),a2@+	|(calling allocate)
	movl	#_nilatom+0x1400+400,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+184,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(100),a2@+	|(calling allocate)
	movl	#_nilatom+0x1400+280,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+184,a5
	jbsr	a5@
	lea	a2@(-8),a2
	movl	a3@(104),a2@+	|(calling allocate)
	movl	#_nilatom+0x1400+120,a2@+
	lea	a2@(-8),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+184,a5
	jbsr	a5@
	lea	a2@(-8),a2
	lea	a2@,a5	|(calling setup)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+192,a5
	jbsr	a5@
	lea	a2@,a2
	movl	#_nilatom+0x1400+8,a2@+	|(calling print)
	|(calling bench)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+200,a5
	jbsr	a5@
	lea	a2@(-4),a2
	movl	d0,a2@+
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+208,a5
	jbsr	a5@
	lea	a2@(-4),a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+216,a5
	jbsr	a5@
	lea	a2@,a2
	movl	#_nilatom+0x1400+20,a2@+	|(calling print)
	|(calling bench)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+200,a5
	jbsr	a5@
	lea	a2@(-4),a2
	movl	d0,a2@+
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+208,a5
	jbsr	a5@
	lea	a2@(-4),a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+216,a5
	jbsr	a5@
	lea	a2@,a2
	movl	#_nilatom+0x1400+40,a2@+	|(calling print)
	|(calling bench)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+200,a5
	jbsr	a5@
	lea	a2@(-4),a2
	movl	d0,a2@+
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+208,a5
	jbsr	a5@
	lea	a2@(-4),a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+216,a5
	jbsr	a5@
	lea	a2@,a2
	movl	#_nilatom+0x1400+60,a2@+	|(calling print)
	|(calling bench)
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+200,a5
	jbsr	a5@
	lea	a2@(-4),a2
	movl	d0,a2@+
	lea	a2@(-4),a5
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+208,a5
	jbsr	a5@
	lea	a2@(-4),a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,_lbot
	movl	a2,_np
	movl	trantb+216,a5
	jbsr	a5@
	lea	a2@,a2
	moveml	a6@(-L00206),#L00207
	unlk	a6
	rts
L00207 = 15488
L00206 = 20
bind_org:
	linker_size = 	27
	trans_size = 	28
	.long	99
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long -1
lit_org:
.asciz "order"
.asciz "*x*"
.asciz "v"
.asciz "u*"
.asciz "x"
.asciz "y"
.asciz "z"
.asciz "r"
.asciz "(x 1 1 0 1)"
.asciz "(y 1 1)"
.asciz "(z 1 1)"
.asciz "r2"
.asciz "100000"
.asciz "r3"
.asciz "1.0"
.asciz "start"
.asciz "res1"
.asciz "res2"
.asciz "res3"
.asciz "power="
.asciz "60.0"
.asciz "float-format"
.asciz "\"%.5G\""
.asciz "list"
.asciz "fixnum"
.asciz "bignum"
.asciz "flonum"
.asciz "zerop"
.asciz "plus"
.asciz "pcplus1"
.asciz "psimp"
.asciz "pplus"
.asciz "pcoefadd"
.asciz "times"
.asciz "pctimes1"
.asciz "ptimes"
.asciz "pcplus"
.asciz "pplus1"
.asciz "pctimes"
.asciz "ptimes1"
.asciz "ptimes2"
.asciz "ptimes3"
.asciz "pdiffer1"
.asciz "lessp"
.asciz "quotient"
.asciz "oddp"
.asciz "putprop"
.asciz "ptime"
.asciz "pexptsq"
.asciz "b1"
.asciz "allocate"
.asciz "setup"
.asciz "bench"
.asciz "print"
.asciz "terpr"
.ascii "(quote (declare (localf pcoefadd pcplus pcplus1 pplus ptimes"
.asciz " ptimes1 ptimes2 ptimes3 psimp pctimes pctimes1 pplus1)))"
.asciz "pcoefadd"
.asciz "pcplus"
.asciz "pcplus1"
.asciz "pctimes"
.asciz "pctimes1"
.asciz "pplus"
.asciz "pplus1"
.asciz "psimp"
.asciz "ptimes"
.asciz "ptimes1"
.asciz "ptimes2"
.asciz "ptimes3"
.asciz "pexptsq"
.asciz "setup"
.asciz "bench"
.asciz "b1"
.asciz "frp-bench"
lit_end:
.data	| this is just for documentation
.asciz "@(#)Compiled by Liszt M68000 version 8.20 on Fri Feb  4 10:59:30 1983"
.asciz "$Header: /na/franz/68k/liszt/RCS/decl.l,v 1.6 83/01/29 00:51:11 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/array.l,v 1.2 83/01/29 00:51:01 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/datab.l,v 1.3 83/01/29 00:51:08 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/expr.l,v 1.7 83/01/29 00:51:15 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/io.l,v 1.17 83/01/29 00:51:40 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/funa.l,v 1.19 83/01/31 00:30:06 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/funb.l,v 1.7 83/01/29 00:51:30 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/func.l,v 1.9 83/01/31 00:33:26 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/tlev.l,v 1.13 83/01/29 00:51:44 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/fixnum.l,v 1.7 83/01/29 00:51:20 layer Exp $"
.asciz "$Header: /na/franz/68k/liszt/RCS/util.l,v 1.10 83/01/29 00:51:51 layer Exp $"

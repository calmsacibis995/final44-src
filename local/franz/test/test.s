	.globl	F00015	|(fcn lambda nlist)
F00015:
	link	a6,#-L00017
	tstb	sp@(-132)
	moveml	#L00018,a6@(-L00017)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(4),a2
L00016:
	movl	#_nilatom+0x1400+4,a2@+	|(beginning do)
	movl	d7,a2@+
L00019:
	movl	a4@(4),a2@+	|(calling greaterp)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00020
	movl	a4@(8),d0
	jra	L00021
L00020:
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400+4088,d6
	jle	L00022
	movl	a4@(4),a0
	jbsr	_qoneplus
	movl	d0,a2@+
	jra	L00023
L00022:
	movl	a4@(4),d0
	addql	#4,d0
	movl	d0,a2@+
L00023:
	movl	a4@(4),a2@+
	movl	a4@(8),a2@+
	jbsr	_qcons
	movl	d0,a4@(8)
	movl	a2@-,a4@(4)
	jra	L00019
L00021:
	subl	#12,a2
	moveml	a6@(-L00017),#L00018
	unlk	a6
	rts
L00018 = 14528
L00017 = 20
	.globl	F00024	|(fcn lambda tfact)
F00024:
	link	a6,#-L00026
	tstb	sp@(-132)
	moveml	#L00027,a6@(-L00026)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(4),a2
L00025:
	movl	#_nilatom+0x1400+12,a2@+	|(calling greaterp)
	movl	a4@,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00029
	movl	a4@,d0
	jra	L00028
L00029:
	movl	a4@,a2@+	|(calling times)
	movl	a4@,a2@+	|(calling tfact)
	|(calling difference)
	movl	#_nilatom+0x1400+4,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+8,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+16,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+24,a5
	jbsr	a5@
	movl	d3,a2
L00028:
	subql	#4,a2
	moveml	a6@(-L00026),#L00027
	unlk	a6
	rts
L00027 = 14528
L00026 = 20
	.globl	F00030	|(fcn lambda tget)
F00030:
	link	a6,#-L00032
	tstb	sp@(-132)
	moveml	#L00033,a6@(-L00032)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(8),a2
L00031:
	movl	a4@,a2@+
	movl	a4@(4),a2@+
	jbsr	_qget
	subql	#8,a2
	moveml	a6@(-L00032),#L00033
	unlk	a6
	rts
L00033 = 14464
L00032 = 16
	.globl	F00034	|(fcn lambda tmemq)
F00034:
	link	a6,#-L00036
	tstb	sp@(-132)
	moveml	#L00037,a6@(-L00036)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(8),a2
L00035:
	movl	a4@,d5
	movl	a4@(4),d0
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00039
	movl	d0,a0
L00040:
	cmpl	a0@(4),d5
	jeq	L00038
	movl	a0@,a0
	cmpl	a0,d7
	jne	L00040
	movl	a0,d0
L00039:
	movl	d0,d0
	jra	L00041
L00038:
	movl	a0,d0
L00041:
	subql	#8,a2
	moveml	a6@(-L00036),#L00037
	unlk	a6
	rts
L00037 = 14560
L00036 = 24
	.globl	F00042	|(fcn lambda ttype)
F00042:
	link	a6,#-L00044
	tstb	sp@(-132)
	moveml	#L00045,a6@(-L00044)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(4),a2
L00043:
	movl	a4@,d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	addl	d0,a5
	movb	a5@,d0
	extw	d0
	extl	d0
	asll	#2,d0
	lea	_tynames+4,a5
	addl	d0,a5
	movl	a5@,a5
	movl	a5@,d0
	subql	#4,a2
	moveml	a6@(-L00044),#L00045
	unlk	a6
	rts
L00045 = 14464
L00044 = 16
	.globl	F00047	|(fcn lexpr lexpr-argtest)
F00047:
	link	a6,#-L00049
	tstb	sp@(-132)
	moveml	#L00050,a6@(-L00049)
	movl	#_nilatom,d7
	lea	linker,a3
L00048:
	movl	a2,a5
	subl	d3,a5
	addl	#_nilatom+0x1400+0,a5
	movl	a5,a2@+
	movl	a2,a4
	movl	a5,a2@+
	movl	a4@(-4),a2@+	|(calling greaterp)
	movl	#_nilatom+0x1400+0,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00052
	movl	a4@,a2@+	|(beginning do)
	movl	d7,a2@+
L00055:
	movl	a4@(4),a2@+	|(calling lessp)
	movl	#_nilatom+0x1400+4,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00056
	movl	a4@(8),d0
	jra	L00057
|	jra	L00057
L00056:
	movl	a4@(4),d0
	cmpl	a4@(4),d7
	jeq	L00058
	movl	d0,d6
	cmpl	#_nilatom+0x1400+0,d6
	jeq	L00058
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),a2@+
	jra	L00059
L00058:
	movl	a4@(-4),a2@+
L00059:
	movl	a4@(8),a2@+
	jbsr	_qcons
	movl	d0,a4@(8)
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400-4096,d6
	jle	L00060
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400+4092,d6
	jle	L00061
L00060:
	movl	a4@(4),a0
	jbsr	_qoneminus
	movl	d0,a4@(4)
	jra	L00062
L00061:
	movl	a4@(4),d0
	subql	#4,d0
	movl	d0,a4@(4)
L00062:
	jra	L00055
L00057:
	subql	#8,a2
	jra	L00051
L00052:
	movl	d7,d0
L00051:
	subql	#4,a2
	moveml	a6@(-L00049),#L00050
	unlk	a6
	rts
L00050 = 14528
L00049 = 20
	.globl	F00063	|(fcn lexpr lexpr-setargtest)
F00063:
	link	a6,#-L00065
	tstb	sp@(-132)
	moveml	#L00066,a6@(-L00065)
	movl	#_nilatom,d7
	lea	linker,a3
L00064:
	movl	a2,a5
	subl	d3,a5
	addl	#_nilatom+0x1400+0,a5
	movl	a5,a2@+
	movl	a2,a4
	movl	a5,a2@+
	movl	#_nilatom+0x1400+12,d2
	movl	a3@,d0
	subl	a4@(-4),d2
	lea	a4@(-8,d2:L),a5
	movl	d0,a5@
	movl	a4@,d2
	movl	a3@(4),d0
	subl	a4@(-4),d2
	lea	a4@(-8,d2:L),a5
	movl	d0,a5@
	movl	#_nilatom+0x1400+4,d2
	movl	a3@(8),d0
	subl	a4@(-4),d2
	lea	a4@(-8,d2:L),a5
	movl	d0,a5@
	movl	a4@(-4),a2@+	|(calling greaterp)
	movl	#_nilatom+0x1400+0,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+0,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00068
	movl	a4@,a2@+	|(beginning do)
	movl	d7,a2@+
L00071:
	movl	a4@(4),a2@+	|(calling lessp)
	movl	#_nilatom+0x1400+4,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+32,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00072
	movl	a4@(8),d0
	jra	L00073
|	jra	L00073
L00072:
	movl	a4@(4),d0
	cmpl	a4@(4),d7
	jeq	L00074
	movl	d0,d6
	cmpl	#_nilatom+0x1400+0,d6
	jeq	L00074
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),a2@+
	jra	L00075
L00074:
	movl	a4@(-4),a2@+
L00075:
	movl	a4@(8),a2@+
	jbsr	_qcons
	movl	d0,a4@(8)
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400-4096,d6
	jle	L00076
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400+4092,d6
	jle	L00077
L00076:
	movl	a4@(4),a0
	jbsr	_qoneminus
	movl	d0,a4@(4)
	jra	L00078
L00077:
	movl	a4@(4),d0
	subql	#4,d0
	movl	d0,a4@(4)
L00078:
	jra	L00071
L00073:
	subql	#8,a2
	jra	L00067
L00068:
	movl	d7,d0
L00067:
	subql	#4,a2
	moveml	a6@(-L00065),#L00066
	unlk	a6
	rts
L00066 = 14528
L00065 = 20
	.globl	F00079	|(fcn lexpr lexpr-tail-merge)
F00079:
	link	a6,#-L00081
	tstb	sp@(-132)
	moveml	#L00082,a6@(-L00081)
	movl	#_nilatom,d7
	lea	linker,a3
L00080:
	movl	a2,a5
	subl	d3,a5
	addl	#_nilatom+0x1400+0,a5
	movl	a5,a2@+
	movl	a2,a4
	movl	a5,a2@+
	movl	#_nilatom+0x1400+4,d0
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),a0
	movl	a0@,a2@+
	movl	#_nilatom+0x1400+8,d0
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),a0
	movl	a0@,d0
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00084
	movl	#_nilatom+0x1400+8,d0
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),d0
	jra	L00083
L00084:
	movl	#_nilatom+0x1400+4,d0	|(calling lexpr-tail-merge)
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),a0
	movl	a0,d6
	cmpl	#_nilatom+0x1400+4088,d6
	jle	L00091
	jbsr	_qoneplus
	movl	d0,a2@+
	jra	L00092
L00091:
	movl	a0,d0
	addql	#4,d0
	movl	d0,a2@+
L00092:
	movl	#_nilatom+0x1400+8,d0
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),a2@+
	movl	d3,a5
	movl	a4@(-4),a5
	movl	a5@,d6
	asll	#2,d6
	movl	d6,a5
	subl	a5,a4
	movl	a4,a5
	subql	#4,a5
	movl	a2@(-8),a5@
	movl	a2@(-4),a5@(4)
	movl	a5,a2
	addql	#8,a2
	jra	L00080
L00083:
	subql	#4,a2
	moveml	a6@(-L00081),#L00082
	unlk	a6
	rts
L00082 = 14528
L00081 = 20
	.globl	F00097	|(fcn lexpr lexpr-cc)
F00097:
	link	a6,#-L00099
	tstb	sp@(-132)
	moveml	#L00100,a6@(-L00099)
	movl	#_nilatom,d7
	lea	linker,a3
L00098:
	movl	a2,a5
	subl	d3,a5
	addl	#_nilatom+0x1400+0,a5
	movl	a5,a2@+
	movl	a2,a4
	movl	a5,a2@+
	movl	a4@,d6
	cmpl	a3@(12),d6
	jne	L00102
	movl	#_nilatom+0x1400+4,d0
	subl	a4@(-4),d0
	cmpl	a4@(-8,d0:L),d7
	jne	L00104
	movl	#_nilatom+0x1400+8,d0
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),d0
	jra	L00103
L00104:
	movl	#_nilatom+0x1400+4,d0
	subl	a4@(-4),d0
	movl	a4@(-8,d0:L),d0
L00103:
	jra	L00101
L00102:
	movl	a4@,d0
L00101:
	subql	#4,a2
	moveml	a6@(-L00099),#L00100
	unlk	a6
	rts
L00100 = 14528
L00099 = 20
	.globl	F00111	|(fcn lambda tail-merge)
F00111:
	link	a6,#-L00113
	tstb	sp@(-132)
	moveml	#L00114,a6@(-L00113)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(4),a2
L00112:
	movl	#_nilatom+0x1400+4,a2@+
	movl	a4@,a2@+	|(calling length)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00116
	movl	a4@,a1
	movl	a1@(4),d0
	jra	L00115
L00116:
	movl	a4@,a5	|(calling tail-merge)
	movl	a5@,a2@+
	movl	d3,a5
	movl	a4,a5
	movl	a2@(-4),a5@
	movl	a5,a2
	addql	#4,a2
	jra	L00112
L00115:
	subql	#4,a2
	moveml	a6@(-L00113),#L00114
	unlk	a6
	rts
L00114 = 14528
L00113 = 20
	.globl	F00117	|(fcn lambda tail-merge2)
F00117:
	link	a6,#-L00119
	tstb	sp@(-132)
	moveml	#L00120,a6@(-L00119)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@(12),a2
L00118:
	movl	a4@,a5
	movl	a5@,d6
	cmpl	#0,d6
	jpl	L00122
	movl	a4@,a2@+
	movl	a4@(4),a2@+
	movl	a4@(8),a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	movl	d0,a2@+
	jbsr	_qcons
	jra	L00121
L00122:
	movl	a4@(8),d6	|(calling tail-merge2)
	cmpl	#_nilatom+0x1400-4096,d6
	jle	L00123
	movl	a4@(8),d6
	cmpl	#_nilatom+0x1400+4092,d6
	jle	L00124
L00123:
	movl	a4@(8),a0
	jbsr	_qoneminus
	movl	d0,a2@+
	jra	L00125
L00124:
	movl	a4@(8),d0
	subql	#4,d0
	movl	d0,a2@+
L00125:
	movl	a4@,d6
	cmpl	#_nilatom+0x1400-4096,d6
	jle	L00126
	movl	a4@,d6
	cmpl	#_nilatom+0x1400+4092,d6
	jle	L00127
L00126:
	movl	a4@,a0
	jbsr	_qoneminus
	movl	d0,a2@+
	jra	L00128
L00127:
	movl	a4@,d0
	subql	#4,d0
	movl	d0,a2@+
L00128:
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400-4096,d6
	jle	L00129
	movl	a4@(4),d6
	cmpl	#_nilatom+0x1400+4092,d6
	jle	L00130
L00129:
	movl	a4@(4),a0
	jbsr	_qoneminus
	movl	d0,a2@+
	jra	L00131
L00130:
	movl	a4@(4),d0
	subql	#4,d0
	movl	d0,a2@+
L00131:
	movl	d3,a5
	movl	a4,a5
	movl	a2@(-12),a5@
	movl	a2@(-8),a5@(4)
	movl	a2@(-4),a5@(8)
	movl	a5,a2
	addl	#12,a2
	jra	L00118
L00121:
	subl	#12,a2
	moveml	a6@(-L00119),#L00120
	unlk	a6
	rts
L00120 = 14528
L00119 = 20
	.globl	F00132	|(fcn lambda test)
F00132:
	link	a6,#-L00134
	tstb	sp@(-132)
	moveml	#L00135,a6@(-L00134)
	movl	#_nilatom,d7
	lea	linker,a3
	movl	d3,a4
	lea	a4@,a2
L00133:
	movl	d7,a2@+
	movl	d7,a2@+
	movl	d7,a2@+
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(20),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(28),a2@+
	movl	a3@(32),a2@+	|(calling length)
	|(calling nlist)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+64,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+40,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00139
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00140
	jra	L00138
L00139:
	subql	#8,a2
L00140:
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00142
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00141
L00142:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00141:
	jra	L00137
L00138:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00144
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00143
L00144:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00143:
L00137:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(48),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	#_nilatom+0x1400+800,a2@+	|(calling tfact)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+16,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a3@(52),a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00147
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00148
	jra	L00146
L00147:
	subql	#8,a2
L00148:
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00150
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00149
L00150:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00149:
	jra	L00145
L00146:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00152
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00151
L00152:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00151:
L00145:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(56),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	#_nilatom+0x1400+4,a4@
	movl	#_nilatom+0x1400+8,a4@(4)
	movl	#_nilatom+0x1400+12,a4@(8)
	movl	a3@(60),a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+4,a2@+
	movl	a3@(64),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+96,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(68),a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+8,a2@+
	movl	a3@(64),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+96,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(72),a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+12,a2@+
	movl	a3@(64),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+96,a5
	jbsr	a5@
	movl	d3,a2
	movl	#_nilatom+0x1400+4,a2@+
	movl	a3@(60),a2@+	|(calling tget)
	movl	a3@(64),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+104,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00154
	movl	a3@(60),a2@+	|(calling tget)
	movl	a3@(76),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+104,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jne	L00154
	movl	d7,a2@+	|(calling putprop)
	movl	#_nilatom+0x1400+180,a2@+
	movl	a3@(64),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+96,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00154
	movl	#_nilatom+0x1400+180,a2@+
	movl	d7,a2@+	|(calling tget)
	movl	a3@(64),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+104,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00154
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00157
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00156
L00157:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00156:
	jra	L00153
L00154:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00159
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00158
L00159:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00158:
L00153:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(80),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(84),a2@+	|(calling tmemq)
	movl	a3@(88),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+112,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d6
	cmpl	d0,d6
	jne	L00161
	movl	a3@(92),a2@+
	movl	a3@(96),a2@+	|(calling tmemq)
	movl	a3@(100),a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+112,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00163
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00164
	jra	L00161
L00163:
	subql	#8,a2
L00164:
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00166
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00165
L00166:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00165:
	jra	L00160
L00161:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00168
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00167
L00168:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00167:
L00160:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(104),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(108),d0
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
	jeq	L00170
	movl	a3@(112),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	cmpb	#9,a5@(0,d0:L)
	jne	L00170
	movl	a3@(116),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	cmpb	#3,a5@(0,d0:L)
	jne	L00170
	movl	a3@(120),a2@+
	movl	d7,a2@+
	jbsr	_qcons
	movl	d7,d6
	cmpl	d0,d6
	jeq	L00170
	movl	a3@(124),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	cmpb	#1,a5@(0,d0:L)
	jne	L00170
	movl	a3@(128),d0
	subl	d7,d0
	moveq	#9,d1
	asrl	d1,d0
	lea	_typetable+1,a5
	cmpb	#0,a5@(0,d0:L)
	jne	L00170
	movl	a3@(132),a2@+
	movl	a3@(136),a2@+	|(calling ttype)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+120,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00170
	movl	a3@(140),a2@+
	movl	a3@(144),a2@+	|(calling ttype)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+120,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00170
	movl	a3@(148),a2@+
	movl	#_nilatom+0x1400+4,a2@+	|(calling ttype)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+120,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00170
	movl	a3@(152),a2@+
	movl	a3@(156),a2@+	|(calling ttype)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+120,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00170
	movl	a3@(160),a2@+
	movl	a3@(164),a2@+	|(calling ttype)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+120,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00170
	movl	a3@(168),a2@+
	movl	a3@(172),a2@+	|(calling ttype)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+120,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00170
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00175
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00174
L00175:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00174:
	jra	L00169
L00170:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00177
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00176
L00177:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00176:
L00169:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(176),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(180),a2@+
	movl	a3@(84),a2@+	|(calling lexpr-argtest)
	movl	a3@(184),a2@+
	movl	a3@(96),a2@+
	movl	a3@(188),a2@+
	movl	a3@(192),a2@+
	movl	a3@(196),a2@+
	lea	a2@(-24),a5
	movl	a5,d3
	movl	trantb+128,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00180
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00181
	jra	L00179
L00180:
	subql	#8,a2
L00181:
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00183
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00182
L00183:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00182:
	jra	L00178
L00179:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00185
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00184
L00185:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00184:
L00178:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(200),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(204),a2@+
	movl	#_nilatom+0x1400+4,a2@+	|(calling lexpr-setargtest)
	movl	#_nilatom+0x1400+8,a2@+
	movl	#_nilatom+0x1400+12,a2@+
	movl	#_nilatom+0x1400+16,a2@+
	movl	#_nilatom+0x1400+20,a2@+
	movl	#_nilatom+0x1400+24,a2@+
	movl	#_nilatom+0x1400+28,a2@+
	movl	#_nilatom+0x1400+32,a2@+
	movl	#_nilatom+0x1400+36,a2@+
	lea	a2@(-36),a5
	movl	a5,d3
	movl	trantb+136,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00188
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00189
	jra	L00187
L00188:
	subql	#8,a2
L00189:
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00191
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00190
L00191:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00190:
	jra	L00186
L00187:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00193
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00192
L00193:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00192:
L00186:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(208),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	#_nilatom+0x1400+40,a2@+
	movl	#_nilatom+0x1400+0,a2@+	|(calling lexpr-tail-merge)
	movl	#_nilatom+0x1400+40,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+144,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00195
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00197
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00196
L00197:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00196:
	jra	L00194
L00195:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00199
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00198
L00199:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00198:
L00194:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(212),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	#_nilatom+0x1400+20,a2@+
	movl	#_nilatom+0x1400+4,a2@+	|(calling lexpr-cc)
	movl	#_nilatom+0x1400+8,a2@+
	movl	#_nilatom+0x1400+12,a2@+
	movl	#_nilatom+0x1400+16,a2@+
	movl	#_nilatom+0x1400+20,a2@+
	lea	a2@(-20),a5
	movl	a5,d3
	movl	trantb+152,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00201
	movl	#_nilatom+0x1400+8,a2@+
	movl	d7,a2@+	|(calling lexpr-cc)
	movl	#_nilatom+0x1400+8,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+152,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00201
	movl	#_nilatom+0x1400+4,a2@+
	movl	#_nilatom+0x1400+4,a2@+	|(calling lexpr-cc)
	movl	#_nilatom+0x1400+8,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+152,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00201
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00204
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00203
L00204:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00203:
	jra	L00200
L00201:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00206
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00205
L00206:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00205:
L00200:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(216),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(220),a2@+
	movl	a3@(224),a2@+	|(calling tail-merge)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+160,a5
	jbsr	a5@
	movl	d3,a2
	movl	a2@-,d1
	movl	d0,d6
	cmpl	d1,d6
	jne	L00208
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00210
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00209
L00210:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00209:
	jra	L00207
L00208:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00212
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00211
L00212:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00211:
L00207:
	movl	a3@(16),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(228),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(24),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(232),a2@+
	movl	a3@(236),a2@+	|(calling tail-merge2)
	movl	a3@(240),a2@+
	movl	a3@(244),a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+168,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00216
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00217
	jra	L00214
L00216:
	subql	#8,a2
L00217:
	movl	a3@(248),a2@+
	movl	#_nilatom+0x1400+48,a2@+	|(calling tail-merge2)
	movl	#_nilatom+0x1400+52,a2@+
	movl	#_nilatom+0x1400+56,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+168,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00218
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00219
	jra	L00214
L00218:
	subql	#8,a2
L00219:
	movl	a3@(252),a2@+
	movl	#_nilatom+0x1400+160,a2@+	|(calling tail-merge2)
	movl	#_nilatom+0x1400+80,a2@+
	movl	#_nilatom+0x1400+120,a2@+
	lea	a2@(-12),a5
	movl	a5,d3
	movl	trantb+168,a5
	jbsr	a5@
	movl	d3,a2
	movl	d0,a2@+
	movl	a2@(-8),d6
	cmpl	a2@(-4),d6
	jeq	L00220
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+72,a5
	jbsr	a5@
	movl	d3,a2
	tstl	d0
	jne	L00221
	jra	L00214
L00220:
	subql	#8,a2
L00221:
	movl	a3@(36),a5
	cmpl	a5@,d7
	jne	L00223
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00222
L00223:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00222:
	jra	L00213
L00214:
	movl	d7,d6
	cmpl	d7,d6
	jne	L00225
	movl	a3@(40),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
	movl	a3@(36),a5	|(calling *break)
	movl	a5@,a2@+
	movl	d7,a2@+
	lea	a2@(-8),a5
	movl	a5,d3
	movl	trantb+88,a5
	jbsr	a5@
	movl	d3,a2
	jra	L00224
L00225:
	movl	a3@(44),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling drain)
	movl	a5,d3
	movl	trantb+56,a5
	jbsr	a5@
	movl	d3,a2
L00224:
L00213:
	movl	a3@(256),a2@+	|(calling msg-print)
	lea	a2@(-4),a5
	movl	a5,d3
	movl	trantb+48,a5
	jbsr	a5@
	movl	d3,a2
	lea	a2@,a5	|(calling terpr)
	movl	a5,d3
	movl	trantb+80,a5
	jbsr	a5@
	movl	d3,a2
	movl	d7,d0
L00136:
	subl	#12,a2
	moveml	a6@(-L00134),#L00135
	unlk	a6
	rts
L00135 = 14528
L00134 = 20
bind_org:
	linker_size = 	65
	trans_size = 	22
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
	.long -1
lit_org:
.asciz "three"
.asciz "last-arg"
.asciz "first-arg"
.asciz "2"
.asciz "\"Testing \""
.asciz "\"misc functions\""
.asciz "\"...\""
.asciz "3000"
.asciz "3000"
.asciz "t"
.asciz "\"failed -- breaking.\""
.asciz "\"done.\""
.asciz "\"factorial\""
.ascii "788657867364790503552363213932185062295135977687173263294742"
.ascii "533244359449963403342920304284011984623904177212138919638830"
.ascii "257642790242637105061926624952829931113462857270763317237396"
.ascii "988943922445621451664240254033291864131227428294853277524242"
.ascii "407573903240321257405579568660226031904170324062351700858796"
.ascii "178922222789623703897374720000000000000000000000000000000000"
.asciz "000000000000000"
.asciz "\"get\""
.asciz "x"
.asciz "number"
.asciz "y"
.asciz "z"
.asciz "junk"
.asciz "\"memq\""
.asciz "a"
.asciz "(b c d e f g h i j k l)"
.asciz "(c d e f)"
.asciz "c"
.asciz "(a b c d e f)"
.asciz "\"type\""
.asciz "sdfsdfds"
.asciz "9999999999999999999999999999999"
.asciz "(a b c d)"
.asciz "(a d s a)"
.asciz "asdasdas"
.asciz "\"1212323213\""
.asciz "string"
.asciz "\"asdasdas\""
.asciz "bignum"
.asciz "99999999999999999999999999999"
.asciz "fixnum"
.asciz "symbol"
.asciz "asdasdasdas"
.asciz "flonum"
.asciz "123.123"
.asciz "list"
.asciz "(asd asd asd asd asd asd asd)"
.asciz "\"arg\""
.asciz "(a b c d e f)"
.asciz "b"
.asciz "d"
.asciz "e"
.asciz "f"
.asciz "\"setarg\""
.asciz "(first-arg 2 three 4 5 6 7 8 last-arg)"
.asciz "\"lexpr tail merge\""
.asciz "\"lexpr/cc\""
.asciz "\"tail merge1\""
.asciz "last"
.asciz "(1 2 3 4 5 6 7 8 7 6 5 6 67 last)"
.asciz "\"tail merge2\""
.asciz "(-1 -1 -1)"
.asciz "65535"
.asciz "65535"
.asciz "65535"
.asciz "(-1 0 -2)"
.asciz "(-3 7 17)"
.asciz "\"All tests completed successfully!\""
.asciz "greaterp"
.asciz "difference"
.asciz "tfact"
.asciz "times"
.asciz "lessp"
.asciz "length"
.asciz "msg-print"
.asciz "drain"
.asciz "nlist"
.asciz "equal"
.asciz "terpr"
.asciz "*break"
.asciz "putprop"
.asciz "tget"
.asciz "tmemq"
.asciz "ttype"
.asciz "lexpr-argtest"
.asciz "lexpr-setargtest"
.asciz "lexpr-tail-merge"
.asciz "lexpr-cc"
.asciz "tail-merge"
.asciz "tail-merge2"
.ascii "(setq fcn-in-test.l \"test.l compiled by Liszt 68000 version "
.asciz "8.35 on Fri Aug 19 13:12:19 1983\")"
.asciz "nlist"
.asciz "tfact"
.asciz "tget"
.asciz "tmemq"
.asciz "ttype"
.asciz "lexpr-argtest"
.asciz "lexpr-setargtest"
.asciz "lexpr-tail-merge"
.asciz "lexpr-cc"
.asciz "tail-merge"
.asciz "tail-merge2"
.asciz "test"
lit_end:
.data | this is just for documentation 
.asciz "@(#)Compiled by Liszt 68000 version 8.35 on Fri Aug 19 13:13:10 1983"
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

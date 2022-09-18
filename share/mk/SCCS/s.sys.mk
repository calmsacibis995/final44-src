h20412
s 00003/00000/00098
d D 8.2 94/03/21 17:49:51 bostic 19 17
c add a default .c to target rule
c From: Christos Zoulas <christos@deshaw.com>
e
s 00003/00000/00098
d R 8.2 94/03/19 10:45:37 bostic 18 17
c add a ``shuttle'' rule from .c to the program
c From: Christos Zoulas <christos@deshaw.com>
e
s 00000/00000/00098
d D 8.1 93/07/09 15:57:48 bostic 17 16
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00097
d D 5.15 93/07/09 15:57:37 bostic 16 14
c just call cpp; Sparc doesn't use traditional, depend on cpp to be
c right per architecgture.
e
s 00000/00000/00098
d R 8.1 93/06/08 11:36:13 bostic 15 14
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00003/00094
d D 5.14 93/05/12 11:02:34 elan 14 13
c Converted to gcc2.
e
s 00004/00000/00093
d D 5.13 93/02/16 13:14:27 torek 13 12
c sparc gcc2 wants -O4, not just -O
e
s 00026/00026/00067
d D 5.12 92/07/16 13:47:25 bostic 12 11
c permit command line options to override
e
s 00000/00009/00093
d D 5.11 91/03/13 13:01:55 bostic 11 10
c no longer need special cases for hp300, 386
e
s 00002/00002/00100
d D 5.10 90/12/17 14:54:55 william 10 9
c 386 uses gas and gcc's cpp just like hp300
e
s 00001/00001/00101
d D 5.9 90/06/29 17:29:16 bostic 9 8
c hp300's use gcc-cpp at the moment.
e
s 00009/00000/00093
d D 5.8 90/06/22 19:05:26 bostic 8 7
c checkpoint .mk files
e
s 00002/00000/00091
d D 5.7 90/05/10 17:23:11 bostic 7 6
c add sccs id
e
s 00023/00040/00068
d D 5.6 90/05/08 13:42:49 bostic 6 5
c checkpoint, the world rebuilds
e
s 00002/00002/00106
d D 5.5 90/03/17 15:16:27 bostic 5 4
c full paths for ci, co
e
s 00001/00003/00107
d D 5.4 90/03/16 12:01:09 bostic 4 3
c remove .INCLUDES, it's going away
e
s 00021/00025/00089
d D 5.3 90/03/13 11:07:08 bostic 3 2
c checkpoint (lots of stuff)
e
s 00094/00090/00020
d D 5.2 89/09/25 17:16:14 bostic 2 1
c rework for BSD
e
s 00110/00000/00000
d D 5.1 89/09/13 16:46:29 bostic 1 0
c initial distribution
e
u
U
t
T
I 7
#	%W% (Berkeley) %G%

E 7
I 1
D 2
#
# System Makefile for:
#	ISI68K running BSD UNIX
#
# These are the variables used to specify the nature of the system on which
# pmake is running. These names may later be used in #if expressions for
# conditional reading of the enclosed portion of the Makefile
#
isi68k		= Machine is an isi68k
mc68000		= so it has a Motorola 68000-family chip.
unix		= It runs UNIX.
mc68020		= It has a 68020 microprocessor.
E 2
I 2
D 12
unix=		We run UNIX.
E 12
I 12
unix		?=	We run UNIX.
E 12
D 4
LIBC=		/lib/libc.a
E 4
D 6
SHELL=		/bin/sh
E 6
E 2

D 2
.SUFFIXES 	: .out .a .ln .o .c .F .f .e .r .y .l .s .cl .p .h \
		.c,v .y,v .l,v .s,v .h,v
.INCLUDES 	: .h
.LIBS		: .a
.NULL		: .out
E 2
I 2
D 3
.MAIN: all
E 2

E 3
D 2
YACC		= yacc
YFLAGS		=
LEX		= lex
LFLAGS		=
CC		= cc
#if defined(vax) || defined(sun)
AS		= as
#else
AS		= as -
#endif
PC		= pc
PFLAGS		=
CFLAGS		=
#ifdef SYSV
ASFLAGS		= 
#else
AFLAGS		=
#endif SYSV
RC		= f77
RFLAGS		=
FC		= f77
EFLAGS		=
FFLAGS		=
LOADLIBES	=
CO		= co
COFLAGS		=
CI		= ci
CIFLAGS		=
AR		= ar
ARFLAGS		= rl
E 2
I 2
D 6
.SUFFIXES: .out .a .ln .o .c .F .f .e .r .y .l .s .cl .p .h \
D 3
		.c,v .y,v .l,v .s,v .h,v .8 .7 .6 .5 .4 .3 .2 .1 .0
E 3
I 3
		.8 .7 .6 .5 .4 .3 .2 .1 .0
E 6
I 6
.SUFFIXES: .out .a .ln .o .c .F .f .e .r .y .l .s .cl .p .h 
E 6

D 6
# for RCS
#.SUFFIXES: .out .a .ln .o .c .F .f .e .r .y .l .s .cl .p .h \
#		.c,v .y,v .l,v .s,v .h,v .8 .7 .6 .5 .4 .3 .2 .1 .0

E 6
E 3
D 4
.INCLUDES:	.h
E 4
.LIBS:		.a
D 3
.NULL:		.out
E 3
I 3
D 6
#.NULL:		.out
E 6
E 3
E 2

D 2
.c,v.c .y,v.y .l,v.l .s,v.s .h,v.h :
	$(CO) $(COFLAGS) $(.IMPSRC) $(.TARGET)
E 2
I 2
D 3
AR=		ar
E 3
I 3
D 6
AR=		/usr/bin/ar
E 6
I 6
D 12
AR=		ar
E 6
E 3
ARFLAGS=	rl
I 6
RANLIB=		ranlib
E 12
I 12
AR		?=	ar
ARFLAGS		?=	rl
RANLIB		?=	ranlib
E 12
E 6
E 2

I 8
D 10
.if (${MACHINE} == "hp300")
E 10
I 10
D 11
.if (${MACHINE} == "hp300" || ${MACHINE} == "i386")
E 10
AS=		/usr/local/lib/gcc-as
.else
E 11
E 8
D 2
.c.o 		:
	$(CC) $(CFLAGS) -c $(.IMPSRC)
E 2
I 2
D 3
AS=		as
E 3
I 3
D 6
AS=		/usr/bin/as
E 6
I 6
D 12
AS=		as
I 8
D 11
.endif

E 11
E 8
E 6
E 3
AFLAGS=
E 12
I 12
AS		?=	as
AFLAGS		?=
E 12
E 2

D 2
.p.o 		:
	$(PC) $(PFLAGS) -c $(.IMPSRC)
E 2
I 2
D 3
CC=		cc
E 3
I 3
D 6
CC=		/usr/bin/cc
E 6
I 6
D 12
CC=		cc
E 6
E 3
CFLAGS=		-O
E 12
I 12
D 14
CC		?=	cc
E 14
I 14
CC		?=	gcc

E 14
I 13
.if ${MACHINE} == "sparc"
CFLAGS		?=	-O4
.else
E 13
D 14
CFLAGS		?=	-O
E 14
I 14
CFLAGS		?=	-O2
E 14
I 13
.endif
E 13
E 12
E 2

I 8
D 10
.if (${MACHINE} == "hp300")
E 10
I 10
D 11
.if (${MACHINE} == "hp300" || ${MACHINE} == "i386")
E 10
D 9
CPP=		cpp -traditional
E 9
I 9
CPP=		/usr/local/lib/gcc-cpp -traditional
E 9
.else
E 11
E 8
D 2
.cl.o 		:
	class -c $(.IMPSRC)
E 2
I 2
D 5
CI=		ci
E 5
I 5
D 6
CI=		/usr/new/ci
E 5
CIFLAGS=
D 5
CO=		co
E 5
I 5
CO=		/usr/new/co
E 5
COFLAGS=
E 6
I 6
D 12
CPP=		cpp
E 12
I 12
D 14
CPP		?=	cpp
E 14
I 14
D 16
CPP		?=	/usr/libexec/gcc2/cpp -traditional
E 16
I 16
CPP		?=	cpp
E 16
E 14
E 12
I 8
D 11
.endif
E 11
E 8
E 6
E 2

D 2
.e.o .r.o .F.o .f.o :
	$(FC) $(RFLAGS) $(EFLAGS) $(FFLAGS) -c $(.IMPSRC)
E 2
I 2
D 3
CPP=		newcpp
E 3
I 3
D 6
CPP=		/usr/bin/newcpp
E 3
E 2

D 2
#ifdef SYSV
.s.o 		:
	$(AS) $(ASFLAGS) -o $(.TARGET) $(.IMPSRC)
#else
.s.o 		:
	$(AS) $(AFLAGS) -o $(.TARGET) $(.IMPSRC)
#endif
E 2
I 2
D 3
FC=		f77
E 3
I 3
FC=		/usr/bin/f77
E 3
FFLAGS=
E 6
I 6
D 12
FC=		f77
FFLAGS=		-O
E 6
EFLAGS=
E 12
I 12
FC		?=	f77
FFLAGS		?=	-O
EFLAGS		?=
E 12
E 2

D 2
.y.o 		:
	$(YACC) $(YFLAGS) $(.IMPSRC)
	$(CC) $(CFLAGS) -c y.tab.c
E 2
I 2
D 3
LEX=		lex
E 3
I 3
D 6
LEX=		/usr/bin/lex
E 6
I 6
D 12
LEX=		lex
E 6
E 3
LFLAGS=
E 12
I 12
LEX		?=	lex
LFLAGS		?=
E 12

D 3
LINT=		lint
E 3
I 3
D 6
LINT=		/usr/bin/lint
E 6
I 6
D 12
LD=		ld
LDFLAGS=
E 12
I 12
LD		?=	ld
LDFLAGS		?=
E 12

D 12
LINT=		lint
E 6
E 3
LINTFLAGS=	-chapbx
E 12
I 12
LINT		?=	lint
LINTFLAGS	?=	-chapbx
E 12

D 3
MAKE=		make
E 3
I 3
D 6
MAKE=		/usr/src/usr.bin/pmake/obj/pmake
E 6
I 6
D 12
MAKE=		make
E 12
I 12
MAKE		?=	make
E 12
E 6
E 3

D 3
NROFF=		nroff
E 3
I 3
D 6
NROFF=		/usr/bin/nroff
E 3

D 3
PC=		pc
E 3
I 3
PC=		/usr/bin/pc
E 6
I 6
D 12
PC=		pc
E 6
E 3
PFLAGS=
E 12
I 12
PC		?=	pc
PFLAGS		?=
E 12

D 3
RC=		f77
E 3
I 3
D 6
RC=		/usr/bin/f77
E 6
I 6
D 12
RC=		f77
E 6
E 3
RFLAGS=
E 12
I 12
RC		?=	f77
RFLAGS		?=
E 12

D 3
YACC=		yacc
E 3
I 3
D 6
YACC=		/usr/bin/yacc
E 3
YFLAGS=
E 6
I 6
D 12
SHELL=		sh
E 12
I 12
SHELL		?=	sh
E 12
E 6

D 3
.c,v.c .y,v.y .l,v.l .s,v.s .h,v.h:
	${CO} ${COFLAGS} ${.IMPSRC} ${.TARGET}
E 3
I 3
D 6
#.c,v.c .y,v.y .l,v.l .s,v.s .h,v.h:
#	${CO} ${COFLAGS} ${.IMPSRC} ${.TARGET}
E 6
I 6
D 12
YACC=		yacc
YFLAGS=-d
E 12
I 12
YACC		?=	yacc
YFLAGS		?=	-d
E 12
E 6
E 3

I 19
.c:
	${CC} ${CFLAGS} ${.IMPSRC} -o ${.TARGET}

E 19
.c.o:
D 4
	${CC} ${.INCLUDES} ${CFLAGS} -c ${.IMPSRC}
E 4
I 4
	${CC} ${CFLAGS} -c ${.IMPSRC}
E 4

.p.o:
	${PC} ${PFLAGS} -c ${.IMPSRC}

D 6
.cl.o:
	class -c ${.IMPSRC}

E 6
.e.o .r.o .F.o .f.o:
	${FC} ${RFLAGS} ${EFLAGS} ${FFLAGS} -c ${.IMPSRC}

.s.o:
	${AS} ${AFLAGS} -o ${.TARGET} ${.IMPSRC}

.y.o:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c y.tab.c -o ${.TARGET}
E 2
D 6
	rm y.tab.c
E 6
I 6
	rm -f y.tab.c
E 6
D 2
	mv y.tab.o $(.TARGET)
E 2

D 2
.l.o 		:
	$(LEX) $(LFLAGS) $(.IMPSRC)
	$(CC) $(CFLAGS) -c lex.yy.c
E 2
I 2
.l.o:
	${LEX} ${LFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} -c lex.yy.c -o ${.TARGET}
E 2
D 6
	rm lex.yy.c
E 6
I 6
	rm -f lex.yy.c
E 6
D 2
	mv lex.yy.o $(.TARGET)
E 2

D 2
.y.c 		:
	$(YACC) $(YFLAGS) $(.IMPSRC)
	mv y.tab.c $(.TARGET)
E 2
I 2
.y.c:
	${YACC} ${YFLAGS} ${.IMPSRC}
	mv y.tab.c ${.TARGET}
E 2

D 2
.l.c 		:
	$(LEX) $(LFLAGS) $(.IMPSRC)
	mv lex.yy.c $(.TARGET)
E 2
I 2
.l.c:
	${LEX} ${LFLAGS} ${.IMPSRC}
	mv lex.yy.c ${.TARGET}
E 2

D 2
.s.out .c.out .o.out :
	$(CC) $(CFLAGS) $(.IMPSRC) $(LOADLIBES) -o $(.TARGET)
E 2
I 2
.s.out .c.out .o.out:
	${CC} ${CFLAGS} ${.IMPSRC} ${LDLIBS} -o ${.TARGET}
E 2

D 2
.f.out .F.out .r.out .e.out :
	$(FC) $(EFLAGS) $(RFLAGS) $(FFLAGS) $(.IMPSRC) \
		$(LOADLIBES) -o $(.TARGET)
	rm -f $(.PREFIX).o
E 2
I 2
.f.out .F.out .r.out .e.out:
	${FC} ${EFLAGS} ${RFLAGS} ${FFLAGS} ${.IMPSRC} \
	    ${LDLIBS} -o ${.TARGET}
	rm -f ${.PREFIX}.o
E 2

D 2
.y.out 		:
	$(YACC) $(YFLAGS) $(.IMPSRC)
	$(CC) $(CFLAGS) y.tab.c $(LOADLIBES) -ly -o $(.TARGET)
E 2
I 2
.y.out:
	${YACC} ${YFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} y.tab.c ${LDLIBS} -ly -o ${.TARGET}
E 2
D 6
	rm y.tab.c
E 6
I 6
	rm -f y.tab.c
E 6

D 2
.l.out 		:
	$(LEX) $(LFLAGS) $(.IMPSRC)
	$(CC) $(CFLAGS) lex.yy.c $(LOADLIBES) -ll -o $(.TARGET)
E 2
I 2
.l.out:
	${LEX} ${LFLAGS} ${.IMPSRC}
	${CC} ${CFLAGS} lex.yy.c ${LDLIBS} -ll -o ${.TARGET}
E 2
D 6
	rm lex.yy.c
I 2

.8.0 .7.0 .6.0 .5.0 .4.0 .3.0 .2.0 .1.0:
	${NROFF} -man -h ${.IMPSRC} > ${.TARGET}
E 6
I 6
	rm -f lex.yy.c
E 6
D 3

DEPENDFILE=	.depend
.if exists(${DEPENDFILE})
.include ".depend"
.endif


E 3
E 2
E 1

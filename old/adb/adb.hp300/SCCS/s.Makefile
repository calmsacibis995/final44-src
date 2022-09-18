h03788
s 00007/00012/00008
d D 5.2 93/04/26 18:29:42 bostic 2 1
c new VM version for HP68K's
e
s 00020/00000/00000
d D 5.1 93/04/26 18:26:57 bostic 1 0
c date and time created 93/04/26 18:26:57 by bostic
e
u
U
t
T
I 1
D 2
#
#	Makefile	4.4	86/06/07
#
E 2
I 2
#	%W% (Berkeley) %G%

E 2
PROG=	adb
SRCS=	access.c command.c expr.c format.c input.c main.c message.c \
D 2
	opset.hp300.c optab.hp300.c output.c pcs.c print.c \
	runpcs.c setup.c sym.c
ASPATH=	../../../usr.bin/gas
SYSPATH=../../../sys/hp300

CC=	cc -traditional
INCS= -I. -I${.CURDIR} -I${.CURDIR}/${SYSPATH}
DFLAGS = -DADB -DNEWVM
CFLAGS+= -w -g ${DFLAGS} ${INCS}
E 2
I 2
	opset.hp300.c optab.hp300.c output.c pcs.c print.c runpcs.c \
	setup.c sym.c
.PATH:	${.CURDIR}/../common_source
DFLAGS=	-DADB -DNEWVM
CC+=	-traditional
CFLAGS+=-w -g ${DFLAGS} -I. -I${.CURDIR} -I${.CURDIR}/../../../sys/hp300
E 2

optab.hp300.o message.o:
	${CC} ${CFLAGS} -R -c ${.IMPSRC}

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

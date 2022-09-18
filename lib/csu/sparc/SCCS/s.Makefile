h23006
s 00000/00000/00025
d D 8.1 93/06/01 23:58:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00015/00023
d D 5.2 92/08/24 22:32:16 torek 2 1
c update for new profiling style
e
s 00038/00000/00000
d D 5.1 92/06/25 06:43:44 torek 1 0
c date and time created 92/06/25 06:43:44 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

CFLAGS=	-O -DLIBC_SCCS
OBJS=	crt0.o gcrt0.o
D 2
CLEANFILES+=	gmon.o mon.o moncrt0.o core a.out
E 2
I 2
CLEANFILES+=	core a.out
E 2

all: ${OBJS}

crt0.o: crt0.c
	${CC} ${CFLAGS} -c -DCRT0 ${.ALLSRC}
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

D 2
moncrt0.o: crt0.c
E 2
I 2
gcrt0.o: crt0.c
E 2
	${CC} ${CFLAGS} -c -DMCRT0 ${.ALLSRC} -o ${.TARGET}
D 2
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

gcrt0.o: moncrt0.o gmon.o mcount.o
	${LD} -x -r -o ${.TARGET} moncrt0.o gmon.o mcount.o

gmon.o:	${.CURDIR}/../csu.gmon/gmon.c
	${CC} ${CFLAGS} -c ${DEFS} ${.CURDIR}/../csu.gmon/gmon.c
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

mcount.o: ${.CURDIR}/../csu.gmon/mcount.c
	${CC} ${CFLAGS} -c ${DEFS} ${.CURDIR}/../csu.gmon/mcount.c
E 2
	${LD} -x -r ${.TARGET}
	mv a.out ${.TARGET}

install:
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}/usr/lib

depend lint tags:

.include <bsd.prog.mk>
E 1

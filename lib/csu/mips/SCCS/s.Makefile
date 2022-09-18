h64994
s 00000/00000/00025
d D 8.1 93/06/01 23:57:03 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00000/00021
d D 5.3 93/03/13 15:48:11 ralph 3 2
c strip local symbols
e
s 00006/00003/00015
d D 5.2 93/02/20 19:00:22 ralph 2 1
c added __progname support
e
s 00018/00000/00000
d D 5.1 92/07/19 14:38:12 bostic 1 0
c date and time created 92/07/19 14:38:12 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

CFLAGS=	-O -DLIBC_SCCS
D 2
OBJS=	crt0.o
CLEANFILES+=	gmon.o mon.o moncrt0.o core a.out
E 2
I 2
OBJS=	crt0.o gcrt0.o
CLEANFILES+=	core a.out
E 2

all: ${OBJS}

crt0.o: crt0.s
D 2
	${CC} -c -DCRT0 ${.ALLSRC}
E 2
I 2
	${CPP} -DCRT0 ${.ALLSRC} | ${AS} -o $@
I 3
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 3

gcrt0.o: crt0.s
	${CPP} -DMCRT0 ${.ALLSRC} | ${AS} -o $@
I 3
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
E 3
E 2

install:
	install -o ${BINOWN} -g ${BINGRP} -m 444 ${OBJS} \
	    ${DESTDIR}/usr/lib

depend lint tags:

.include <bsd.prog.mk>
E 1

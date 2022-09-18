h44222
s 00000/00000/00019
d D 8.1 93/06/06 16:04:12 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00018
d D 5.2 90/07/03 18:55:45 bostic 2 1
c clean pxref.0
e
s 00019/00000/00000
d D 5.1 90/06/29 11:44:47 bostic 1 0
c date and time created 90/06/29 11:44:47 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN1=	pxref.0

all: pxref ${MAN1}

lint depend:

clean cleandir:
D 2
	rm -f pxref pxref.o
E 2
I 2
	rm -f pxref pxref.o ${MAN1}
E 2

pxref: pxref.p
	pc -w ${.CURDIR}/pxref.p -o ${.TARGET}

beforeinstall:
	install ${STRIP} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} pxref \
	    ${DESTDIR}/usr/bin

.include <bsd.prog.mk>
E 1

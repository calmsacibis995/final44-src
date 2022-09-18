h32705
s 00000/00000/00016
d D 8.1 93/06/06 16:17:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00016/00000/00000
d D 5.1 90/05/23 11:51:53 bostic 1 0
c date and time created 90/05/23 11:51:53 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN1=	shar.0

all shar: ${MAN1}

clean depend lint tags:

cleandir:
	rm -f ${MAN1}

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/shar.sh ${DESTDIR}/usr/bin/shar

.include <bsd.prog.mk>
E 1

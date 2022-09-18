h30234
s 00002/00000/00009
d D 5.2 90/06/19 14:53:03 bostic 2 1
c don't create obj link
e
s 00009/00000/00000
d D 5.1 90/05/24 21:32:50 bostic 1 0
c date and time created 90/05/24 21:32:50 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

I 2
NOOBJ=	noobj

E 2
MAKEHOSTS all clean cleandir depend lint tags:

install:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    MAKEHOSTS.sh ${DESTDIR}${BINDIR}/MAKEHOSTS

.include <bsd.prog.mk>
E 1

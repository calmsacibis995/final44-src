h43189
s 00001/00001/00008
d D 5.3 92/07/17 19:59:25 bostic 3 2
c typo
e
s 00001/00001/00008
d D 5.2 92/03/16 14:21:09 bostic 2 1
c don't make object directories
e
s 00009/00000/00000
d D 5.1 90/06/08 15:43:17 bostic 1 0
c date and time created 90/06/08 15:43:17 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
all hpux-as clean cleandir depend lint tags:
E 2
I 2
all hpux-as clean cleandir depend lint obj tags:
E 2

install:
D 3
	install -c -o ${BINOWN} -o ${BINGRP} -m ${BINMODE} hpux-as \
E 3
I 3
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} hpux-as \
E 3
	    ${DESTDIR}${BINDIR}

.include <bsd.prog.mk>
E 1

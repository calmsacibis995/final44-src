h46044
s 00000/00000/00012
d D 8.1 93/06/06 14:32:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00011
d D 5.2 90/06/08 14:41:09 bostic 2 1
c use bsd.prog.mk
e
s 00012/00000/00000
d D 5.1 90/05/11 15:14:39 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

all explain clean cleandir depend lint tags:

install:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${.CURDIR}/explain.d ${DESTDIR}/usr/share/dict
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/explain.sh ${DESTDIR}${BINDIR}/explain

.include "../../Makefile.inc"
D 2
.include <bsd.own.mk>
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1

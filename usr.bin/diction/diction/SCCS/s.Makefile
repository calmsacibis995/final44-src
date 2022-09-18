h51218
s 00000/00000/00015
d D 8.1 93/06/06 14:31:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00013
d D 5.2 90/06/19 16:26:59 bostic 2 1
c rename to dprog (that's what the shell script execs)
e
s 00014/00000/00000
d D 5.1 90/05/11 15:14:34 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
PROG=	diction
E 2
I 2
PROG=	dprog
E 2
BINDIR=	/usr/libexec
I 2
MAN1=	diction.0
E 2
MLINKS=	diction.1 explain.1

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${.CURDIR}/dict.d ${DESTDIR}/usr/share/dict
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/diction.sh ${DESTDIR}/usr/bin/diction

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

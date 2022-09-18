h01254
s 00000/00000/00017
d D 8.1 93/07/09 16:18:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00000/00012
d D 5.2 93/07/09 16:18:40 bostic 4 1
c install a cpp that doesn't set -traditional for the Sparc architecture
e
s 00005/00000/00012
d R 5.2 93/07/09 16:16:28 bostic 3 1
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00012
d R 8.1 93/06/06 14:29:13 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00000/00000
d D 5.1 93/05/03 21:10:39 bostic 1 0
c date and time created 93/05/03 21:10:39 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

NOMAN=noman
NOOBJ=noobj

all nologin clean cleandir depend lint tags:

beforeinstall:
I 4
.if ${MACHINE} == "sparc"
E 4
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
I 4
	    ${.CURDIR}/cpp.notraditional.sh ${DESTDIR}/usr/bin/cpp
.else
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
E 4
	    ${.CURDIR}/cpp.sh ${DESTDIR}/usr/bin/cpp
I 4
.endif
E 4

.include <bsd.prog.mk>
E 1

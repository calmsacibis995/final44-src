h09635
s 00004/00001/00010
d D 8.2 94/04/22 08:23:13 bostic 7 6
c delete the man page on cleandir
e
s 00000/00000/00011
d D 8.1 93/06/19 09:18:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00001/00011
d D 5.3 93/06/19 09:18:03 bostic 5 3
c build the man page in the obj directory
e
s 00000/00000/00012
d R 8.1 93/06/19 09:16:50 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00010
d D 5.2 93/06/19 09:16:46 bostic 3 1
c add a man page
e
s 00000/00000/00012
d R 8.1 93/06/05 11:09:03 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00000/00000
d D 5.1 92/04/02 14:05:20 bostic 1 0
c date and time created 92/04/02 14:05:20 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
NOMAN=noman
E 3
I 3
MAN8=	nologin.0
E 3
D 5
NOOBJ=noobj
E 5

D 3
all nologin clean cleandir depend lint tags:
E 3
I 3
D 7
nologin clean cleandir depend lint tags:
E 7
I 7
nologin clean depend lint tags:
E 7
E 3

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/nologin.sh ${DESTDIR}/sbin/nologin
I 7

cleandir:
	rm -f nologin.0
E 7

.include <bsd.prog.mk>
E 1

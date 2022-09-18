h51407
s 00000/00000/00014
d D 8.1 93/06/06 14:51:15 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00005
d D 5.2 91/11/11 15:33:51 bostic 2 1
c add groups, whoami
e
s 00005/00000/00000
d D 5.1 91/06/29 13:31:44 bostic 1 0
c date and time created 91/06/29 13:31:44 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	id
I 2
MAN1=   id.0 groups.0 whoami.0

afterinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/groups.sh ${DESTDIR}/usr/bin/groups
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/whoami.sh ${DESTDIR}/usr/bin/whoami
	${MINSTALL} groups.0 ${DESTDIR}${MANDIR}1/groups.0
	${MINSTALL} whoami.0 ${DESTDIR}${MANDIR}1/whoami.0
E 2

.include <bsd.prog.mk>
E 1

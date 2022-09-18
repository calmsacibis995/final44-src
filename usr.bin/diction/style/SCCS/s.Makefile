h33973
s 00000/00000/00018
d D 8.1 93/06/06 14:33:24 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00018/00000/00000
d D 5.1 90/05/11 15:14:44 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN1=	style.0

all style: ${MAN1}

clean depend lint tags:

cleandir:
	rm -f ${MAN1}

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	     ${.CURDIR}/style.sh ${DESTDIR}${BINDIR}/style


.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

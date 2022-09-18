h28614
s 00000/00000/00013
d D 8.1 93/06/06 15:55:54 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 5.1 90/06/29 11:42:24 bostic 1 0
c date and time created 90/06/29 11:42:24 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	pix
SRCDIR=	${.CURDIR}/../src
SRCS=	pix.c
OBJS+=	config.o
CFLAGS+=-I${SRCDIR}
CLEANFILES+=config.c

WHOAMI=	pi

.include "${SRCDIR}/config.include"
.include <bsd.prog.mk>
E 1

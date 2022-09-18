h42723
s 00000/00000/00021
d D 8.1 93/06/06 15:59:41 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00000/00000
d D 5.1 90/06/29 11:43:07 bostic 1 0
c date and time created 90/06/29 11:43:07 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	px_header
SRCDIR=	${.CURDIR}/../src
CFLAGS+=-I${SRCDIR}
LDFLAGS+=-N
SRCS=	px_header.c
OBJS+=	config.o
BINDIR=	/usr/libexec/pascal
NOMAN=	noman
CLEANFILES+=config.c

beforeinstall:
	strip px_header
	mv px_header temp
	dd if=temp of=px_header conv=sync
	rm -f temp

WHOAMI=		pi
.include "${SRCDIR}/config.include"
.include <bsd.prog.mk>
E 1

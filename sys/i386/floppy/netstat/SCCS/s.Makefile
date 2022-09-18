h40093
s 00000/00000/00012
d D 8.1 93/06/11 15:30:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00012
d D 5.2 93/04/27 10:31:27 bostic 2 1
c doesn't need libutil
e
s 00014/00000/00000
d D 5.1 91/05/03 18:42:03 bostic 1 0
c date and time created 91/05/03 18:42:03 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	netstat
SRCS=	host.c inet.c if.c main.c mbuf.c route.c unix.c ns.c iso.c
CFLAGS+=-DLETS_GET_SMALL
BINGRP=	kmem
BINMODE=2555
D 2
LDADD=	-lutil
DPADD=	${LIBUTIL}
E 2
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../usr.bin/netstat

.include <bsd.prog.mk>
E 1

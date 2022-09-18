h28059
s 00000/00000/00013
d D 8.1 93/06/11 15:29:12 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00000/00000
d D 5.1 91/05/03 18:33:23 bostic 1 0
c date and time created 91/05/03 18:33:23 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	init
SRCS=	init.c
CFLAGS+=-DLETS_GET_SMALL
DPADD=	${LIBUTIL}
LDADD=	-lutil
BINMODE=500
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../sbin/init

.include <bsd.prog.mk>
E 1

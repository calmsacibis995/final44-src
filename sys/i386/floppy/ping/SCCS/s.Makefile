h25033
s 00000/00000/00010
d D 8.1 93/06/11 15:30:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 91/05/03 18:42:06 bostic 1 0
c date and time created 91/05/03 18:42:06 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	ping
SRCS=	ping.c
CFLAGS+=-DLETS_GET_SMALL
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../sbin/ping

.include <bsd.prog.mk>
E 1

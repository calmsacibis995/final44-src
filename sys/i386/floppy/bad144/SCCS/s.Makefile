h25498
s 00000/00000/00011
d D 8.1 93/06/11 15:27:20 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 91/05/03 18:19:50 bostic 1 0
c date and time created 91/05/03 18:19:50 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	bad144
SRCS=	bad144.c
CFLAGS+=-DLETS_GET_SMALL
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../usr.sbin/bad144

.include <bsd.prog.mk>

E 1

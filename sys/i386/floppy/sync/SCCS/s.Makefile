h24971
s 00000/00000/00010
d D 8.1 93/06/11 15:32:25 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 91/05/03 19:11:57 bostic 1 0
c date and time created 91/05/03 19:11:57 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	sync
SRCS=	sync.c
CFLAGS+=-DLETS_GET_SMALL
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../bin/sync

.include <bsd.prog.mk>
E 1

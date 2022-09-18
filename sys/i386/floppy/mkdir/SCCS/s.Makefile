h33084
s 00000/00000/00007
d D 8.1 93/06/11 15:29:24 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00004/00006
d D 5.2 91/05/09 18:47:38 bostic 2 1
c roll our own
e
s 00010/00000/00000
d D 5.1 91/05/03 18:34:35 bostic 1 0
c date and time created 91/05/03 18:34:35 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mkdir
D 2
SRCS=	mkdir.c
CFLAGS+=-DLETS_GET_SMALL
E 2
I 2
CFLAGS+=-s -N -I${.CURDIR}/../cat
E 2
NOMAN=	noman
D 2
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../bin/mkdir
E 2

.include <bsd.prog.mk>
E 1

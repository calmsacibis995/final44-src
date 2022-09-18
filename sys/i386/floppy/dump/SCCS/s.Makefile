h33744
s 00000/00000/00011
d D 8.1 93/06/11 15:28:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 91/05/03 18:26:34 bostic 1 0
c date and time created 91/05/03 18:26:34 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	dump
SRCS=	dumpitime.c dumpmain.c dumpoptr.c dumptape.c dumptraverse.c \
	unctime.c
CFLAGS+=-DLETS_GET_SMALL -I${.CURDIR}/../../../../sbin/dump
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../sbin/dump

.include <bsd.prog.mk>
E 1

h34826
s 00000/00000/00010
d D 8.1 93/06/11 15:29:17 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00010
d D 5.2 93/04/27 18:14:01 bostic 2 1
c pwcache(3) now in the C library
e
s 00012/00000/00000
d D 5.1 91/05/03 18:34:21 bostic 1 0
c date and time created 91/05/03 18:34:21 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	ls
SRCS=	cmp.c ls.c print.c util.c
CFLAGS+=-DLETS_GET_SMALL
D 2
DPADD=	${LIBUTIL}
LDADD=	-lutil
E 2
NOMAN=	noman
LDFLAGS=-N
.PATH:	${.CURDIR}/../../../../bin/ls

.include <bsd.prog.mk>
E 1

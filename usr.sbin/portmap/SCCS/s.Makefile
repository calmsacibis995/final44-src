h40078
s 00000/00000/00008
d D 8.1 93/06/06 14:03:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00006
d D 5.3 93/04/27 18:10:58 bostic 3 2
c daemon(3) now in the C library
e
s 00002/00002/00006
d D 5.2 90/09/27 10:42:20 mckusick 2 1
c lint (from Torek)
e
s 00008/00000/00000
d D 5.1 90/08/23 15:59:59 mckusick 1 0
c date and time created 90/08/23 15:59:59 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	portmap
D 2
DPADD=	${LIBUTIL}
LDADD=	-lrpc
E 2
I 2
D 3
DPADD=	${LIBRPC} ${LIBUTIL}
LDADD=	-lrpc -lutil
E 3
I 3
DPADD=	${LIBRPC}
LDADD=	-lrpc
E 3
E 2
MAN8=	portmap.0

.include <bsd.prog.mk>
E 1

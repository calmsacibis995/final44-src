h25824
s 00000/00000/00010
d D 8.1 93/06/06 22:14:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 91/03/02 13:16:12 bostic 1 0
c date and time created 91/03/02 13:16:12 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	uupoll
CFLAGS+=-I${.CURDIR}/../includes
BINMODE=6555
DPADD=	${LIBCOMPAT}
LDADD=	${LIBUU} -lcompat
MAN8=	uupoll.0

.include <bsd.prog.mk>
E 1

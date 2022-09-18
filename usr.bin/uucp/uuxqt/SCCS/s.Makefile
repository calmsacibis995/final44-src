h26893
s 00000/00000/00011
d D 8.1 93/06/06 22:15:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 91/03/02 13:16:42 bostic 1 0
c date and time created 91/03/02 13:16:42 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	uuxqt
CFLAGS+=-I${.CURDIR}/../includes
BINDIR=	${LIBDIR}
BINMODE=6550
MAN8=	uuxqt.0
DPADD=	${LIBCOMPAT}
LDADD=	${LIBUU} -lcompat

.include <bsd.prog.mk>
E 1

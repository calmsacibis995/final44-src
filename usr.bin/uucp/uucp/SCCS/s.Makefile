h24491
s 00000/00000/00009
d D 8.1 93/06/06 22:14:07 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 91/03/02 13:15:41 bostic 1 0
c date and time created 91/03/02 13:15:41 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	uucp
CFLAGS+=-I${.CURDIR}/../includes
BINMODE=6555
DPADD=	${LIBCOMPAT}
LDADD=	${LIBUU} -lcompat

.include <bsd.prog.mk>
E 1

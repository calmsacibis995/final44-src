h25125
s 00000/00000/00010
d D 8.1 93/06/06 22:07:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 91/03/02 13:08:10 bostic 1 0
c date and time created 91/03/02 13:08:10 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	acucntrl
CFLAGS+=-I${.CURDIR}/../includes
BINDIR=	${LIBDIR}
BINOWN=	root
BINMODE=6550
MAN8=	acucntrl.0

.include <bsd.prog.mk>
E 1

h22536
s 00000/00000/00008
d D 8.1 93/06/06 22:14:59 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00000/00000
d D 5.1 91/03/02 13:16:32 bostic 1 0
c date and time created 91/03/02 13:16:32 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	uusnap
CFLAGS+=-I${.CURDIR}/../includes
BINMODE=6555
MAN8=	uusnap.0

.include <bsd.prog.mk>
E 1

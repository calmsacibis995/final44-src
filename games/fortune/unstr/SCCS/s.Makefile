h21434
s 00000/00000/00007
d D 8.1 93/05/31 17:16:10 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00007/00000/00000
d D 5.1 91/04/27 15:50:06 bostic 1 0
c date and time created 91/04/27 15:50:06 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	unstr
NOMAN=	noman
CFLAGS+=-I${.CURDIR}/../strfile

.include <bsd.prog.mk>
E 1

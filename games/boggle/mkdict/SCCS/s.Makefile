h22173
s 00000/00000/00009
d D 8.1 93/06/11 14:50:05 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 93/06/11 14:50:01 bostic 1 0
c date and time created 93/06/11 14:50:01 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mkdict
CFLAGS+=-I${.CURDIR}/../boggle
NOMAN=noman

install:

.include <bsd.prog.mk>
E 1

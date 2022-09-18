h15316
s 00007/00000/00000
d D 5.1 90/05/11 14:25:28 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	sortbib
CFLAGS+=-I${.CURDIR}/../refer

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

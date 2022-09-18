h17529
s 00008/00000/00000
d D 5.1 90/05/11 14:25:21 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	lookbib
CFLAGS+=-I${.CURDIR}/../refer
MLINKS=	lookbib.1 indxbib.1

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

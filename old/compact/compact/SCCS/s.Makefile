h26347
s 00010/00000/00000
d D 5.1 90/05/31 16:07:54 bostic 1 0
c date and time created 90/05/31 16:07:54 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	compact
SRCS=	compact.c tree.c
CFLAGS+=-I${.CURDIR}/../common_source
.PATH:	${.CURDIR}/../common_source
MLINKS=	compact.1 ccat.1 compact.1 uncompcat.1

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

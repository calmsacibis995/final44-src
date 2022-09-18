h23904
s 00010/00000/00000
d D 5.1 90/05/31 16:08:23 bostic 1 0
c date and time created 90/05/31 16:08:23 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	uncompact
SRCS=	uncompact.c tree.c
CFLAGS+=-I${.CURDIR}/../common_source
.PATH:	${.CURDIR}/../common_source
NOMAN=	noman

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

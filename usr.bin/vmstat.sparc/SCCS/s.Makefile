h28465
s 00000/00000/00011
d D 8.1 93/06/06 22:22:27 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00000
d D 5.1 93/05/21 15:10:04 torek 1 0
c date and time created 93/05/21 15:10:04 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	vmstat
SRCS=	getdev.c intr.c main.c mem.c names.c sum.c util.c vmstat.c
MAN8=	vmstat.0
BINGRP=	kmem
BINMODE=2555
DPADD=	${LIBKVM}
LDADD=	-lkvm

.include <bsd.prog.mk>
E 1

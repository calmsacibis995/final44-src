h26671
s 00000/00000/00009
d D 8.1 93/06/06 16:50:34 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00000/00000
d D 5.1 93/05/11 10:05:59 bostic 1 0
c date and time created 93/05/11 10:05:59 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mkhits
SRCS=	mkhits.c dohits.c asc_ebc.c ebc_disp.c
CFLAGS+=-I${.CURDIR}/.. -I.
NOMAN=	noman
.PATH:	${.CURDIR}/../../api

.include <bsd.prog.mk>
E 1

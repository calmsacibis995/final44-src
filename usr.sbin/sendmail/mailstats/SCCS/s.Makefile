h26054
s 00000/00000/00008
d D 8.1 93/06/07 10:21:34 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00008
d D 6.1 92/12/21 16:14:07 eric 2 1
c Release 6
e
s 00008/00000/00000
d D 5.1 90/05/11 16:08:43 bostic 1 0
c first pass for new make
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	mailstats
CFLAGS+=-I${.CURDIR}/../src
NOMAN=	noman

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1

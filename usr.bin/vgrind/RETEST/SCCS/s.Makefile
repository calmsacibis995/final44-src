h23319
s 00000/00000/00010
d D 8.1 93/06/06 22:19:29 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00010/00000/00000
d D 5.1 90/06/05 11:02:30 bostic 1 0
c date and time created 90/06/05 11:02:30 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	retest
SRCS=	regexp.c retest.c
.PATH:	${.CURDIR}/..
NOMAN=	noman

install:

.include <bsd.prog.mk>
E 1
